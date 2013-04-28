#include <stdio.h>
#include "zhw_tcp.h"
static int process_one_conn(int sfd, void *arg);
int main(int argc, char *argv[])
{
    if(argc < 3) {
        printf("./sample_zhw_tcp ip port\n");
        return -1;
    }
    int port = atoi(argv[2]);
    const char *ip = argv[1];
    int ret = zhw_tcp_listen(ip, port, process_one_conn, NULL);
    if(ret == 0) {
        fprintf(stdout, "succ listen on ip: %s port: %d\n",  ip, port);
    } else {
        fprintf(stdout, "fail listen on ip: %s port: %d\n",  ip, port);
    }
    return 0;
} 

int process_one_conn(int sfd, void *arg)
{
    fprintf(stdout, "conn_sfd: %d arg: %p\n", sfd, arg);
    return 0;
}
