#include "api.h"
#include <dirent.h>

/***********************************
	实例 1-3 ls(1)命令的简要实现
***********************************/
int main(int argc, char *argv[])
{
	DIR *dirp;
	struct dirent *direntp;

	if (argc != 2)
		err_quit("usage: command_name directory_name");

	if ((dirp = opendir(argv[1])) == NULL)
		err_sys("can't open %s", argv[1]);

	while((direntp = readdir(dirp)) != NULL)
		printf("%s\n", direntp->d_name);

	closedir(dirp);
	exit(0);
}
