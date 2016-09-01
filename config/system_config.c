#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

static void	pr_sysconf(char *, int);
static void	pr_pathconf(char *, char *, int);

/**************************************************
    实例 2-14 打印所有可能的 sysconf 和 pathconf 值
**************************************************/
int main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: a.out <dirname>");

#ifdef ARG_MAX
	printf("ARG_MAX defined to be %ld\n", (long)ARG_MAX+0);
#else
	printf("no symbol for ARG_MAX\n");
#endif

#ifdef _SC_ARG_MAX
	pr_sysconf("ARG_MAX =", _SC_ARG_MAX);
#else
	printf("no symbol for _SC_ARG_MAX\n");
#endif

#ifdef ATEXIT_MAX
	printf("ATEXIT_MAX defined to be %ld\n", (long)ATEXIT_MAX+0);
#else
	printf("no symbol for ATEXIT_MAX\n");
#endif

#ifdef _SC_ATEXIT_MAX
	pr_sysconf("ATEXIT_MAX =", _SC_ATEXIT_MAX);
#else
	printf("no symbol for _SC_ATEXIT_MAX\n");
#endif

	exit(0);
}

static void pr_sysconf(char *mesg, int name)
{
	long	val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = sysconf(name)) < 0)
	{
		if (errno != 0)
		{
			if (errno == EINVAL)
				fputs(" (not supported)\n", stdout);
			else
				err_sys("sysconf error");
		}
		else
		{
			fputs(" (no limit)\n", stdout);
		}
	}
	else
	{
		printf(" %ld\n", val);
	}
}

static void pr_pathconf(char *mesg, char *path, int name)
{
	long	val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = pathconf(path, name)) < 0)
	{
		if (errno != 0)
		{
			if (errno == EINVAL)
				fputs(" (not supported)\n", stdout);
			else
				err_sys("pathconf error, path = %s", path);
		}
		else
		{
			fputs(" (no limit)\n", stdout);
		}
	}
	else
	{
		printf(" %ld\n", val);
	}
}
