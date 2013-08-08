#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
#define ZHW_MAX_CONFIG_VAL_LEN 1024
typedef _zhw_int_config_var {
    const char *config_name;
    int *val;
    short must;
}ZHW_INT_CONFIG_VAR;

typedef _zhw_str_config_var {
    const char *config_name;
    char val[ZHW_MAX_CONFIG_VAL_LEN+1];
    short must;
}ZHW_INT_CONFIG_VAR;

#ifdef __cplusplus
}
#endif
