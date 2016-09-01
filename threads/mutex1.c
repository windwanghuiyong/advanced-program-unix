#include <stdlib.h>
#include <pthread.h>

/***************************************
	实例 11-10 使用互斥量保护数据结构
***************************************/

struct foo 
{
	int					f_count;	// 引用计数, 用于访问动态分配的对象时不会提现被释放
	pthread_mutex_t		f_lock;
	int					f_id;
	/* ... more stuff here ... */
};

struct foo *foo_alloc (int id)	/* allocate the object */
{
	struct foo *fp;

	if ((fp = malloc(sizeof(struct foo))) != NULL)
	{
		fp->f_count = 1;	// 初始化引用计数
		fp->f_id = id;
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0){
			free(fp);
			return(NULL);
		}
		/* ... continue initialization ... */
	}
	return (fp);
}

void foo_hold(struct foo *fp)	/* add a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;						// 使用对象前, 引用计数+1
	pthread_mutex_unlock(&fp->f_lock);
}

void foo_release(struct foo *fp)	 /* release a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	--fp->f_count;
	pthread_mutex_unlock(&fp->f_lock);
	
	if (fp->f_count == 0)				// 使用对象后, 引用计数-1
	{
		pthread_mutex_destory(&fp->f_lock);	// 最后一个引用被释放
		free(fp);
	}
}
