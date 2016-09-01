#include <stdio.h>
#include <string.h>
#include <unistd.h>

/***********************************
    实例 1-5 将标准输入复制到标准输出
        标准 I/O
************************************/
int copy_buffer(void)
{
    int c;

    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            perror("output error");

    if (ferror(stdin))
        perror("input error");
	return 0;
}
