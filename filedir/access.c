#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/*********************
	实例 4-8
		文件权限测试
*********************/
int access_test(char const *pathname)
{
	printf("F_OK = %x\n", F_OK);
	printf("R_OK = %x\n", R_OK);
	printf("W_OK = %x\n", W_OK);
	printf("X_OK = %x\n", X_OK);
	
	/* 文件存在 */
	if (access(pathname, F_OK) < 0)
		perror("file not exist");
	else
		puts("file exist OK");
	
	/* 实际用户对该文件具有读权限 */
	if (access(pathname, R_OK) < 0)
		perror("read access error");
	else
		puts("read access OK");
	
	/* 以只读方式打开文件 */
	if (open(pathname, O_RDONLY) < 0)
		perror("open error");
	else
		puts("open for reading OK");
	
	return (0);
}
