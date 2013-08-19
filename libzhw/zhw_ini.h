#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _zhw_ini_int32_t {
    const char *key;
    int32_t *val;
    short must;
}zhw_ini_int32_t;

typedef struct _zhw_ini_uint32_t {
    const char *key;
    uint32_t *val;
    short must;
}zhw_ini_uint32_t;

typedef struct _zhw_ini_int64_t {
    const char *key;
    int64_t *val;
    short must;
}zhw_ini_int64_t;

typedef struct _zhw_ini_uint64_t {
    const char *key;
    uint64_t *val;
    short must;
}zhw_ini_uint64_t;

typedef struct _zhw_ini_str_t {
    const char *key;
    char *val;
    uint32_t max_len;
    short must;
}zhw_ini_str_t;

typedef struct _zhw_ini_dict_node_t {
    char *key;
    char *val;
    uint32_t hash;
    uint32_t scope;
}zhw_ini_dict_node_t;

typedef struct _zhw_ini_dict_t {
    uint32_t n;
    zhw_ini_dict_node_t *nodes;
}zhw_ini_dict_t;


zhw_ini_dict_t *zhw_ini_open(const char *file_path);

int zhw_ini_parse_conf_file(zhw_ini_dict_t *dict, const char *scope,
                zhw_ini_int32_t int32_ary[],
                zhw_ini_uint32_t uint32_ary[],
                zhw_ini_int64_t int64_ary[],
                zhw_ini_uint64_t uint64_ary[],
                zhw_ini_str_t str_ary[]
    );

void zhw_ini_close(zhw_ini_dict_t **dict);

#ifdef __cplusplus
}
#endif
