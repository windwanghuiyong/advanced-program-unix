#include <stdio.h>
#include "prototype.h"
#include "macro.h"

int main(int argc, char const *argv[]) 
{
	int fd;
	
	fd = creatat("/mnt/hgfs/OneDrive/Books/advanced_program_unix/fileio", FILE_NAME);
	write(fd, "aaa", 3);
	return 0;
}
