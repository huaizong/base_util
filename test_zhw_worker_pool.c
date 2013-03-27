#include <stdio.h>

#include "zhw_worker_pool.h"
static int test_task(void *p)
{
    fprintf(stdout, "It's a simple task, para: %p\n", p);
    return 0;
}

int main(int argc, char **argv)
{
    int ret = -1;
    struct zhw_worker_pool_t *pool = zhw_worker_pool_init();
    ret = zhw_worker_pool_create_task(pool, test_task, NULL);
    struct zhw_worker_pool_task_t *task = NULL;
    ret = zhw_worker_pool_create_task(pool, test_task, &task);
    zhw_destroy_worker_pool(pool);
    return ret;
}
