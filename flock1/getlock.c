#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "macros.h"

int main()
{
    struct flock lk;
	int fd, ret;
	
	/*打开文件*/
	fd = open(FILEPATH, O_RDWR);
    if (fd < 0)
    {
        perror("open error");
        exit(1);
    }
    
    /*测试*/
    lk.l_type   = F_RDLCK;		// 读共享锁
    lk.l_whence = SEEK_SET;
    lk.l_start  = 0;
    lk.l_len    = 0;
    
    ret = fcntl(fd, F_GETLK, &lk);
    if (ret < 0)
    {
        perror("get lock error");
        close(fd);
        exit(1);
    }

    printf("getlock: lock is %d\n", lk.l_type);
    
	/*关闭文件*/
    close(fd);
}

 
