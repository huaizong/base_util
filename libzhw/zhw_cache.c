#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "zhw_log.h"
#include "zhw_cache.h"

struct zhw_cache_t {
    void **pool;
    size_t valid_num;
    size_t cache_num;
    size_t item_size;
    pthread_mutex_t lock;
    
};

struct zhw_cache_t *zhw_cache_create(size_t cache_num, size_t item_size)
{
    struct zhw_cache_t *p = calloc(1, sizeof(struct zhw_cache_t));
    pthread_mutex_init(&p->lock, NULL);
    p->cache_num = cache_num;
    p->item_size = item_size;
    p->pool = calloc(cache_num, sizeof(void *));
    if(p->pool == NULL) {
        pthread_mutex_destroy(&p->lock);
        free(p);
        p = NULL;
    }
    size_t i = 0;
    for(i = 0; i < p->cache_num; i++) {
        p->pool[i] = calloc(1, p->item_size);
        p->valid_num++;
    }
    return p;
}


void* zhw_cache_alloc(struct zhw_cache_t *p)
{
    void *it = NULL;
    if(p->valid_num > 0) {
        if(pthread_mutex_lock(&p->lock) == 0) {
            if(p->valid_num > 0){
                it = p->pool[--p->valid_num];
            }
            pthread_mutex_unlock(&p->lock);
        }
    }
    if(!it) {
        it = calloc(1, p->item_size);
    }
    return it;
}

void zhw_cache_free(struct zhw_cache_t *p, void *it)
{
    if(p->valid_num < p->cache_num) {
        if(pthread_mutex_lock(&p->lock) == 0) {
            if(p->valid_num < p->cache_num) {
                memset(it, 0, p->item_size);
                p->pool[p->valid_num++] = it;
            } else {
                free(it);
            }
            pthread_mutex_unlock(&p->lock);
            return;
        }
    }
    free(it);
    return;
}

void zhw_cache_destroy(struct zhw_cache_t *p)
{
    if(!p) {
        return;
    }
    size_t i;
    for(i = 0; i < p->cache_num; i++) {
        if(p->pool[i]) { 
            free(p->pool[i]);
        }
    }
    free(p->pool);
    pthread_mutex_destroy(&p->lock);
    free(p);
}
