#include "shmdata.h"

int main()
{
	int			shmid;					// 共享内存标识符
	void		*shmaddr = NULL;		// 分配的共享内存的原始首地址
	struct SHM	*shmptr = NULL;			// 指向shmaddr
	char		buffer[BUFSIZ + 1];		// 用于保存输入的文本

	/* 创建共享内存 */
	shmid = shmget((key_t)1234, sizeof(struct SHM), 0666 | IPC_CREAT);
	if(shmid == -1)
		exit(EXIT_FAILURE);

	/* 初始化共享内存 */
	shmaddr = shmat(shmid, (void *)0, 0);
	if(shmaddr == (void *)-1)
		exit(EXIT_FAILURE);
	shmptr = (struct SHM*)shmaddr;

	while (1)
	{
		//数据还没有被读取，则等待数据被读取,不能向共享内存中写入文本
		while(shmptr->written == 1)
		{
			printf("write process: waiting...\n");
			sleep(1);
		}
		//向共享内存中写入数据
		printf("write process: writeing \n");
		fgets(buffer, BUFSIZ, stdin);
		strncpy(shmptr->data, buffer, TEXT_SZ);
		shmptr->written = 1;		// 写完数据，设置written使共享内存段可读
		printf("write process: write finished\n");

		if(strncmp(buffer, "end", 3) == 0)
			break;
	}

	/* 把共享内存从当前进程中分离 */
	if(shmdt(shmaddr) == -1)
	{
		exit(EXIT_FAILURE);
	}
	sleep(2);
	exit(EXIT_SUCCESS);
}
