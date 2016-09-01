#include <pwd.h>
// #include <shadow.h>
#include <grp.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

struct passwd *getpwname(const char *name);


int main(int argc, char const *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		struct passwd *ptr = getpwname(argv[i]);
		printf("%s\n", ptr->pw_name);
		printf("%s\n", ptr->pw_passwd);
		printf("%d\n", ptr->pw_uid);
		printf("%d\n", ptr->pw_gid);
		printf("%s\n", ptr->pw_gecos);
		printf("%s\n", ptr->pw_dir);
		printf("%s\n", ptr->pw_shell);
		printf("%s\n", ptr->pw_class);
		printf("%ld\n", ptr->pw_change);
		printf("%ld\n", ptr->pw_expire);
	}
	return 0;
}

/**********************************************
	实例 6-2 通过用户名获取该用户的 passwd 结构体
**********************************************/
struct passwd *getpwname(const char *name)
{
	struct passwd *ptr;

	setpwent();
	while ((ptr = getpwent()) != NULL)
	{
		if(strcmp(name, ptr->pw_name) == 0)
			break;
	}
	endpwent();
	return(ptr);
}
