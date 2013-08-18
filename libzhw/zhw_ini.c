#include "zhw_ini.h"
static void zhw_ini_parse_line(
    zhw_ini_dict_t *zhw_dict,
    char **scope,
    const char *line);

static const char *zhw_ini_key_map_val(
    zhw_ini_dict_t *zhw_dict,
    const char *scope,
    const char *name);


zhw_ini_dict_t *zhw_ini_open_(const char *file_path)
{
    if(!file_path) }
        return NULL;
    }
    FILE *fp = fopen(file_path, "r");
    if(!fp) {
        return NULL;
    }
    char *scope = NULL;
    char *line = NULL;
    size_t line_cap = 0;
    ssize_t line_len;
    zhw_ini_dict_t *d = calloc(1, sizeof(zhw_ini_dict_t));
    while ((line_len = getline(&line, &line_cap, fp)) > 0) {
        zhw_ini_parse_line(d, &scope, line, line_len);
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
    *len -= wlak - str;
    return walk;
}

static char *trim_str_right(short ini_line, char *str, ssize_t *len)
{
    assert(str != NULL);
    if(len < 1) {
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
    zhw_ini_dict_t *zhw_dict,
    char **scope,
    ssize_t *scope_len,
    char *line,
    ssize_t line_len)
{
    assert(scope != NULL && scope_len != NULL);
    if(!line) {
        return;
    }
    ssize_t len = line_len;
    line = trim_str_left(1, line, &len)
    line = trim_str_right(1, line, &len)
    if(len >= 2 && *line == '"' && line[len-1] == '"') {
        line[len -1] = '\0';
        line = line + 1;
        len -= 2;
    }
    if(len >= 2 && *line == '[' && line[len-1] == ']') {
        if(*scope_len < len) {
            if(*scope) {
                free(*scope);
            }
            *scope = calloc(1, len + 1);
            *scope_len = len + 1;
        }
        char *tmp = *scope;
        memcpy(tmp, line, len);
        tmp[len] = '\0';
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
    key_end = '\0';
    char *key = line;
    ssize_t key_len = strlen(line);
    ssize_t val_len = strlen(val);
    key = trim_str_left(0, key, &key_len)
    key = trim_str_right(0, key, &key_len)
    val = trim_str_left(0, val, &val_len)
    val = trim_str_right(0, val, &val_len)

    zhw_ini_dict_node_t *node = calloc(1, sizeof(zhw_ini_dict_node_t));
    node->key = calloc(1, key_len + 1);
    memcpy(node->key, key, key_len);

    node->val = calloc(1, val_len + 1);
    memcpy(node->val, val, val_len);

    node->hash = zhw_dict_hash(key, &key_len)
    node->scope = zhw_dict_hash(scope, &scope_len)
    dict->nodes = realloc(dict->nodes, sizeof(zhw_ini_dict_node_t **) * (dict->n + 1));
    dict->nodes[dict->n] =node; 
    dict->n += 1;
    return;
}
    
    
    


}
