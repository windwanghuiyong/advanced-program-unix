#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include "macro.h"

/****************************************
	实例 3-2
		创建一个具有空洞的文件
	调用示例
		./a.out; ls -ls file_hole.txt
****************************************/
int file_hole(void)
{
	int				fd;
	off_t			offset;
	static char		buf1[] = "before hole\n";
	static char		buf2[] = "after hole";
	unsigned int	len1 = sizeof(buf1);
	unsigned int	len2 = sizeof(buf2);

	if ((fd = creat(FILE_HOLE, FILE_MODE)) < 0)
		perror("file creat error");

	if (write(fd, buf1, len1) != len1)
		perror("buf1 write error");

	if ((offset = lseek(fd, 0x4000, SEEK_SET)) == -1)
		perror("lseek error");

	if (write(fd, buf2, len2) != len2)
		perror("buf2 write error");		// 如磁盘空间不足

	return 0;
}

/*******************
	文件偏移量位宽
*******************/
void offset_bits(void)
{
	// printf("_FILE_OFFSET_BITS = %d\n", _FILE_OFFSET_BITS);		// 32(4字节)
	printf("off_t width = %zu Bytes\n", sizeof(off_t));			// 8 字节
	printf("%ld\n", sysconf(_SC_V6_ILP32_OFF32));
	printf("%ld\n", sysconf(_SC_V6_ILP32_OFFBIG));
	printf("%ld\n", sysconf(_SC_V6_LP64_OFF64));
	// printf("%ld\n", sysconf(_SC_V6_LP64_OFFBIG));
}
