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
	int					serverfd;
	int					clientfd; 
	struct sockaddr_in	serveraddr;
	struct sockaddr_in	clientaddr;
	socklen_t			clientlen;
	
	/* 面向连接的字节流, 套接字描述符一般值为3 */
	if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) == - 1) 
	{
	    perror("socket error");
	    return 1; 
	}
	/* 初始化客户端套接字地址 */
	memset(&clientaddr, 0, sizeof(struct sockaddr)); 
	
	/* 初始化服务器套接字地址 */
	memset(&serveraddr, 0, sizeof(struct sockaddr)); 
	serveraddr.sin_family      = AF_INET; 
	serveraddr.sin_port        = htons(SERVER_PORT);	// 主机字节序转换为网络字节序
	serveraddr.sin_addr.s_addr = INADDR_ANY;			// 套接字端点可以被绑定到所有的系统网络接口上
	printf("server: serveraddr = %u\n", serveraddr.sin_addr.s_addr);
	
	/* 套接字绑定地址 */
	if (bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) == - 1) 
	{
	    perror("bind error"); 
	    return 1;
	}
	/* 接收套接字连接请求 */
	if (listen(serverfd, CONNECT_NUM) == - 1) 
	{ 
	    perror("listen error"); 
	    return 1; 
	}
	
	while (1) 
	{
	    clientlen = sizeof(struct sockaddr_in);
		
		/* 获得连接请求并建立连接, 阻塞模式 */
		printf("server: ready to accept\n");
	    if ((clientfd = accept(serverfd, (struct sockaddr *)&clientaddr, &clientlen)) == - 1) 
		{
	        perror ("accept error");
	        continue;
	    }
	    printf("server: got connection from %s\n", inet_ntoa(clientaddr.sin_addr));
	    
		/* 接收 */
		printf("server: ready to receive\n");
		if ((recvbytes = recv(clientfd, recvbuf, BUF_LEN, 0) ) == -1) 
		{
	        perror ("recv error"); 
	        return 1; 
	    }
		printf("server: recvbytes = %zd\n", recvbytes);
	    if (recvbytes) 
		{
	        recvbuf[recvbytes] = '\0'; 
	        printf("server: receive: %s\n", recvbuf); 
	        sleep(3);
	    }
		/* 发送 */
	    printf("server: ready to send\n");
	    if (send(clientfd, "Hi, I am server", 16, 0) == -1) 
		{ 
	        perror("send error"); 
	        return 1; 
	    }
	    close(clientfd); 
	} 
	return 0; 
}
