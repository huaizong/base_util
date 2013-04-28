#include <stdio.h>
#include "libzhw/zhw_tcp.h"

int main(int argc, char **argv)
{
    const char *ip = "127.0.0.1";
    int port = 12345;
    int ret = zhw_tcp_listen(ip, port);
    
    return ret;
}
