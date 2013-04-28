#pragma once
#include <stdlib.h>
#ifdef __cplusplus
extern "C"
{
#endif

typedef int process_client_req(void *arg, int sfd);
int zhw_tcp_listen(const char *ip, int port);

#ifdef __cplusplus
}
#endif
