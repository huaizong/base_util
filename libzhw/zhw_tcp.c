#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

//select
#include <sys/select.h>

#include "zhw_tcp.h"


static int zhw_tcp_socket(const char *ip, int port);
static int zhw_tcp_use_select(int sfd);

int zhw_tcp_listen(const char *ip, int port)
{
    int sfd =  zhw_tcp_socket(ip, port);
    if(sfd < 0) {
        return -1;
    }
    int ret = zhw_tcp_use_select(sfd); 
    return ret;
}

int zhw_tcp_use_select(int sfd)
{
    fd_set rset;
    int maxfdp1;
    FD_ZERO(&rset);
    FD_SET(sfd, &rset);
    while(1) {
//        maxfdp1 = 
    }
    return 0;
}

int zhw_tcp_socket(const char *ip, int port)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd < 0) {
        perror("socket");
        return -1;
    }
    int flags = 1;
    int ret = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (void *)&flags, sizeof(flags));
    if (ret != 0) {
        perror("setsockopt");
        return -1;
    }
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = (ip != NULL) ? inet_addr(ip) : htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    ret = bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
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

