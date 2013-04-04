#include "zhw_strip_token.h"

const char *zhw_strip_token(const char *data, struct zhw_strip_token_t tokens[], const int num)
{
    if(data == NULL || tokens == NULL) {
        return data;
    }
    const char *walk = data;
    int i;
    while(1) {
        for(i = 0; i < num; i++) {
            if(strncasecmp(tokens[i].data, walk, tokens[i].len) == 0) {
                walk += tokens[i].len;
                while(*walk && isblank(*walk)) {
                    walk++;
                }
                break;
            }//if
        }//for
        if(i == num) {
            break;
        }
    }
    return walk;
}
