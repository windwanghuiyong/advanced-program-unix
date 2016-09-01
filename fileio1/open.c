#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include "macro.h"

/******************
	参数:
		绝对路径
		相对路径
******************/
int creatat(char *dir_path, char *relative_path)
{
    int		dd, fd, flags;
	off_t	offset;

	/* 获取目录的文件描述符 */
	flags = O_RDONLY | O_DIRECTORY | O_CLOEXEC;
    dd = open(dir_path, flags, DIR_MODE);
    if (dd < 0)
    {
        perror("open dir error");
        exit(EXIT_FAILURE);
    }

	/* 使用相对路径打开文件 */
    flags = O_RDWR | O_CREAT | O_TRUNC;
    fd = openat(dd, relative_path, flags, FILE_MODE);
    if (fd < 0)
    {
        perror("openat error");
        exit(EXIT_FAILURE);
    }
	
	/* 关闭文件 */
	close(dd);
    return (fd);
}
