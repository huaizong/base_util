#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "zhw_log.h"
#include "zhw_worker_pool.h"

struct zhw_worker_pool_task_t {
    size_t id;
};

struct zhw_worker_t {
    size_t id;
};

struct zhw_worker_pool_t {
    size_t id;
    struct zhw_worker_t *workers;
};



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
    struct zhw_worker_pool_t *pool,
    zhw_worker_pool_task_pt func,
    struct zhw_worker_pool_task_t **task
    )
{
    int ret = -1;
    if(NULL != func) {
        ret = func(NULL);
    }
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
