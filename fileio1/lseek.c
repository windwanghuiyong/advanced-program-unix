#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/******************************************
	实例 3-1
		测试标准输入能否被设置偏移量
	来源:
		APUE 3.6 Page 54
	调用示例
		./a.out < /etc/passwd
******************************************/
int stdin_offset(void)
{
	off_t		current_pos;

	/* 返回的偏移量可能是负值, 因此判断出错应测试它是否等于 -1, 而非小于 0 */
	if((current_pos = lseek(STDIN_FILENO, 0, SEEK_CUR)) == -1)
	{
		printf("errno = %d\n", errno);
		perror("can't seek");
	}
	else
	{
		printf("stdin current_pos = %lld\n", current_pos);
	}
	return 0;
}
