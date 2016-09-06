#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "macro.h"

/**************************
	实例 4-9
		文件模式创建屏蔽字
**************************/
int createmode(void)
{
	mode_t	rwxrwxrwx = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH;
	mode_t	rw_rw_rw_ = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	mode_t	___rw_rw_ = S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	
	/* 无权限屏蔽创建文件 */
	umask(0);
	if (creat(TMP_FILE_ONE, rwxrwxrwx) < 0)
		perror("creat error");
	
	/* 带权限屏蔽创建文件 */
	umask(___rw_rw_);
	if (creat(TMP_FILE_TWO, rw_rw_rw_) < 0)
		perror("creat error");
	
	return 0;
}

/******************************
	实例 4-12
		修改现有文件的访问权限
******************************/
int changemode(void)
{
	struct stat		statbuf;

	/* turn on set-group-ID and turn off group-execute */
	if (stat(TMP_FILE_ONE, &statbuf) < 0)
		perror("stat error");
	if (chmod(TMP_FILE_ONE, (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		perror("chmod error");

	/* set absolute mode to "rw-r--r--" */
	if (chmod(TMP_FILE_TWO, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
		perror("chmod error");

	return 0;
}
