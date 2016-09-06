#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include "macro.h"
#include "prototype.h"

int createTempFile(void)
{
	char	good_template[] = "/tmp/dirXXXXXX";	/* right way */
	char	*bad_template = "/tmp/dirXXXXXX";	/* wrong way*/

	printf("trying to create first temp file...\n");
	make_temp(good_template);
	printf("trying to create second temp file...\n");
	make_temp(bad_template);
	
	return 0;
}

/*********************
	实例 5-12
		创建临时文件
*********************/
int tempFile(void)
{
	char	name[L_tmpnam], line[MAXLINE];
	FILE	*fp;

	printf("%s\n", tmpnam(NULL));		/* first temp name */

	printf("%s\n", tmpnam(name));		/* second temp name */
	printf("%s\n", name);

	if ((fp = tmpfile()) == NULL)		/* create temp file */
		perror("tmpfile error");
	fputs("one line of output\n", fp);	/* write to temp file */
	rewind(fp);							/* then read it back */
	if (fgets(line, sizeof(line), fp) == NULL)
		perror("fgets error");
	fputs(line, stdout);				/* print the line we wrote */

	return 0;
}

/****************************
	实例 5-13
		使用模板创建临时文件
****************************/
void make_temp(char *template)
{
	int			fd;
	struct stat	sbuf;

	if ((fd = mkstemp(template)) < 0)
		perror("can't create temp file");
	printf("temp name = %s\n", template);
	close(fd);
	
	if (stat(template, &sbuf) < 0) 
	{
		if (errno == ENOENT)
			printf("file doesn't exist\n");
		else
			perror("stat failed");
	} 
	else 
	{
		printf("file exists\n");
		unlink(template);
	}
}
