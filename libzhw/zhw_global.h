#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif
enum ZHW_ERR_DESC_TYPE{
    ZHW_OK = 0,
    ZHW_ERR_START = 100,
    ZHW_INVALID_NULL_PARA,
    ZHW_MEMORY_OUT,
    ZHW_NO_FOUND,
};

const char * zhw_get_err_desc(int ec);
#ifdef __cplusplus
}
#endif
