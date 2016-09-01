#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "macros.h"

int main()
{
    struct flock lk;
	int fd, ret;
	
	/*打开文件*/
	fd = open( FILEPATH, O_CREAT | O_RDWR, S_IRWXU | S_IRGRP | S_IWGRP | S_IRWXO);
    if (fd < 0)
    {
        perror("open file error");
        exit(1);
    }
    
    /*上锁*/
    lk.l_type   = F_WRLCK;		// 写排斥锁
    lk.l_whence = SEEK_SET;		// 从文件开始处加锁	
    lk.l_start  = 0;
    lk.l_len    = 0;

    ret = fcntl(fd, F_SETLK, &lk);
    if (ret < 0)
    {
        perror("set lock error");
        close(fd);
        exit(1);
    }
    puts("setlock: locked");
    
	/*挂起*/
    sleep(100);
    
    /*解锁*/
	lk.l_type   = F_UNLCK;
	lk.l_whence = SEEK_SET;
	lk.l_start  = 0;
	lk.l_len    = 0;
	
	ret = fcntl(fd, F_SETLK, &lk);
	if (ret < 0)
	{
	    perror("unlock error");
	}
	puts("setlock: unlocked");
	
	/*关闭文件*/
    close(fd);
}
