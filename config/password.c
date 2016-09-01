#include <pwd.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

struct passwd *getpwnam(const char *);

int main (int argc, char const *argv[])
{
	getpwnam(argv[0]);
	return 0;
}

struct passwd *getpwnam(const char *name)
{
	struct passwd *ptr;

	setpwent();
	while ((ptr = getpwent()) != NULL)
	{
		if (strcmp(name, ptr->pw_name) == 0)
		{
			printf("dir = %s\n", ptr->pw_dir);
			break;
		}
	}
	endpwent();
	return (ptr);
}
