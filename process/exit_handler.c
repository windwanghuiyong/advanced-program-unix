#include <stdio.h>
#include <stdlib.h>

#include "error_handing.h"
#include "create_process.h"

static void my_exit1(void);
static void my_exit2(void);
static void my_exit3(void);

/**************************
    实例 7-3 终止处理程序
**************************/
int register_exit_handler(void)
{
    /*登记终止处理程序*/
    if (atexit(my_exit3))
        prt_err("can't register my_exit3");

    if (atexit(my_exit2))
        prt_err("can't register my_exit1");

    if (atexit(my_exit1))
        prt_err("can't register my_exit1");

    printf("main is done\n");
    return 0;   // 等价于 exit(0);
}

static void my_exit1(void)
{
    printf("first exit handler\n");
}

static void my_exit2(void)
{
    printf("second exit handler\n");
}

static void my_exit3(void)
{
    printf("third exit handler\n");
}

void test(void)
{
	create_process();
	errno_specify();
	error_handing();
	prt_err("error string = %s %d %d ", "errstr", 1, 2);
	register_exit_handler();
}
