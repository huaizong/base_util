#include <stdio.h>
#include "zhw_tcp.h"
int main(int argc, char *argv[])
{
    if(argc < 3) {
        printf("./sample_zhw_tcp ip port\n");
        return -1;
    }
    int port = atoi(argv[2]);
    const char *ip = argv[1];
    int ret = zhw_tcp_listen(ip, port);
    if(ret == 0) {
        fprintf(stdout, "succ listen on ip: %s port: %d\n",  ip, port);
    } else {
        fprintf(stdout, "fail listen on ip: %s port: %d\n",  ip, port);
    }
    return 0;
} 
