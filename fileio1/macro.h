/* 文件访问权限 */
#define		FILE_FLAG			(O_RDWR | O_CREAT | O_APPEND)
#define		FILE_MODE			(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define		DIR_MODE			(S_IRUSR | S_IWUSR | S_IXUSR)
#define		FILE_HOLE			"test.txt"
#define		FILE_NAME			FILE_HOLE
#define		BUFFSIZE			4096
#define		OPEN_MAX_GUESS		256
#define		PATH_MAX_GUESS		1024
#define		SUSV3				200112L
