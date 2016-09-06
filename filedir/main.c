#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "prototype.h"
#include "macro.h"

int main(int argc, char const *argv[]) 
{
	changemode();
	return 0;
}
