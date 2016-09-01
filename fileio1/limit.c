#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include "macro.h"

/******************************************
    不确定的运行时限制中：路径名长度
	实例 2-16 为路径名动态的分配空间
******************************************/

static long posix_version = 0;
static long xsi_version = 0;
/* If PATH is indeterminate, no guarantee this is adequate */

char *path_alloc(size_t *sizep) /*also return allocated size, if nonnull */
{
#ifdef PATH_MAX
	static long pathmax = PATH_MAX;
#else
	static long pathmax = 0;
#endif
	char *ptr;
	size_t size;

	if (posix_version == 0)
		posix_version = sysconf(_SC_VERSION);

	if (xsi_version == 0)
		xsi_version = sysconf(_SC_XOPEN_VERSION);

	if (pathmax == 0)	// first time through limits.h中没有定义，则调用pathconf函数
	{
		errno = 0;
		if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)	// 基于根目录的相对路径的最大长度
		{
			if (errno == 0)		// pathconf 指明 PATH_MAX 不确定，则猜测
				pathmax = PATH_MAX_GUSS;	// it's indeterminate
			else
				err_sys("pathconf error for _PC_PATH_MAX");
		}
		else
		{
			pathmax++;	// add one since it's relative to root
		}
	}

	if ((posix_version < SUSV3) && (xsi_version < 4))
		size = pathmax + 1;		// 加上NULL字符
	else
		size = pathmax;

	if ((ptr = malloc(size)) == NULL)
		err_sys("malloc error for pathname");

	if (sizep != NULL)
		*sizep = size;	// 传址调用分配的内存的长度

	return(ptr);		// 返回指向分配的内存的指针
}

/****************************************************
	文件描述符最大数(用户进程限制, 每个进程最多打开文件数)
    不确定的运行时限制中：最大打开文件数
	实例 2-17 确定文件描述符个数
****************************************************/
/* If OPEN_MAX is indeterminate, this might be inadequate */
long open_max(void)
{
#ifdef OPEN_MAX
	printf("OPEN_MAX defined\n");
	static long openmax = OPEN_MAX;
#else
	printf("OPEN_MAX undefine\n");
	static long openmax = 0;
#endif

	if (open_max == 0)
	{
		errno = 0;
		if (openmax = sysconf(_SC_OPEN_MAX) < 0)
		{
			if (errno == 0)					// 返回不确定的值(返回负值但无错误)
				openmax = OPEN_MAX_GUESS;
			else							// name 参数不是合适的常量(返回负值且参数名称错误)
				perror("sysconf error");
		}
	}
	return(openmax);
}
