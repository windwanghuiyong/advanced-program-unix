#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "prototype.h"

char	Buffer[500000];

/**************************
	实例 14-1
		长的非阻塞 write
**************************/
int nonblock_write(void)
{
	int		readbytes, writebytes;
	char	*ptr;

	/* 从标准输入一次性读取很长的数据 */
	readbytes = read(STDIN_FILENO, Buffer, sizeof(Buffer));
	fprintf(stderr, "readbytes = %d\n", readbytes);
	
	/* 
	** 将标准输出设置为非阻塞
	** 若标准输出是普通文件, 则写一次全部写完
	** 若标准输出是终端, 则多次写或返回出错
	*/ 
	set_flag(STDOUT_FILENO, O_NONBLOCK);	/* set nonblocking */

	ptr = Buffer;
	while (readbytes > 0) 
	{
		errno = 0;
		
		/* 将读到的数据写到标注输出 */
		writebytes = write(STDOUT_FILENO, ptr, readbytes);
		fprintf(stderr, "writebytes = %d, errno = %d\n", writebytes, errno);
		
		/* 成功写入, 则更新位置继续写 */
		if (writebytes > 0) 
		{
			ptr += writebytes;
			readbytes -= writebytes;
		}
	}

	cls_flag(STDOUT_FILENO, O_NONBLOCK);	/* clear nonblocking */

	return 0;
}
