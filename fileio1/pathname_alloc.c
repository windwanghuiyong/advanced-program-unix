#include <errno.h>
#include <limits.h>


/******************************************
    不确定的运行时限制中：路径名长度
	实例 2-16 为路径名动态的分配空间
******************************************/
#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif
static long posix_version = 0;
static long xsi_version = 0;
/* If PATH is indeterminate, no guarantee this is adequate */
#define PATH_MAX_GUSS 1024

char *path_alloc(size_t *sizep) /*also return allocated size, if nonnull */
{
	char *ptr;
	size_t size;

	if (posix_version == 0)
		posix_version = sysconf(_SC_VERSION);

	if (xsi_version == 0)
		xsi_version = sysconf(_SC_XOPEN_VERSION);

	if (pathmax == 0)	// first time through
	{
		errno = 0;
		if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)	// 基于根目录的相对路径的最大长度
		{
			if (errno == 0)
				pathmax = PATH_MAX_GUSS;	// it's indeterminate
			else
				err_sys("pathconf error for _PC_PATH_MAX");
		}
		else
		{
			pathmax++;	// add one since it's relative to root
		}
	}

	if ((posix_version < 200112L) && (xsi_version < 4))
		size = pathmax + 1;
	else
		size = pathmax;

	if ((ptr = malloc(size)) == NULL)
		err_sys("malloc error for pathname");

	if (sizep != NULL)
		*sizep = size;	// 传址调用分配的内存的长度

	return(ptr);		// 返回指向分配的内存的指针
}

/******************************************
    不确定的运行时限制中：最大打开文件数
	实例 2-17 确定文件描述符个数
******************************************/
#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif
/* If OPEN_MAX is indeterminate, this might be inadequate */
#define OPEN_MAX_GUESS 256

long open_max(void)
{
	if (open_max == 0)
	{
		errno = 0;
		if (openmax = sysconf(_SC_OPEN_MAX) < 0)
		{
			if (errno == 0)
				openmax = OPEN_MAX_GUESS;
			else
				err_sys("sysconf error for _SC_OPEN_MAX");
		}
	}
	return(openmax);
}
