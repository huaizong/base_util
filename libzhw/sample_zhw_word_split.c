#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "zhw_word_split.h"

int main(int argc, char **argv)
{
    const int MAX_SIZE = 8*1024*1024;
    char *in = (char*)malloc(MAX_SIZE);
    char c;
    size_t size = 0;
    while((c=getc(stdin))!=EOF)
    {
        in[size++] = c;
    }
    struct zhw_string_link_t *strings = NULL;
    int ret = zhw_word_split(in, strlen(in), &strings);
    if(ret == 0 && strings) {
        struct zhw_string_t *walk = strings->head;
        int i = 0;
        while(walk) {
            i++;
            printf("[%04d](%*s)\t", i, (int)walk->len, walk->data);
        }
        printf("\n");
    } else {
        printf("zhw_word_split fail\n");
    }
    free(in);
    return 0;
}
