#include <stdio.h>
#include <string.h>
#include "macros.h"

void macro_test(void)
{
	int a = 10;
	int b = 5;
	printf("suqare a = %d\n", MULTIPLE(a, b));
	
	printf("%s\n", STRING);
	printf("STRING \n");
	PRINT_SQUARE(2);
	char *str = STR_SELF( abcdefg );
	printf("str = %s\n", str);
	STR_ARG(    abc   de   fg        );
	int num9 = 100;
	int num = STR_NUM(9);
	printf("num = %d\n", num);
	int token9 = 9; 
	PASTER(9);
	
	char var1_p[20]; 
	char var2_p[20]; 
	strcpy(var1_p, "aaaa"); 
	strcpy(var2_p, "bbbb"); 
	printf("var1_p = %s\n", var1_p); 
	printf("var2_p = %s\n", var2_p);  
	
	STRCPY(var1, cccc); 
	STRCPY(var2, dddd); 
	printf("var1_p = %s\n", var1_p); 
	printf("var2_p = %s\n", var2_p);  
	
	NAMETYPE(a, int);
	a_int_int = 10;
	printf("a_int_int = %d\n", a_int_int);
	
	return;
}
