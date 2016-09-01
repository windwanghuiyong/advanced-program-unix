#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "prototype.h"
#include "macro.h"

int read_write(void)
{
	int			fd;
	int			oflag;
	char		writebuf[BUFFSIZE];
	char		readbuf[BUFFSIZE];
	off_t		pos;
	size_t		len;
	mode_t		mode;
	ssize_t		nbytes;
	
	/* 打开文件 */
	fd = openat(AT_FDCWD, FILE_NAME, FILE_FLAG, FILE_MODE);
	if (fd < 0)
		perror("openat error");
	
	/* 写入文件(添加到文件末尾) */
	strcpy(writebuf, "write1\n");
	len = strlen(writebuf);
	nbytes = write(fd, writebuf, len);	// 添加到文件尾
	if (nbytes != len)
		perror("write error");
	
	/* 写入文件(添加到文件末尾) */
	strcpy(writebuf, "write2\n");
	len = strlen(writebuf);
	pos = lseek(fd, 0, SEEK_SET);
	nbytes = write(fd, writebuf, len);	// 由于 O_APPEND 标志, 即使设置了文件偏移量, 写入时依然添加到文件末尾
	if (nbytes != len)
		perror("write error");
	
	/* 写入文件(覆盖文件指定位置) */
	cls_flag(fd, O_APPEND);
	strcpy(writebuf, "write3\n");
	len = strlen(writebuf);
	pos = lseek(fd, 3, SEEK_SET);
	nbytes = write(fd, writebuf, len);	// 写入到指定位置
	if (nbytes != len)
		perror("write error");
	
	/* 读取文件 */
	len = lseek(fd, 0, SEEK_END);		// 还有其他方式来获取文件长度
	pos = lseek(fd, 0, SEEK_SET);
	nbytes = read(fd, readbuf, len);
	if (nbytes != len)
		perror("read error");
	else
		printf("readbuf:\n%s\n", readbuf);
	
	/* 关闭文件 */
	close(fd);
	
	return 0;
}
