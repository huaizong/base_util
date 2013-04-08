#pragma once
#include <unistd.h>
#include "zhw_global.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct zhw_string_t {
    char *data;
    size_t len;
    struct zhw_string_t *next;
};

struct zhw_string_link_t {
    struct zhw_string_t *head;
    struct zhw_string_t *tail;
    size_t num;
};

int zhw_word_split(const char *data, size_t data_len, struct zhw_string_link_t **strings);

#ifdef __cplusplus
}
#endif
