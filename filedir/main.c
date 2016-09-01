#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "prototype.h"
#include "macro.h"

int main(int argc, char const *argv[]) 
{
	printf("S_IFMT = %x\n", S_IFMT);
	printf("S_IFREG = %x\n", S_IFREG);
	printf("S_IFDIR = %x\n", S_IFDIR);
	// printf("S_IFLINK = %x\n", S_IFLINK);
	printf("S_IFBLK = %x\n", S_IFBLK);
	printf("S_IFCHR = %x\n", S_IFCHR);
	printf("S_IFSOCK = %x\n", S_IFSOCK);
	// printf("S_IFFIFO = %x\n", S_IFFIFO);

	file_type(argv[1]);
	return 0;
}
