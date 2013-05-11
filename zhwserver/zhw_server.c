#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "zhw_tcp.h"
#include "zhw_log.h"
#include "zhw_server.h"
#define MAX_MSG_LEN 10240
int main(int argc, char *argv[])
{
    if(argc < 3) {
        printf("./zhw_server ip port\n");
        return -1;
    }
    int port = atoi(argv[2]);
    const char *ip = argv[1];
    int ret = zhw_tcp_listen(ip, port, process_smtp_conn, NULL);
    if(ret == 0) {
        ZHW_LOG_INFO("succ listen on ip: %s port: %d\n",  ip, port);
    } else {
        ZHW_LOG_ERR("fail listen on ip: %s port: %d\n",  ip, port);
    }
    return 0;
} 
