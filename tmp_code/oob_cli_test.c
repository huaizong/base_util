#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MYPORT 4000
#define MAXDATASIZE 100



int main(int argc, char **argv)
{
    int sock_fd, numbytes;
   
    char buf[MAXDATASIZE]; 

    struct hostent *he;

    struct sockaddr_in their_addr;

    if(argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    if((he = gethostbyname(argv[1]) == NULL)) {
        herror("gethostbyname");
        exit(1);
    }
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(MYPORT);
    their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//he->h_addr_list[0]);
    bzero(&(their_addr.sin_zero), 8);

    int new_fd;
    if((new_fd = connect(sock_fd, (struct sockaddr *)&their_addr,
        sizeof(struct sockaddr)) == -1)) {
        perror("connect");
        exit(1);
    }
    if(send(new_fd, "123", 3, 0) == -1) {
        perror("send");
        close(new_fd);
        exit(0);
    }
    printf("Send 3 byte of normal data\n");
    sleep(1);
    if(send(new_fd, "4", 1, MSG_OOB) == -1) {
        perror("send");
        close(new_fd);
        exit(0);
    }
    printf("Send 1 byte of OOB data\n");
    sleep(1);
    if(send(new_fd, "56", 2 , 0) == -1) {
        perror("send");
        close(new_fd);
        exit(0);
    }
    printf("Send 2 bytes of normal data\n");
    sleep(1);
    if(send(new_fd, "7", 1, MSG_OOB) == -1) {
        perror("send");
        close(new_fd);
        exit(0);
    }
    printf("Send 1 byte of OOB data\n");
    close(sock_fd);
    return 0; 
}
