#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

int lock_set(int, int);

int main(void)
{
	int fd;
 
	fd = open("test.txt", O_RDWR|O_CREAT, 0644);
	if(fd < 0)
	{
		perror("Open file error!!\n");
		exit(1);
	}
 
	lock_set(fd, F_WRLCK);		// 独占性写锁
	getchar();
 
	lock_set(fd, F_UNLCK);		// 解锁一个区域
	getchar();
  
	close(fd);
	exit(0);
}

int lock_set(int fd, int type)
{
	struct flock lk;
	
	/* 初始化记录锁 */
	lk.l_type   = type;
	lk.l_start  = 0;
	lk.l_whence = SEEK_SET;
	lk.l_len    = 0;
	lk.l_pid    = -1;

	/* 获取记录锁 */
	fcntl(fd, F_GETLK, &lk);
	if(lk.l_type == F_RDLCK)
		printf("Read lock already set by %d\n",  lk.l_pid);
	else if(lk.l_type == F_WRLCK)
		printf("Write lock already set by %d\n", lk.l_pid);
	else if (lk.l_type == F_UNLCK)
		printf("Any lock has not set by %d\n",   lk.l_pid);
	
	printf("testlock: type = %u\n", lk.l_type);
	
	/* 指定记录锁类型 */
	lk.l_type = type;
	
	if((fcntl(fd, F_SETLKW, &lk)) < 0)
	{
		perror("Lock failed");
		return 1;
	}
	switch(lk.l_type)
	{
	case F_RDLCK:
		printf("Read lock set by %d\n",  getpid());
		break;
	case F_WRLCK:
		printf("Write lock set by %d\n", getpid());
		break;
	case F_UNLCK:
		printf("Release lock by %d\n",   getpid());
		return 1;
		break;
	default:
		break;
	}
	return 0;
}
