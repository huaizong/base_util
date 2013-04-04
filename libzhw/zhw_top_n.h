#pragma once
#include "zhw_global.h"
struct zhw_top_n_t_struct;
typedef struct zhw_top_n_t zhw_top_n_t;
int32_t zhw_top_n_init(zhw_top_n_t **handle);
int64_t zhw_top_n_query(zhw_top_n_t *handle, const char *key);
int32_t zhw_top_n_add(zhw_top_n_t *handle, const char *key);
int64_t zhw_top_n_add_and_get(zhw_top_n_t *handle, const char *key);
