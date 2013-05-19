#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "zhw_tcp.h"
#include "zhw_log.h"
#define MAX_MSG_LEN 10240
#define ZHW_SMTP_SUPPORT_MSG \
                        "250-mx.jiuxtea.com\r\n"\
                        "250-PIPELINING\r\n"\
                        "250-SIZE 10240000\r\n"\
                        "250-VRFY\r\n"\
                        "250-ETRN\r\n"\
                        "250-ENHANCEDSTATUSCODES\r\n"\
                        "250-8BITMIME\r\n"\
                        "250 DSN\r\n"
static int resp_msg(int sfd, const char *msg, size_t len);

int process_smtp_conn(int sfd, void *arg)
{
    ZHW_LOG_DEBUG("conn_sfd: %d arg: %p\n", sfd, arg);
    char buf[MAX_MSG_LEN+1];
    ssize_t n, offset;
    offset = 0;
    const char *welcome_msg = "220 mx.jiuxtea.com ESMTP\r\n";
    resp_msg(sfd, welcome_msg, strlen(welcome_msg));
    const char *default_msg = "250 2.1.0 Ok\r\n";
    short data_start = 0;
    long sleep_times = 0;
    const long usleep_len = 10000;
    const char *msg = NULL;
    while(1) {
        n = read(sfd, buf+offset, MAX_MSG_LEN - offset);
        ZHW_LOG_DEBUG("n :%d offset: %d buf: %s", n, offset, buf);
        buf[offset+n] = '\0';
        if(n <= 0){
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                usleep(usleep_len);
                sleep_times += 1;
                if(sleep_times  > 5*100) {
                    close(sfd);
                    return 0;
                }
                continue;
            }
            close(sfd);
            return n;
        } else {
            sleep_times = 0;
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
                        walk = end + 2;
                        continue;
                    } else {
                        walk = end + 2;
                        continue;
                    }
                } else if(strncasecmp("data\r\n", walk, strlen("data\r\n")) == 0) {
                    const char *notice_msg = "354 End data with <CR><LF>.<CR><LF>\r\n";
                    resp_msg(sfd, notice_msg, strlen(notice_msg));
                    data_start = 1; 
                    walk = end + 2;
                    continue;
                } else if(strncasecmp("rcpt to:", walk, strlen("rcpt to:")) == 0) {
                    const char *tmp_msg = "250 2.1.5 Ok\r\n";
                    resp_msg(sfd, tmp_msg, strlen(tmp_msg));
                } else if(strncasecmp("ehlo ", walk, strlen("ehlo ")) == 0) {
                    msg = ZHW_SMTP_SUPPORT_MSG;
                    resp_msg(sfd, msg, strlen(msg));
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
                int walk_len = offset-1-10;
                ZHW_LOG_ERR("offset >=MAX_MSG_LEN %ld %ld %s", offset, MAX_MSG_LEN, buf+walk_len);
                memmove(buf, buf+walk_len, 10);
                offset = 10;
                continue;
            }
        }
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
