#include <stdio.h>

extern char **environ;

int print_environ()
{
	int i;

	do
	{
		printf("%s\n", *environ);
	}while(*environ++ != NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("environ[%d] = %s\n", i, environ[i]);
	}
	return 0;
}
