#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
int zhw_mc_get_value(const char *mc_ip, int mc_port,
                const char *key, size_t key_len,
                char **value, size_t *value_len);
int zhw_mc_set_value(const char *mc_ip, int mc_port,
                const char *key, size_t key_len,
                const char *value, size_t value_len);

#ifdef __cplusplus
}
#endif
