#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "macro.h"
#include "prototype.h"
#include "../signals/prototype.h"

#define	read_lock(fd, offset, whence, len)			lock_region((fd), F_SETLK,  F_RDLCK, (offset), (whence), (len))
#define	readw_lock(fd, offset, whence, len)			lock_region((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define	write_lock(fd, offset, whence, len)			lock_region((fd), F_SETLK,  F_WRLCK, (offset), (whence), (len))
#define	writew_lock(fd, offset, whence, len)		lock_region((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define	un_lock(fd, offset, whence, len)			lock_region((fd), F_SETLK,  F_UNLCK, (offset), (whence), (len))
#define is_read_lockable(fd, offset, whence, len)	(lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
#define is_write_lockable(fd, offset, whence, len)	(lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

/****************
	实例 14-5
****************/
int lock_region(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	
	lock.l_type   = type;
	lock.l_start  = offset;
	lock.l_whence = whence;
	lock.l_len    = len;
	
	return(fcntl(fd, cmd, &lock));
}

/****************
	实例 14-6
****************/
pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	
	lock.l_type   = type;
	lock.l_start  = offset;
	lock.l_whence = whence;
	lock.l_len    = len;
	
	if (fcntl(fd, F_GETLK, &lock) < 0)
		perror("fcntl error");
	
	if (lock.l_type == F_UNLCK)
		return 0;
	
	return (lock.l_pid);
}

static void lock_one_byte(const char *name, int fd, off_t offset)
{
	/* 新建一个阻塞版本的独占写锁 */
	if (writew_lock(fd, offset, SEEK_SET, 1) < 0)	// 长度为1个字节
		perror("writew_lock error");
	printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}

int dead_lock(void)
{
	int		fd;
	pid_t	pid;

	/* 创建文件(只写) */
	if ((fd = creat(FILE_NAME, FILE_MODE)) < 0)
	{
		perror("creat error");
		exit(1);
	}
	
	/* 向文件写入2个字节的字符 */
	if (write(fd, "ab", 2) != 2)
	{
		perror("write error");
		exit(1);
	}

	initSigSetHandler();
	
	if ((pid = fork()) < 0) 
	{
		perror("fork error");
		exit(1);
	}
	
	/* child */ 
	else if (pid == 0) 
	{
		lock_one_byte("child", fd, 0);
		tellParent(getppid());
		waitParent();
		lock_one_byte("child", fd, 1);
	}
	
	/* parent */
	else
	{
		lock_one_byte("parent", fd, 1);
		tellChild(pid);
		waitChild();
		lock_one_byte("parent", fd, 0);
	}
	exit(0);
}

int flock_test(void)
{
	int		fd, i, j, rtn;
	pid_t	pid;
	char	char1, char2;
	int		len = sizeof(char);

	/* 创建文件(追加) */
	if ((fd = open(FILE_NAME, FILE_FLAG, FILE_MODE)) < 0)
	{
		perror("create file error");
		exit(1);
	}
	
	/* 创建子进程 */
	if ((pid = fork()) < 0) 
	{
		perror("fork error");
		exit(1);
	}
	
	/* 子进程 */ 
	else if (pid == 0) 
	{
		while (1)
		{
			/* 加锁 */
			rtn = lock_region(fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0);
			if (rtn >= 0)
			{
				printf("child: locked\n");
			
				/* 写入字母 */
				for (i = 0; i < 5; i++)
				{
					char1 = 'a' + i;
					printf("child: %c\n", char1);
					if (write(fd, &char1, len) != len)
					{
						perror("write error");
						exit(1);
					}
					sleep(1);
				}
				write(fd, "\n", 1);
				
				/* 解锁 */
				rtn = lock_region(fd, F_SETLK, F_UNLCK, 0, SEEK_SET, 0);
				if (rtn < 0)
					perror("child: unlock failed");
				else
					printf("child: unlock\n");
				
				sleep(5);
			}
		}
	}
	
	/* 本进程 */
	else
	{
		while (1)
		{
			/* 加锁 */
			rtn = lock_region(fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0);
			if (rtn >= 0)
			{
				printf("parent: locked\n");
			
				/* 写入数字 */
				for (j = 0; j < 5; j++)
				{
					char2 = '1' + j;
					printf("parent: %c\n", char2);
					if (write(fd, &char2, len) != len)
					{
						perror("write error");
						exit(1);
					}
					sleep(1);
				}
				write(fd, "\n", 1);
				
				/* 解锁 */
				rtn = lock_region(fd, F_SETLK, F_UNLCK, 0, SEEK_SET, 0);
				if (rtn < 0)
					perror("parent: unlock failed");
				else
					printf("parent: unlock\n");

				sleep(5);
			}
		}
	}
}
