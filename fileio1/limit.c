#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include "macro.h"

/****************************************************
	文件描述符最大数(用户进程限制, 每个进程最多打开文件数)
****************************************************/
long get_open_max(void)
{
#ifdef OPEN_MAX
	printf("OPEN_MAX defined\n");
    static long openmax = OPEN_MAX;
#else
	printf("OPEN_MAX undefine\n");
    static long openmax = 0;
#endif
	
    if (openmax == 0)
    {
        errno = 0;
        if ((openmax = sysconf(_SC_OPEN_MAX)) < 0)
        {
            if (errno == 0)					// 返回不确定的值(返回负值但无错误)
                openmax = OPEN_MAX_GUESS;
            else							// name 参数不是合适的常量(返回负值且参数名称错误)
                perror("sysconf error");
        }
    }
    return(openmax);
}
