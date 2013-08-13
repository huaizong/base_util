#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api_b.h"

typedef struct _dict {
    size_t n;
    char **key;
    char **val;
}dict;


dict *open_conf_file(const char *path);

void print_conf_file(int code, dict *d, const char *scope);

void close_conf_file(dict *d);

void b_test_conf_file(int code, const char *path)
{
    printf("code: %d\n", code);
    dict *d = open_conf_file(path);
    print_conf_file(code, d, "show_test");
    close_conf_file(d);
}

void fill_dict(dict *d)
{
    size_t i = 0;
    char tmp[32];
    for(i = 0; i < d->n; i++) {
        snprintf(tmp, sizeof(tmp), "key_%02d", i);
        d->key[i] =  strdup(tmp);
        snprintf(tmp, sizeof(tmp), "val_%02d", i);
        d->val[i] =  strdup(tmp);
    }
}

dict *open_conf_file(const char *path)
{
    dict *d = calloc(1, sizeof(dict));
    d->n = 5;
    d->key = calloc(d->n, sizeof(char **));
    d->val = calloc(d->n, sizeof(char **));
    fill_dict(d);
    return d;
}

void print_conf_file(int code, dict *d, const char *scope)
{
    size_t i = 0;
    for(i = 0; i < d->n; i++) {
        printf("libapi_b_%s: %s\n", d->key[i], d->val[i]); 
    }
    printf("code: %d, scope: %s\n", code, scope);
}

void close_conf_file(dict *d)
{
    if(!d) {
        return;
    }
    size_t i = 0;
    for(i = 0; i < d->n; i++) {
        if(d->key[i]) {
            free(d->key[i]);
            d->key[i] = NULL;
        }
        if(d->val[i]) {
            free(d->val[i]);
            d->val[i] = NULL;
        }
    }
    free(d->key);
    free(d->val);
    free(d);
    d = NULL;
}

