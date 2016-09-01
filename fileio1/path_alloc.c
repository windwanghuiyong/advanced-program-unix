#include <errno.h>
#include <limits.h>
#include "apue.h"

#ifdef PATH_MAX
  static int pathmax = PATH_MAX;    //limits.h中有定义，则使用定义值
#else
  static int pathmax = 0;
#endif

#define SUSV3 200112L

static long posix_version = 0;

#define PATH_MAX_GUESS 1024

char * path_alloc(int *sizep)
{
  char  *ptr;
  int   size;

  if (posix_version == 0)
    posix_version = sysconf(_SC_VERSION);

  if (pathmax == 0)     //limits.h中没有定义，则调用pathconf函数
  {
    errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)    //指定根目录作为第一个参数
    {
      if (errno == 0)       //pathconf指明PATH_MAX不确定，则猜测
        pathmax = PATH_MAX_GUESS;
      else
        err_sys("pathconf error for _PC_PATH_MAX");
    }
  }
  if (posix_version < SUSV3)
    size = pathmax + 1; //加上NULL字符
  else
    size = pathmax;

  if ((ptr = malloc(size)) == NULL)
    err_sys("malloc error for pathname");

  if (sizep != NULL)
    *sizep = size;  //路径名长度

  return(ptr);
}
