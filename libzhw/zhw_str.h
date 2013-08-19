#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct  _zhw_str_t {
    char *val; 
    uint32_t val_len;
    uint32_t max_len;
}zhw_str_t;



