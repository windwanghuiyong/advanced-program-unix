#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>

/***********************************************************
    实例 16-12 16-22
        分配和初始化套接字端点供服务器使用
        使用地址复用
    参数
        套接字类型, 通用套接字地址结构, 套接字地址长度, 请求数量
***********************************************************/
int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
    int fd;
    int errno_tmp = 0;
    int reuse = 1;
	
	/* 创建服务器的套接字 */
    if ((fd = socket(addr->sa_family, type, 0)) < 0)
        return -1;
	
	/* 设置服务器套接字选项, 重复绑定同一个地址 */
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)
        goto errout;
		
	/* 服务器套接字绑定服务器地址 */
    if (bind(fd, addr, alen) < 0)
        goto errout;
	
	/* 面向连接的套接字类型 */
    if (   type == SOCK_STREAM
        || type == SOCK_SEQPACKET)
    {
        if (listen(fd, qlen) < 0)
            goto errout;
    }
    return fd;

errout:
    errno_tmp = errno;	//保存套接字函数返回的错误
    close(fd);          //防止 close 函数改变错误码
    errno = errno_tmp;
    return -1;
}
