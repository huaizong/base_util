#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct _zhw_ini_int32_t {
    const char *name;
    int32_t *val;
    short must;
}zhw_ini_int32_t;

typedef struct _zhw_ini_uint32_t {
    const char *name;
    uint32_t *val;
    short must;
}zhw_ini_uint32_t;

typedef struct _zhw_ini_int64_t {
    const char *name;
    int64_t *val;
    short must;
}zhw_ini_int64_t;

typedef struct _zhw_ini_uint64_t {
    const char *name;
    uint64_t *val;
    short must;
}zhw_ini_uint64_t;

typedef struct _zhw_ini_str_t {
    const char *name;
    char *val;
    uint32_t val_len;
    short must;
}zhw_ini_str_t;

typedef struct _zhw_ini_dict_node_t {
    char *key;
    char *val;
    uint32_t hash;
    uint32_t scope;
}zhw_ini_dict_node_t;

typedef struct _zhw_ini_dict_t {
    unsigned n;
    zhw_ini_dict_node_t *nodes;
}zhw_ini_dict_t;


zhw_ini_dict_t *zhw_ini_open(const char *file_path);

void zhw_ini_close(zhw_ini_dict_t *dict);

#ifdef __cplusplus
}
#endif
