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
        ZHW_LOG_INFO("succ listen on ip: %s port: %d\n",  ip, port);
    } else {
        ZHW_LOG_ERR("fail listen on ip: %s port: %d\n",  ip, port);
    }
    return 0;
} 

int resp_msg(int sfd, const char *msg, size_t len)
{
    ZHW_LOG_DEBUG("resp: %.*s", len, msg);
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
    ZHW_LOG_DEBUG("conn_sfd: %d arg: %p\n", sfd, arg);
    char buf[MAX_MSG_LEN+1];
    int n, offset;
    offset = 0;
    const char *welcome_msg = "mx.jiuxtea.com welcome you\r\n";
    resp_msg(sfd, welcome_msg, strlen(welcome_msg));
    const char *default_msg = "250 2.1.0 Ok\r\n";
    short data_start = 0;
    while(1) {
        n = read(sfd, buf+offset, MAX_MSG_LEN - offset);
        ZHW_LOG_DEBUG("n :%d offset: %d buf: %s", n, offset, buf);
        buf[offset+n] = '\0';
        if(n > 0){
            offset += n;
            const char *walk = buf;
            const char *end = NULL;
            while(*walk && (end = strstr(walk, "\r\n")) != NULL) {
                ZHW_LOG_DEBUG("walk: %s", walk);
                if(data_start) {
                    if(strcmp(walk, ".\r\n") == 0) {
                        const char *finish_msg = "250 2.0.0 Ok: queued as D5B95180257\r\n";
                        resp_msg(sfd, finish_msg, strlen(finish_msg));
                        data_start = 0;
                        offset = 0;
                        walk = end + 2;
                        continue;
                    } else {
                        offset = 0;
                        walk = end + 2;
                        continue;
                    }
                } else if(strncasecmp("data\r\n", walk, strlen("data\r\n")) == 0) {
                    const char *notice_msg = "354 End data with <CR><LF>.<CR><LF>\r\n";
                    resp_msg(sfd, notice_msg, strlen(notice_msg));
                    data_start = 1; 
                    offset = 0;
                    walk = end + 2;
                    continue;
                } else if(strncasecmp("rcpt to:", walk, strlen("rcpt to:")) == 0) {
                    const char *tmp_msg = "250 2.1.5 Ok\r\n";
                    resp_msg(sfd, tmp_msg, strlen(tmp_msg));
                } else {
                    resp_msg(sfd, default_msg, strlen(default_msg));
                }
                if(strncasecmp("quit\r\n", walk, strlen("quit\r\n")) == 0) {
                    close(sfd);
                    return 0;
                }
                walk = end + 2;
            }
            if(*walk) {
                offset = buf + offset - walk;
                memmove(buf, walk, offset);
                buf[offset] = '\0';
            } else {
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
                ZHW_LOG_DEBUG("errno :%s", strerror(errno));
                usleep(1000);
                continue;
            }
            return -1;
        }
    }
        
    return 0;
}
