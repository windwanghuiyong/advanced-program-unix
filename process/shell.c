#include "api.h"
#include <sys/wait.h>

/***********************************
    实例 1-7 shell 基本实现
************************************/
int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");								// print prompt
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;			// replace newlin with null
        if (pid = fork() < 0){
            err_sys("fork error");
        } else if (pid == 0) {					// child fork 函数对子进程返回0
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

		/*父进程等待子进程终止*/
        if (pid = waitpid(pid, &status, 0) < 0)	// parent fork 函数对父进程返回子进程的 pid
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}
