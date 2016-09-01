#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <errno.h>

#define UNIX_DOMAIN_PATH "/tmp/UNIX.domain"
#define MAXBUFSIZE 1024

int main()
{
    int connfd;
    int ret;
    char buf[MAXBUFSIZE];
    static struct sockaddr_un servaddr;
    connfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    printf("client: connfd = %d\n", connfd);
    if (connfd < 0) {
        perror("cannot create connect socket");
        return -1;
    }
    servaddr.sun_family = AF_LOCAL;
    strncpy(servaddr.sun_path, UNIX_DOMAIN_PATH, sizeof(servaddr.sun_path)-1);
    printf("servaddr.sun_path = %s\n", servaddr.sun_path);
    ret = connect(connfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (ret == -1) {
        perror("cannot connect to the server");
        return -1;
    }
    else
	printf("connect success\n");
    memset(buf, 0, MAXBUFSIZE);
    strcpy(buf, "client");
    if (send(connfd, buf, strlen(buf), 0) == -1) {
        perror("cannot send msg to the server");
        return -1;
    }
    else
	printf("send success\n");
    close(connfd);
    return 0;
}
