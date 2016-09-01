#include "api.h"
#include <setjmp.h>

static void f1(int, int, int, int);
static void f2(void);

static jmp_buf jmpbuffer;
static int globalVal;

int main(void)
{
	auto int     autoVal;
	register int registerVal;
	volatile int volatileVal;
	static int   staticVal;

	globalVal   = 1;
	autoVal     = 2;
	registerVal = 3;
	volatileVal = 4;
	staticVal   = 5;

	if (setjmp(jmpbuffer) != 0)
	{
		printf("after longjmp:\n");
		printf(" globalVal = %d \n autoVal = %d \n registerVal = %d \n volatileVal = %d \n staticVal = %d \n", \
			globalVal, autoVal, registerVal, volatileVal, staticVal);
		exit (0);
	}

	globalVal   = 11;
	autoVal     = 12;
	registerVal = 13;
	volatileVal = 14;
	staticVal   = 15;

	f1 (autoVal, registerVal, volatileVal, staticVal);
	exit (0);
}

static void f1(int i, int j, int k, int l)
{
	printf("in f1():\n");
	printf(" globalVal = %d \n autoVal = %d \n registerVal = %d \n volatileVal = %d \n staticVal = %d \n", \
		globalVal, i, j, k, l);

	f2();
}

static void f2(void)
{
	longjmp(jmpbuffer, 1);
}
