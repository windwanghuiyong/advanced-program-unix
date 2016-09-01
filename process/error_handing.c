#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

#include "error_handing.h"

void prt_err(const char *fmt, ...)
{
	char		buf[MAXLINE];
	va_list		ap;

	printf("ai: ");
	va_start(ap, fmt);
	vsnprintf(buf, MAXLINE - 1, fmt, ap);
	snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(errno));
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);		/* flushes all stdio output streams */
	// abort();			/* dump core and terminate */
	va_end(ap);
	// exit(1);
}

/***********************************
    实例 1-8 出错处理
************************************/
int error_handing(void)
{
	fprintf(stderr, "strerror : %s\n", strerror(errno));
	perror("prterror ");
	// exit(0);
	return 0;
}

void errno_specify(void)
{
	// errno = EPERM;		// 1
	errno = ENOENT;		// 2
	// errno = EACCES;		// 13
}
