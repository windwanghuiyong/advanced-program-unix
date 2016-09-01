#define STRING					"this    is a string"
#define MULTIPLE(x, y)				(x) * (y)
#define PRINT_SQUARE(x)			printf("The square of "#x" is %d.\n", (x) * (x))
#define STR_ARG(str)			printf("the input string is %s.\n", #str)
#define STR_SELF(str)			# str
#define STR_NUM(n)				num ## n
#define PASTER(n)				printf( "token" # n " = %d.\n", token ## n )
#define STRCPY(a, b)			strcpy(a ## _p, #b)
#define NAMETYPE(name, type)	type name ## _ ## type ## _ ## type
void macro_test(void);
