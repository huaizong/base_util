#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "zhw_log.h"
#include "zhw_worker_pool.h"

struct zhw_worker_pool_task_t {
    size_t id;
    long prio;
    zhw_worker_pool_task_pt call_back;
    struct zhw_worker_pool_task_t *next;
};

struct zhw_worker_pool_task_list_t {
    size_t sid;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    struct zhw_worker_pool_task_t *head;
    struct zhw_worker_pool_task_t *tail;
};

struct zhw_worker_t {
    size_t id;
    struct zhw_worker_pool_t *pool;
};

struct zhw_worker_pool_t {
    size_t id;
    long worker_num;
    long init_count;
    struct zhw_worker_t *workers;
    struct zhw_worker_pool_task_list_t tasks;
    pthread_mutex_t init_lock;
    pthread_cond_t init_cond;
};

static void register_thread_initialized(struct zhw_worker_pool_t *p) 
{
    pthread_mutex_lock(&p->init_lock);
    p->init_count++;
    pthread_cond_signal(&p->init_cond);
    pthread_mutex_unlock(&p->init_lock);
}


static void wait_for_thread_registration(struct zhw_worker_pool_t *p) 
{
    pthread_mutex_lock(&p->init_lock);
    while (p->init_count < p->worker_num) {
        pthread_cond_wait(&p->init_cond, &p->init_lock);
    }
    pthread_mutex_unlock(&p->init_lock);
}

static void *worker_walk_task(struct zhw_worker_t *worker)
{
    struct zhw_worker_pool_t *p = worker->pool;
    struct zhw_worker_pool_task_list_t *tasks = &p->tasks;
    struct zhw_worker_pool_task_t *task = NULL;
    while(1) {
        pthread_mutex_lock(&tasks->lock);
        while (tasks->head == NULL) {
            pthread_cond_wait(&tasks->cond, &tasks->lock);
        }
        task = tasks->head;
        tasks->head = task->next;
        if(NULL == tasks->head) {
            tasks->tail = NULL;
        }
        pthread_mutex_unlock(&tasks->lock);
        task->call_back(NULL);
    }
    return NULL;
}

static void *worker_thread_loop(void *arg)
{
    void *ret = NULL;
    struct zhw_worker_t *worker = (struct zhw_worker_t *)arg;
    register_thread_initialized(worker->pool);
    ZHW_LOG_INFO("worker thread in pool: %ld start", (long)worker->id);
    ret = worker_walk_task(worker);
    ZHW_LOG_INFO("worker thread in pool: %ld exit", (long)worker->id);
    pthread_exit(NULL);
    return ret;
}

static void create_worker_thread(void *(*func)(void *), void *arg) {
    pthread_t       tid;
    pthread_attr_t  attr;
    int             ret;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if ((ret = pthread_create(&tid, &attr, func, arg)) != 0) {
        fprintf(stderr, "Can't create thread: %s\n",
                strerror(ret));
        exit(1);
    }
    pthread_attr_destroy(&attr);
}

//
//初始化工作池
struct zhw_worker_pool_t *zhw_worker_pool_init(void)
{
    struct zhw_worker_pool_t *p = calloc(1, sizeof(struct zhw_worker_pool_t));
    if(NULL == p) {
        ZHW_LOG_ERR("CALLOC FAIL");
        return p;
    }
    const long cpu_num = sysconf(_SC_NPROCESSORS_ONLN);
    const long worker_num = cpu_num > 0 ? (cpu_num + 1) : 4;
    p->workers = calloc(worker_num, sizeof(struct zhw_worker_t));
    if(NULL == p->workers) {
        ZHW_LOG_ERR("CALLOC FAIL");
        free(p);
        p = NULL;
        return p;
    }
    ZHW_LOG_INFO("cpu_num: %ld, worker_num: %ld", cpu_num, worker_num);
    long i;
    pthread_mutex_init(&p->init_lock, NULL);
    pthread_cond_init(&p->init_cond, NULL);
    pthread_mutex_init(&p->tasks.lock, NULL);
    pthread_cond_init(&p->tasks.cond, NULL);
    p->worker_num = worker_num;
    for(i = 0; i < worker_num; i++) {
        p->workers[i].id = i;
        p->workers[i].pool = p;
        create_worker_thread(worker_thread_loop, &p->workers[i]);
    }
    wait_for_thread_registration(p);
    return p;
}

//
//销毁工作池
void zhw_destroy_worker_pool(struct zhw_worker_pool_t *p)
{
    if(NULL != p) {
        free(p);
    };
}

//
//创建任务
int zhw_worker_pool_create_task(
    struct zhw_worker_pool_t *p,
    zhw_worker_pool_task_pt call_back,
    struct zhw_worker_pool_task_t **ret_task
    )
{
    int ret = -1;
    struct zhw_worker_pool_task_t *task = calloc(1, sizeof(struct zhw_worker_pool_task_t));
    struct zhw_worker_pool_task_list_t *tasks = &p->tasks;
    if(ret_task) { 
        *ret_task = NULL;
    }
    pthread_mutex_lock(&tasks->lock);
    tasks->sid++;
    task->id = tasks->sid;
    task->call_back = call_back;
    if(tasks->tail == NULL) {
        tasks->head = tasks->tail = task;
    } else {
        tasks->tail->next = task;
        tasks->tail = task;
    }
    pthread_cond_signal(&tasks->cond);
    pthread_mutex_unlock(&tasks->lock);
    if(ret_task) {
        *ret_task = task;
    }
    ret = 0;
    return ret;
}


int zhw_worker_pool_watch_task(struct zhw_worker_pool_task_t *ww)
{
    int ret = -1;
    return ret;
}

int zhw_worker_pool_cancel_task(struct zhw_worker_pool_task_t *ww)
{
    int ret = -1;
    return ret;
}

int zhw_worker_pool_release_task(struct zhw_worker_pool_task_t *ww)
{
    int ret = -1;
    return ret;
}
