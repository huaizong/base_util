#pragma once
#include <stdlib.h>
#ifdef __cplusplus
extern "C"
{
#endif

struct zhw_strip_token_t {
    const char *data;
    size_t len;
};
const char *zhw_strip_token(const char *data, struct zhw_strip_token_t tokens[], int num);

#ifdef __cplusplus
}
#endif
