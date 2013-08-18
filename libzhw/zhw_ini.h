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

typedef struct _zhw_ini_dict_t {
    unsigned n;
    char **key;
    char **val;
    char *scope;
}zhw_ini_dict_t;

zhw_ini_dict_t *zhw_ini_open_(const char *file_path);

const char *zhw_ini_key_map_val(
    zhw_ini_dict_t *zhw_dict, 
    const char *scope,
    const char *name);

void zhw_ini_close(zhw_ini_dict_t *dict);

#ifdef __cplusplus
}
#endif
