#include <sys/socket.h>
#include <unistd.h>

#define MAXSLEEP 128

/***************************
	实例 16-10
		支持重试的 connect
****************************/
int connect_retry_fd(int sockfd, const struct sockaddr *addr, socklen_t alen)
{
	int numsec;
	
	/* try to connect with exponential backoff */
	for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) 
	{
		/* connention accepted */
		if (connect(sockfd, addr, alen) == 0)	//  BSD 下, 若失败则 fd 变为未定义
			return (0);
		/* delay before trying again */
		if (numsec <= MAXSLEEP / 2)
			sleep(numsec);
	}
	return (-1);
}

/*********************************
	实例 16-11
		可移植的支持重试的 connect
*********************************/
int connect_retry(int domian, int type, int protocol, const struct sockaddr *addr, socklen_t alen)
{
	int numsec, fd;
	
	/* try to connect with exponential backoff */
	for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1)
	{
		/* 每次尝试连接前重新创建套接字 */
		if ((fd = socket(domian, type, protocol)) < 0)
			return (-1);
		/* connention accepted */
		if (connect(fd, addr, alen) == 0)
			return (fd);	// 返回一个已连接的客户端的套接字描述符
		close(fd);
		/* delay before trying again */
		if (numsec <= MAXSLEEP / 2)
			sleep(numsec);
	}
	return (-1);
}
