#include <unistd.h>
#include "zhw_sys.h"

ssize_t zhw_read(int fd, void *ptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    nleft = n;
    while(nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if(nleft == n) {
                return (-1);
            } else {
                break;
            }
        } else if(nread == 0) {
            break;
        }
        nleft -= nread;
        ptr   += nread;
    }
    return (n - nleft);
}


ssize_t zhw_write(int fd, const void *ptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    
    nleft = n;
    while(nleft > 0) {
        if ((nwritten = write(fd, ptr, nleft)) < 0) {
            if (nleft == n) {
                return (-1);
            } else {
                break;
            }
        } else if (nwritten == 0) {
            break;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return (n - nleft);
}
