#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/**************************************
	实例 3-11
		对指定的描述符打印文件状态标志
**************************************/
int get_flag(int fd)
{
	int		flags;
	
	/* 获取文件状态标志 */
	if ((flags = fcntl(fd, F_GETFL)) < 0)
	{
		perror("fcntl error");
		exit(1);
	}
	
	/* 使用屏蔽字 O_ACCMODE 获得访问模式位 */
	switch (flags & O_ACCMODE)
	{
	case O_RDONLY:
		printf("read only");
		break;

	case O_WRONLY:
		printf("write only");
		break;

	case O_RDWR:
		printf("read and write");
		break;

	default:
		perror("unknown access mode");
	}
	
	/* 每次写时追加 */
	if (flags & O_APPEND)
		printf(", append");
	
	/* 非阻塞模式 */
	if (flags & O_NONBLOCK)
		printf(", nonblocking");
	
	/* 等待写完成 */
	if (flags & O_SYNC)
		printf(", synchronous writes");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if (flags & O_FSYNC)
		printf(", synchronous writes");
#endif

	putchar('\n');
	return 0;
}

/*******************************************************
	对指定的描述符添加文件状态标志
		参数: flags are file status flags to turn on
*******************************************************/
void set_flag(int fd, int flags)
{
	int		flg;

	if ((flg = fcntl(fd, F_GETFL, 0)) < 0)
		perror("get flag error");

	flg |= flags;

	if (fcntl(fd, F_SETFL, flg) < 0)
		perror("set flag error");
}

/********************************************************
	对指定的描述符清除文件状态标志
		参数: flags are file status flags to turn off
********************************************************/
void cls_flag(int fd, int flags)
{
	int		flg;

	if ((flg = fcntl(fd, F_GETFL, 0)) < 0)
		perror("get flag error");

	flg &= ~flags;

	if (fcntl(fd, F_SETFL, flg) < 0)
		perror("set flag error");
}
