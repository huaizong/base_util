#pragma once
struct zhw_worker_pool_t;
struct zhw_worker_pool_task_t;
typedef int (*zhw_worker_pool_task_pt)(void *);

//
//初始化工作池
struct zhw_worker_pool_t *zhw_worker_pool_init(void);

//
//销毁工作池
void zhw_destroy_worker_pool(struct zhw_worker_pool_t *thpool);

//
//创建任务
struct zhw_worker_pool_task_t *zhw_worker_pool_create_task(
    struct zhw_worker_pool_t *pool,
    //任务内容
    zhw_worker_pool_task_pt func,
    //task 为NULL时创建任务，调用程序不检查任务进度
    //task 非NULL时创建任务，调用程序可通过返回值检查任务进度
    struct zhw_worker_pool_task_t **task
    );
//
//检查任务状态
int zhw_worker_pool_watch_task(struct zhw_worker_pool_task_t *ww);
//
//取消任务
int zhw_worker_pool_cancel_task(struct zhw_worker_pool_task_t *ww);
//
//释放任务资源
int zhw_worker_pool_release_task(struct zhw_worker_pool_task_t *ww);

