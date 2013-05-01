#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "zhw_tcp.h"
#include "zhw_log.h"
#define MAX_MSG_LEN 10240
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

int resp_msg(int sfd, const char *msg, size_t len)
{
    ssize_t n = 0;
    while(1) {
        n = write(sfd, msg, len);
        if(n > 0) {
            if(n == len) {
                return 0;
            }
            len -= n;
            msg += n;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                usleep(1000);
                continue;
            }
            return -1;
        }
    }
    return 0;
}

int process_one_conn(int sfd, void *arg)
{
    fprintf(stdout, "conn_sfd: %d arg: %p\n", sfd, arg);
    char buf[MAX_MSG_LEN];
    int n, offset;
    offset = 0;
    const char *default_msg = "250 2.1.0 Ok\r\n";
    const char *quit_cmd = "quit";
    while(1) {
        n = read(sfd, buf+offset, MAX_MSG_LEN - offset);
        if(n > 0){
            offset += n;
            if(strstr(buf, "\r\n") != NULL) {
                resp_msg(sfd, default_msg, strlen(default_msg));
                ZHW_LOG_DEBUG("%s", buf);
                if(strncmp(quit_cmd, buf, strlen(quit_cmd)) == 0) {
                    close(sfd);
                    return 0;
                }
                offset = 0;
            }
            if(offset < MAX_MSG_LEN) {
                continue;
            } else {
                close(sfd);
                return -1;
            }
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                usleep(1000);
                continue;
            }
            return -1;
        }
    }
        
    return 0;
}
