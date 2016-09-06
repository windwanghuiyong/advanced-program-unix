#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int file_type(char const *filepath)
{
	int         i;
	struct stat buf;
	char        *ptr;
	
	printf("%s: ", filepath);

	if (lstat(filepath, &buf) < 0)
	{
		perror("lstat error\n");
		exit(1);
	}

	if (S_ISREG(buf.st_mode))
		ptr = "regular";
	else if (S_ISDIR(buf.st_mode))
		ptr = "directory";
	else if (S_ISCHR(buf.st_mode))
		ptr = "character special";
	else if (S_ISBLK(buf.st_mode))
		ptr = "block special";
	else if (S_ISFIFO(buf.st_mode))
		ptr = "FIFO";
	// else if (S_ISLINK(buf.st_mode))
	// 	ptr = "symbolic link";
	else if (S_ISSOCK(buf.st_mode))
		ptr = "socket";
	else
		ptr = "unknown mode";

	printf("%s\n", ptr);
	
 	return 0;
}
