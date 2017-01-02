#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

#define		TEXT_SZ		2048

struct SHM
{
	int		written;			// 同步标志, 0表示可写
	char	data[TEXT_SZ];		// 共享内存数据
};
