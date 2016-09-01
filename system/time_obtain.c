#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

/**********************************
	实例 6-11 使用 strftime 函数
**********************************/
void time_obtain()
{
	time_t         cal_time;	// 日历时间(s)
	struct timeval val_time;	// 日历时间(ns)
	struct tm     *brk_time;	// 分解时间
	struct timespec tsp;
	char buf[128];
	int rtn;

	time(&cal_time);
	printf("cal_time = %lds\n", cal_time);

	gettimeofday(&val_time, NULL);
	printf("val_time = %lds, %dns\n", val_time.tv_sec, val_time.tv_usec);

	brk_time = gmtime(&cal_time);
	printf("UTC_time =  %d-%d-%d %d:%d:%d\n", \
		brk_time->tm_year + 1900, brk_time->tm_mon + 1, brk_time->tm_mday, \
		brk_time->tm_hour, brk_time->tm_min, brk_time->tm_sec);

	printf("cal_time1 = %lds\n", mktime(brk_time));

	brk_time = localtime(&cal_time);
	printf("Local_time =  %d-%d-%d %d:%d:%d\n", \
		brk_time->tm_year + 1900, brk_time->tm_mon + 1, brk_time->tm_mday, \
		brk_time->tm_hour, brk_time->tm_min, brk_time->tm_sec);

	printf("cal_time2 = %lds\n", mktime(brk_time));

	rtn = strftime(buf, 128, "year = %Y month = %B day = %d week = %A", brk_time);
	printf("rtn =%d %s\n",rtn, buf);

	strcpy(buf,"2001-02-03 4:5:6");
	strptime(buf, "%F %T", brk_time);
	printf("str_time =  %d-%d-%d %d:%d:%d\n", \
		brk_time->tm_year + 1900, brk_time->tm_mon + 1, brk_time->tm_mday, \
		brk_time->tm_hour, brk_time->tm_min, brk_time->tm_sec);
}
