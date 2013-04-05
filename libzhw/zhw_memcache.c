#include <libmemcached/memcached.h>
#include "zhw_log.h"
#include "zhw_global.h"

int zhw_mc_get_value(const char *mc_ip, int mc_port, const char *key, size_t key_len, char **value, size_t *value_len)
{
    int ret = -1;
    if(mc_ip == NULL || key == NULL || value == NULL) {
        ret = -1;
        return ret;
    }
    memcached_return rc;
    memcached_st *memc = memcached_create(NULL);
    memcached_server_st *serversa = memcached_server_list_append(NULL, mc_ip, mc_port, &rc);

    if (rc != MEMCACHED_SUCCESS) {
        ZHW_LOG_ERR("memcached_server_list_append serversa failed [%s] rc=[%d]", memcached_strerror(memc, rc), rc);
        goto out;
    }

    rc = memcached_server_push(memc, serversa);
    if (rc != MEMCACHED_SUCCESS) {
        ZHW_LOG_ERR("memcached_server_push serversa failed [%s],rc=[%d]",memcached_strerror(memc, rc),rc);
        goto out;
    }

    rc = memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_NO_BLOCK, 1ULL);
    if (rc != MEMCACHED_SUCCESS) {
        ZHW_LOG_ERR("memcached_behavior_set serversa failed [%s],rc=[%d]",memcached_strerror(memc, rc),rc);
        goto out;
    }
    uint32_t flag = 0;
    *value = memcached_get(memc, key, key_len, value_len, &flag, &rc);
    if (rc == MEMCACHED_SUCCESS) {
        ret = ZHW_OK;
    }else if (MEMCACHED_NOTFOUND == rc) {
        ret = ZHW_NO_FOUND;
    } else {
        ZHW_LOG_ERR("memcached_get failed [%s], rc=[%d]", memcached_strerror(memc, rc),rc);
        ret = -1;
    }
out:
    if (memc) {
        memcached_free(memc);
        memc = NULL;
    }
    if (serversa) {
        memcached_server_list_free(serversa);
        serversa = NULL;
    }
    return ret;
}

int mic_mc_set_value(const char *mc_ip, int mc_port, const char *key, size_t key_len, const char *value, size_t value_len)
{
    int ret = -1;
    if(mc_ip == NULL || key == NULL || value == NULL) {
        ret = -1;
        return ret;
    }
    memcached_return rc;
    memcached_st *memc = memcached_create(NULL);
    memcached_server_st *serversa = memcached_server_list_append(NULL, mc_ip, mc_port, &rc);

    if (rc != MEMCACHED_SUCCESS) {
        ZHW_LOG_ERR("memcached_server_list_append serversa failed [%s] rc=[%d]",memcached_strerror(memc, rc),rc);
        goto out;
    }

    rc = memcached_server_push(memc, serversa);
    if (rc != MEMCACHED_SUCCESS) {
        ZHW_LOG_ERR("memcached_server_push serversa failed [%s],rc=[%d]",memcached_strerror(memc, rc),rc);
        goto out;
    }

    rc = memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_NO_BLOCK, 1ULL);
    if (rc != MEMCACHED_SUCCESS) {
        ZHW_LOG_ERR("memcached_behavior_set serversa failed [%s],rc=[%d]",memcached_strerror(memc, rc),rc);
        goto out;
    }
    int flag = 0;
    int expire_time = 0;
    rc = memcached_set(memc, key, key_len, value, (size_t )value_len, (time_t)expire_time,(uint32_t)flag);

    if (rc != MEMCACHED_SUCCESS) {
        ZHW_LOG_ERR("set_memcached ip: %s port: %d, value Key=[%s],value = [%s], rc = [%d], key_len=[%d],value_len=[%d],set value failed [%s]",
                mc_ip, mc_port, key, value, rc, key_len, value_len,
                memcached_strerror(memc, rc));
    } else {
        ret = ZHW_OK;
    }

out:
    if (memc) {
        memcached_free(memc);
        memc = NULL;
    }
    if (serversa) {
        memcached_server_list_free(serversa);
        serversa = NULL;
    }
    return ret;
}
