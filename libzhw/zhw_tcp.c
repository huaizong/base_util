#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include <sys/epoll.h>

#include <errno.h>

#include "zhw_tcp.h"
#include "zhw_worker_pool.h"
#include "zhw_log.h"


static int zhw_nonblock_socket(void);
static int zhw_tcp_bind(const char *ip, int port);
static int zhw_tcp_cli_use_epoll(int sfd, process_client_req callback, void *arg);
static int zhw_tcp_use_epoll(int sfd, process_client_req callback, void *arg);
static int zhw_tcp_use_select(int sfd, process_client_req callback, void *arg);

int zhw_tcp_listen(const char *ip, int port, process_client_req callback, void *arg)
{
    int ret = 0;
    int sfd =  zhw_tcp_bind(ip, port);
    if(sfd < 0) {
        return -1;
    }
    #ifdef ZHW_USE_EPOLL
        ret = zhw_tcp_use_epoll(sfd, callback, arg);
    #else
        ret = zhw_tcp_use_select(sfd, callback, arg);
    #endif
    if(ret < 0) {
        close(sfd);
        return ret;
    }
    return ret;
}

int zhw_tcp_connect(const char *ip, int port,
                    process_client_reg reg,
                    process_client_req callback,
                    void *arg)
{
    int ret = 0;
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0) {
        perror("socket");
        return -1;
    }
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = (ip != NULL) ? inet_addr(ip) : htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    ret = connect(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret != 0) {
        perror("connect");
        close(sfd);
        return -1;
    }
    if(sfd < 0) {
        return -1;
    }
    if(reg) {
        ret = reg(sfd, arg);
        if(ret!= 0) {
            close(sfd);
            return ret;
        }
    }
    ret = zhw_tcp_cli_use_epoll(sfd, callback, arg);
    close(sfd);
    if(ret < 0) {
        return ret;
    }
    return ret;
}

int zhw_tcp_use_epoll(int sfd, process_client_req callback, void *arg)
{
    int efd = epoll_create(10);
    if(efd < 0) {
        ZHW_LOG_ERR("epoll_create fail: %s", strerror(errno));
        return -1;
    }
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sfd;
    if (epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ev) == -1) { 
        ZHW_LOG_ERR("epoll_ctl: %d %s", errno, strerror(errno));
        return -1;
    }
    struct epoll_event events[1024];
    int nfds, n;
    int conn_sfd, listen_sfd;
    struct zhw_worker_pool_t *worker_pool = zhw_worker_pool_init();
    while(1) {
        nfds = epoll_wait(efd, events,
                sizeof(events)/sizeof(struct epoll_event), -1);
        if (nfds == -1) {
            ZHW_LOG_ERR("epoll_wait: %d %s", errno, strerror(errno));
            break;
        }
        for (n = 0; n < nfds; n++) {
            listen_sfd = events[n].data.fd;
            struct sockaddr_in client_addr;
            socklen_t addrlen = sizeof(client_addr);
            bzero(&client_addr, addrlen);
            conn_sfd = accept(listen_sfd,  (struct sockaddr*)&client_addr, &addrlen);
            if(conn_sfd < 0) {
                ZHW_LOG_ERR("accept fail: %s", strerror(errno));
                continue;
            }
            int nonblock_flags;
            if ((nonblock_flags = fcntl(conn_sfd, F_GETFL, 0)) < 0 ||
                fcntl(conn_sfd, F_SETFL, nonblock_flags | O_NONBLOCK) < 0) {
                ZHW_LOG_ERR("setnonblock fail: %s", strerror(errno));
                close(conn_sfd);
                continue;
            }
            ZHW_LOG_DEBUG("%s:%d connected",  inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            zhw_worker_pool_create_task(
                worker_pool,
                callback,
                conn_sfd,
                arg,
                NULL);
        }
    }
    zhw_destroy_worker_pool(worker_pool);
    return 0;
}

int zhw_tcp_use_select(int sfd, process_client_req callback, void *arg)
{
    //TODO
    return 0;
}


int zhw_nonblock_socket(void)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0) {
        perror("socket");
        return -1;
    }
    int flags = 1;
    int ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (void *)&flags, sizeof(flags));
    if (ret != 0) {
        close(sfd);
        perror("setsockopt");
        return -1;
    }
    int nonblock_flags;
    if ((nonblock_flags = fcntl(sfd, F_GETFL, 0)) < 0 ||
        fcntl(sfd, F_SETFL, nonblock_flags | O_NONBLOCK) < 0) {
        close(sfd);
        ZHW_LOG_ERR("setnonblock fail: %s", strerror(errno));
        return -1;
    }
    return sfd;
}

int zhw_tcp_bind(const char *ip, int port)
{
    int sfd = zhw_nonblock_socket();
    if(sfd < 0) {
        perror("socket");
        return -1;
    }
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = (ip != NULL) ? inet_addr(ip) : htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    int ret = bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret != 0) {
        perror("bind");
        close(sfd);
        return -1;
    }
    ret = listen(sfd, 1024);
    if (ret != 0) {
        perror("listen");
        close(sfd);
        return -1;
    }
    return sfd;
}

int zhw_tcp_cli_use_epoll(int sfd, process_client_req callback, void *arg)
{
    int efd = epoll_create(10);
    if(efd < 0) {
        ZHW_LOG_ERR("epoll_create fail: %s", strerror(errno));
        return -1;
    }
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = sfd;
    if (epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ev) == -1) { 
        ZHW_LOG_ERR("epoll_ctl: %d %s", errno, strerror(errno));
        return -1;
    }
    struct epoll_event events[1024];
    int nfds, n;
    int conn_sfd;
    int ret = 0;
    while(1) {
        nfds = epoll_wait(efd, events,
                sizeof(events)/sizeof(struct epoll_event), -1);
        if (nfds == -1) {
            ZHW_LOG_ERR("epoll_wait: %d %s", errno, strerror(errno));
            break;
        }
        for (n = 0; n < nfds; n++) {
            conn_sfd = events[n].data.fd;
            ZHW_LOG_DEBUG("conn_sfd: %d", conn_sfd);
            ret = callback(conn_sfd, arg);
            if(ret < 0) {
                break;
            }
        }
        if(ret < 0) {
            break;
        }
    }
    return ret;
}
