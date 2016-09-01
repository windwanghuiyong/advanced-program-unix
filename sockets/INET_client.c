#include <stdio.h> 
#include <string.h> 
#include <unistd.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

#include "macro.h"

int main(int argc, char *argv[]) 
{
    char				recvbuf[BUF_LEN];
	ssize_t				recvbytes;
    int					clientfd;
    struct sockaddr_in	serveraddr;
	
	/* 面向连接的字节流, 套接字描述符一般值为3 */
    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
        perror("socket error"); 
        return 1; 
    }
	/* 初始化服务器套接字地址 */
    memset(&serveraddr, 0, sizeof(struct sockaddr));
    serveraddr.sin_family      = AF_INET; 
    serveraddr.sin_port        = htons(SERVER_PORT);	// 主机字节序转换为网络字节序
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);	// 点分十进制地址转换成长整型
	printf("client:  serveraddr = %u\n", serveraddr.sin_addr.s_addr);
	
	/* 连接时将 sockaddr_in 强制转换为 sockaddr 格式 */
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) == -1) 
	{
        perror ("connect error"); 
        return 1; 
    }
	/* 发送 */
    printf("client: ready to send\n");
    if (send(clientfd, "Hello, I am client", 19, 0) == -1) 
	{
        perror ("send error"); 
        return 1; 
    }
	/* 接收 */
	printf("client: ready to receive\n");
    if ((recvbytes = recv(clientfd, recvbuf, BUF_LEN, 0)) == - 1) 
	{
        perror ("recv error"); 
        return 1; 
    }
	printf("client: recvbytes = %zd\n", recvbytes);
    if (recvbytes) 
	{ 
        recvbuf[recvbytes] = '\0' ; 
        printf("client: receive: %s\n", recvbuf); 
    } 
    close(clientfd);
    return 0; 
}
