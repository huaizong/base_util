#include <stdio.h>
#include "zhw_ini.h"
int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("./sample_zhw_ini libzhw.ini\n");
        return -1;
    }
    const char *file_path = argv[1];
    zhw_ini_dict_t *dict = zhw_ini_open(file_path);
    int c = -1;
    int c2 = -1;
    zhw_ini_int32_t int32_ary[] = {
        {"c", &c, 1},
        {"c2", &c2, 0},
        {NULL, NULL, 0},
        };

    zhw_ini_uint32_t uint32_ary[] = {
        {NULL, NULL, 0},
        };

    zhw_ini_int64_t int64_ary[] = {
        {NULL, NULL, 0},
        };

    zhw_ini_uint64_t uint64_ary[] = {
        {NULL, NULL, 0},
        };
    char a[64] = "a";
    char a2[64] = "a2";
    char b[64] = "b";
    char b2[64] = "b2";

    zhw_ini_str_t str_ary[] = {
        {"a", a, sizeof(a), 1},
        {"a2", a2, sizeof(a2), 0},
        {"b", b, sizeof(b), 1},
        {"b2", b2, sizeof(b2), 0},
        {NULL, NULL, 0, 0},
    };

    int ret = zhw_ini_parse_conf_file(dict, "global2",
                int32_ary,
                uint32_ary,
                int64_ary,
                uint64_ary,
                str_ary);
    fprintf(stdout,
    "a: %s, a2:%s\n"
    "b: %s, b2:%s\n"
    "c: %d, c2:%d\n",
        a, a2, b, b2, c, c2);
    ret = zhw_ini_parse_conf_file(dict, "global2",
                int32_ary,
                uint32_ary,
                int64_ary,
                uint64_ary,
                str_ary);
    zhw_ini_close(&dict);
    fprintf(stdout,
    "a: %s, a2:%s\n"
    "b: %s, b2:%s\n"
    "c: %d, c2:%d\n",
        a, a2, b, b2, c, c2);

    return ret;
}

