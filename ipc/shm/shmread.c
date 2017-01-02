#include "shmdata.h"

int main()
{
	int			shmid;					// 共享内存标识符
	void		*shmaddr = NULL;		// 分配的共享内存的原始首地址
	struct SHM	*shmptr = NULL;			// 指向shmaddr

	/* 创建共享内存 */
	shmid = shmget((key_t)1234, sizeof(struct SHM), 0666 | IPC_CREAT);
	if(shmid == -1)
		exit(EXIT_FAILURE);

	/* 初始化共享内存 */
	shmaddr = shmat(shmid, (void *)0, 0);
	if(shmaddr == (void *)-1)
		exit(EXIT_FAILURE);
	shmptr = (struct SHM*)shmaddr;
	shmptr->written = 0;

	while (1)
	{
		/* 共享内存可读(已有内容写入) */
		if(shmptr->written)
		{
			printf("read process: reading %s", shmptr->data);
			sleep(rand() % 3);
			shmptr->written = 0;
			printf("read process: read finished\n");

			if(strncmp(shmptr->data, "end", 3) == 0)
				break;
		}
		/* 不能读取数据(有其他进程在写数据) */
		else
		{
			printf("read process: blocked\n");
			sleep(1);
		}
	}

	/* 把共享内存从当前进程中分离 */
	if(shmdt(shmaddr) == -1)
	{
		exit(EXIT_FAILURE);
	}

	/* 删除共享内存 */
	if(shmctl(shmid, IPC_RMID, 0) == -1)
	{
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
