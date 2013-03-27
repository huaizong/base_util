#pragma once
struct hzw_cache_t;
hzw_cache_t* hzw_cache_create(size_t item_size);
void hzw_cache_reverse(hzw_cache_t *p, size_t item_num);
void* hzw_cache_alloc(hzw_cache_t *p);
void hzw_cache_free(hzw_cache_t *p, void *e);
void hzw_cache_destroy(hzw_cache_t *p);
