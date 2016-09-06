#include <stdio.h>
#include <string.h>
#include <fcntl.h>﻿
#include <sys/wait.h>
#include "prototype.h"
#include "macro.h"

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
	lcok.l_len    = len;
	
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
	lcok.l_len    = len;
	
	if (fcntl(fd, F_GETLK, &lock) < 0)
		perror("fcntl error");
	
	if (lock.l_type == F_UNLCK)
		return 0;
	
	return (lock.l_pid);
}

static void lockabyte(const char *name, int fd, off_t offset)
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
		perror("creat error");
	
	/* 向文件写入2个字节的字符 */
	if (write(fd, "ab", 2) != 2)
		perror("write error");

	TELL_WAIT();
	if ((pid = fork()) < 0) {
		perror("fork error");
	} else if (pid == 0) {			/* child */
		lockabyte("child", fd, 0);
		TELL_PARENT(getppid());
		WAIT_PARENT();
		lockabyte("child", fd, 1);
	} else {						/* parent */
		lockabyte("parent", fd, 1);
		TELL_CHILD(pid);
		WAIT_CHILD();
		lockabyte("parent", fd, 0);
	}
	exit(0);
}
