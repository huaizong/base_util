#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define MYPORT 4000

#define BACKLOG 10

void sig_urg(int signo);
int new_fd;

int main(int argc, char **argv)
{
    int sock_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;

    int sin_size;
    int n;
    char buff[100];
   
    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    bzero(&(my_addr.sin_zero), 8);

    if(bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }
    if(listen(sock_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sig_t old_sig_urg_handle = signal(SIGURG, sig_urg);
    fcntl(sock_fd, F_SETOWN, getpid());
    while(1) 
    {
        sin_size = sizeof(struct sockaddr_in);
        if(new_fd = accept(sock_fd, (struct sokaddr*)&their_addr, &sin_size) == -1) {
            perror("accept");
            continue;
        }
        printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
        if(!fork()) {
            while(1) 
            {
                if((n = recv(new_fd, buff, sizeof(buff)-1, 0)) == 0) {
                    printf("received EOF\n");
                    break;
                }
                buff[n] = 0;
                printf("Recv %d bytes: %s\n", n, buff);
            }
            close(new_fd);
        }
    }
    while(waitpid(-1, NULL, WNOHANG) > 0);
    signal(SIGURG, old_sig_urg_handle);
}
        

void sig_urg(int signo)
{
    int n;
    char buff[100];
    printf("SIGURG received\n");
    n = recv(new_fd, buff, sizeof(buff)-1, MSG_OOB);
    buff[n] = 0;
    printf("recv: %d OOB byte: %s\n", n, buff);
}
