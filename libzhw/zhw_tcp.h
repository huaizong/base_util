#pragma once
#include <stdlib.h>
#ifdef __cplusplus
extern "C"
{
#endif

typedef int process_client_reg(int fd, void *arg);
typedef int process_client_req(int fd, void *arg);
int zhw_tcp_listen(const char *ip, int port, process_client_req callback, void *arg);
int zhw_tcp_connect(const char *ip, int port, 
                    process_client_reg reg, 
                    process_client_req callback, 
                    void *arg);

#ifdef __cplusplus
}
#endif
