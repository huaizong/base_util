#pragma once
struct zhw_cache_t;
struct zhw_cache_t *zhw_cache_create(size_t cache_num, size_t item_size);
void* zhw_cache_alloc(struct zhw_cache_t *p);
void zhw_cache_free(struct zhw_cache_t *p, void *e);
void zhw_cache_destroy(struct zhw_cache_t *p);
