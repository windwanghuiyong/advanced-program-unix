#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <errno.h>
#include <time.h>

#define UNIX_DOMAIN_PATH "/tmp/UNIX.domain"
#define MAXBUFSIZE 1024
#define LISTENQ 10
#define LOG_FILE_PATH "/tmp/UNIX.log"
int server_accept(int sockfd);

int main()
{
    int listenfd;
    int connfd;
    int len;
    int ret;
    pid_t childpid;
    struct sockaddr_un cliaddr;
    socklen_t cliaddr_len;
    struct sockaddr_un servaddr;
    listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("cannot create listening socket");
        return -1;
    }
    unlink(UNIX_DOMAIN_PATH);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strncpy(servaddr.sun_path, UNIX_DOMAIN_PATH, sizeof(servaddr.sun_path)-1);
    ret = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (ret == -1) {
        perror("cannot bind server socket");
        close(listenfd);
        unlink(UNIX_DOMAIN_PATH);
        return -1;
    }
    ret = listen(listenfd, LISTENQ);
    if (ret == -1) {
        perror("cannot listen the client connect request");
        close(listenfd);
        unlink(UNIX_DOMAIN_PATH);
        return 1;
    }
    while (1) {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
        if (connfd < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                perror("cannot accept the client connect request");
                close(listenfd);
                unlink(UNIX_DOMAIN_PATH);
                return -1;
            }
        }
        if ((childpid = fork()) < 0) {
            perror("cannot create child process");
            close(listenfd);
            unlink(UNIX_DOMAIN_PATH);
            return -1;
        } else if (childpid == 0) {
            ret = server_accept(connfd);
            exit(ret);
        } else {
            close(connfd);
        }
    }
    close(listenfd);
    unlink(UNIX_DOMAIN_PATH);
    return 0;
}

int server_accept(int sockfd)
{
    ssize_t n;
    char buf[MAXBUFSIZE];
    time_t timestamp;
    FILE *fp;
    memset(buf, 0, sizeof(buf));
    fp = fopen(LOG_FILE_PATH, "a");
    if (fp == NULL) {
        perror("fopen log file");
        return -1;
    }
    else
	printf("server: open log file  success\n");
again:
    while ((n = recv(sockfd, buf, MAXBUFSIZE, 0)) > 0) {
        printf("server: n = %d\n", n);
	buf[n] = '\n';
        buf[n+1] = '\0';
        strcpy(buf+21, buf);
        timestamp = time(NULL);
        strftime(buf, 20, "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
        buf[19] = ':';
        buf[20] = ' ';
        if (fputs(buf, fp)) {
            perror("fputs log file");
            return -1;
        }
    }
    if (n<0 && errno==EINTR) {
        goto again;
    } else if (n < 0) {
        perror("recv connfd msg");
        return -1;
    }
    close(sockfd);
    fclose(fp);
    return 0;
}
