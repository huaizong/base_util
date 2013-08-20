#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include "zhw_ini.h"

#ifndef zhw_ini_parse_log
#define zhw_ini_parse_log(fmt, ...) fprintf(stderr, fmt"\n",##__VA_ARGS__)
#endif

static void zhw_ini_parse_line(
    zhw_ini_dict_t *zhw_dict,
    char **scope,
    ssize_t *scope_len,
    uint32_t *scope_hash,
    char *line,
    ssize_t line_len);

static uint32_t zhw_dict_hash(const char * key, ssize_t len);

static char *zhw_ini_key_map_val(
    zhw_ini_dict_t *zhw_dict,
    uint32_t scope_hash,
    const char *name);

void zhw_ini_close(zhw_ini_dict_t **dict)
{
    if(!dict || !(*dict)) {
        return ;
    }
    free((*dict)->nodes);
    free(*dict);
    *dict = NULL;
}

zhw_ini_dict_t *zhw_ini_open(const char *file_path)
{
    if(!file_path) {
        return NULL;
    }
    FILE *fp = fopen(file_path, "r");
    if(!fp) {
        return NULL;
    }
    char *scope = NULL;
    char *line = NULL;
    size_t line_cap = 0;
    ssize_t line_len = 0;
    ssize_t scope_len = 0;
    uint32_t scope_hash = 0;
    zhw_ini_dict_t *d = calloc(1, sizeof(zhw_ini_dict_t));
    while ((line_len = getline(&line, &line_cap, fp)) > 0) {
        zhw_ini_parse_line(d, &scope, &scope_len, &scope_hash, line, line_len);
    }
    return d;
}

int zhw_ini_parse_conf_file(zhw_ini_dict_t *dict, const char *scope,
                zhw_ini_int32_t int32_ary[],
                zhw_ini_uint32_t uint32_ary[],
                zhw_ini_int64_t int64_ary[],
                zhw_ini_uint64_t uint64_ary[],
                zhw_ini_str_t str_ary[]
    )
{
    uint32_t scope_hash =  zhw_dict_hash(scope, strlen(scope));
    int i = 0;
    for(i = 0; int32_ary[i].val != NULL; i++) {
        char *val = zhw_ini_key_map_val(dict, scope_hash, int32_ary[i].key);
        if (val == NULL) {
            if(int32_ary[i].must) {
                zhw_ini_parse_log(
                    "config file key [%s]-->[%s] unfound", scope, int32_ary[i].key);
                return -1;
            }
        } else {
            *(int32_ary[i].val) = strtol(val, NULL, 0);
        }
    }
    for(i = 0; uint32_ary[i].val != NULL; i++) {
        char *val = zhw_ini_key_map_val(dict, scope_hash, uint32_ary[i].key);
        if (val == NULL) {
            if(uint32_ary[i].must) {
                zhw_ini_parse_log(
                    "config file key [%s]-->[%s] unfound", scope, uint32_ary[i].key);
                return -1;
            }
        } else {
            *(uint32_ary[i].val) = strtoul(val, NULL, 0);
        }
    }

    for(i = 0; int64_ary[i].val != NULL; i++) {
        char *val = zhw_ini_key_map_val(dict, scope_hash, int64_ary[i].key);
        if (val == NULL) {
            if(int64_ary[i].must) {
                zhw_ini_parse_log(
                    "config file key [%s]-->[%s] unfound", scope, int64_ary[i].key);
                return -1;
            }
        } else {
            *(int64_ary[i].val) = strtoull(val, NULL, 0);
        }
    }
    for(i = 0; uint64_ary[i].val != NULL; i++) {
        char *val = zhw_ini_key_map_val(dict, scope_hash, uint64_ary[i].key);
        if (val == NULL) {
            if(uint64_ary[i].must) {
                zhw_ini_parse_log(
                    "config file key [%s]-->[%s] unfound", scope, uint64_ary[i].key);
                return -1;
            }
        } else {
            *(uint64_ary[i].val) = strtoull(val, NULL, 0);
        }
    }

    for(i = 0; str_ary[i].val != NULL; i++) {
        char *val = zhw_ini_key_map_val(dict, scope_hash, str_ary[i].key);
        if (val == NULL) {
            if(str_ary[i].must) {
                zhw_ini_parse_log(
                    "config file key [%s]-->[%s] unfound", scope, str_ary[i].key);
                return -1;
            }
            continue;
        }
        if(strlen(val) >= str_ary[i].max_len) {
            zhw_ini_parse_log(
                "config file key [%s]-->[%s] too long", scope, str_ary[i].key);
            return -1;
        } else {
            memcpy(str_ary[i].val, val, strlen(val));
            str_ary[i].val[strlen(val)] = '\0';
        }
    }

    return 0;
}

static char *zhw_ini_key_map_val(
    zhw_ini_dict_t *zhw_dict,
    uint32_t scope_hash,
    const char *key)
{
    if(zhw_dict == NULL || key == NULL) {
        return NULL;
    }
    uint32_t key_hash =  zhw_dict_hash(key, strlen(key));
    uint32_t i = 0;
    for(i = 0; i < zhw_dict->n; i++) { 
        zhw_ini_parse_log("key: %s %ld hash: %u try map key: %s val:%s", key, strlen(key), key_hash, zhw_dict->nodes[i].key, zhw_dict->nodes[i].val);
        if(zhw_dict->nodes[i].scope == scope_hash
            && zhw_dict->nodes[i].hash == key_hash
            && strcmp(zhw_dict->nodes[i].key, key) == 0) {
            zhw_ini_parse_log("key: %s %ld hash: %u map val:%s", key, strlen(key), key_hash, zhw_dict->nodes[i].val);
            return zhw_dict->nodes[i].val;
        }
    }
    return NULL;
}

static char *trim_str_left(short ini_line, char *str, ssize_t *len)
{
    assert(str != NULL);
    char *walk = str;
    while(*walk) {
        if(ini_line && *walk == '#') {
            *walk = '\0';
            return walk;
        }
        if(!isspace(*walk)) {
            break;
        }
        walk++;
    }
    *len -= walk - str;
    return walk;
}

static char *trim_str_right(short ini_line, char *str, ssize_t *len)
{
    assert(str != NULL);
    if(*len < 1) {
        return str;
    }
    char *walk = str + *len - 1;
    while(walk > str) {
        if(ini_line && *walk == '#') {
            *walk = '\0';
            walk--;
            continue;
        }
        if(!isspace(*walk)) {
            break;
        }
        walk--;
    }
    if(ini_line && *walk != '"') {
        char *tmp_walk = walk;
        char *tmp_end = NULL;
        while(tmp_walk > str && *tmp_walk != '=') {
            if(*tmp_walk == '#') {
                *tmp_walk = '\0';
                tmp_end = tmp_walk - 1;
            }
            tmp_walk--;
        }
        if(tmp_end != NULL) {
            walk =  tmp_end;
        }
    }
    *len = walk - str + 1;
    return str;
}

static uint32_t zhw_dict_hash(const char * key, ssize_t len)
{
    uint32_t    hash ;
    ssize_t         i ;

    for (hash=0, i=0 ; i<len ; i++) {
        hash += (unsigned)key[i] ;
        hash += (hash<<10);
        hash ^= (hash>>6) ;
    }
    hash += (hash <<3);
    hash ^= (hash >>11);
    hash += (hash <<15);
    return hash ;
}

static void zhw_ini_parse_line(
    zhw_ini_dict_t *d,
    char **scope,
    ssize_t *scope_len,
    uint32_t *scope_hash,
    char *line,
    ssize_t line_len)
{
    assert(scope != NULL && scope_len != NULL);
    if(!line) {
        return;
    }
    ssize_t len = line_len;
    line = trim_str_left(1, line, &len);
    line = trim_str_right(1, line, &len);
    if(len >= 2 && *line == '[' && line[len-1] == ']') {
        if(*scope_len < (len-1)) {
            if(*scope) {
                free(*scope);
            }
            *scope = calloc(1, len + 1 - 2);
            *scope_len = len + 1 - 2;
        }
        char *tmp = *scope;
        memcpy(tmp, line+1, len-1);
        tmp[len-2] = '\0';
        *scope_hash = zhw_dict_hash(*scope, (*scope_len) - 1);
        zhw_ini_parse_log("scope: %s", *scope);
        return;
    }
    if(!*scope) {//if *scope is null, key = val is invaid
        return;
    }
    char *key_end = memchr(line, '=', len);
    if(!key_end) {
        return;
    }
    char *val = key_end + 1;
    *key_end = '\0';
    char *key = line;
    ssize_t key_len = strlen(line);
    ssize_t val_len = strlen(val);
    key = trim_str_left(0, key, &key_len);
    key = trim_str_right(0, key, &key_len);
    val = trim_str_left(0, val, &val_len);
    val = trim_str_right(0, val, &val_len);
    if(val_len >= 2 && *val == '"' && val[val_len-1] == '"') {
        val[val_len-1] = '\0';
        val = val + 1;
        val_len -= 2;
    }

    d->nodes = realloc(d->nodes, sizeof(zhw_ini_dict_node_t) * (d->n + 1));
    zhw_ini_dict_node_t *node = &d->nodes[d->n];
    d->n += 1;
    node->key = calloc(1, key_len + 1);
    memcpy(node->key, key, key_len);

    node->val = calloc(1, val_len + 1);
    memcpy(node->val, val, val_len);

    node->hash = zhw_dict_hash(key, key_len);
    node->scope = *scope_hash;
    zhw_ini_parse_log("key: [%s] %ld %u, val: [%s]", node->key, key_len, node->hash,  node->val);
    return;
}


