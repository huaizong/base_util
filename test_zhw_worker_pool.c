#include <stdio.h>

#include "zhw_worker_pool.h"
static int test_task(void *p)
{
    fprintf(stdout, "It's a simple task, para: %p\n", p);
    return 0;
}

int main(int argc, char **argv)
{
    struct zhw_worker_pool_t *pool = zhw_worker_pool_init();
    zhw_destroy_worker_pool(pool);
    return 0;
}
