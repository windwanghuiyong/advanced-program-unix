#include <stdio.h>
#include <string.h>
#include "macro.h"

/*******************************
    实例 5-4 
		将标准输入复制到标准输出
        每次一个字符的 I/O
********************************/
int mycatc(void)
{
	int		c;

	while ((c = getc(stdin)) != EOF)
	{
		if (putc(c, stdout) == EOF)
			perror("output error");
	}
	if (ferror(stdin))
		perror("input error");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}

/*******************************
    实例 5-5
		将标准输入复制到标准输出
        每次一行的 I/O
********************************/
int mycats(void)
{
	char	buf[MAXLINE];

	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (fputs(buf, stdout) == EOF)
			perror("output error");
	}
	if (ferror(stdin))
		perror("input error");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
