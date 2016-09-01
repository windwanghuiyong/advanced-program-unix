#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "macro.h"

/*******************************
    实例 1-4 3-5 
		将标准输入复制到标准输出
        不带缓冲的 I/O
********************************/
int mycat()
{
	int n;
	char buf[BUFFSIZE];

	printf("ssize = %d\n", _POSIX_SSIZE_MAX);

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			perror("write error");

	if (n < 0)
		perror("read error");
	return 0;
}
