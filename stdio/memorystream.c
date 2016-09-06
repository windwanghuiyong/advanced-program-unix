#include <stdio.h>
#include <string.h>
#include "macro.h"

int openMemStream(void)
{
	FILE	*fp;
	char	buf[BUFSIZE];

	memset(buf, 'a', BUFSIZE-2);
	buf[BUFSIZE-2] = '\0';
	buf[BUFSIZE-1] = 'X';
	
	if ((fp = fmemopen(buf, BUFSIZE, "w+")) == NULL)
		perror("fmemopen failed");
	
	printf("initial buffer contents: %s\n", buf);
	fprintf(fp, "hello, world");
	printf("before flush: %s\n", buf);
	fflush(fp);
	printf("after fflush: %s\n", buf);
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	memset(buf, 'b', BUFSIZE-2);
	buf[BUFSIZE-2] = '\0';
	buf[BUFSIZE-1] = 'X';
	fprintf(fp, "hello, world");
	fseek(fp, 0, SEEK_SET);
	printf("after  fseek: %s\n", buf);
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	memset(buf, 'c', BUFSIZE-2);
	buf[BUFSIZE-2] = '\0';
	buf[BUFSIZE-1] = 'X';
	fprintf(fp, "hello, world");
	fclose(fp);
	printf("after fclose: %s\n", buf);
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	return(0);
}
