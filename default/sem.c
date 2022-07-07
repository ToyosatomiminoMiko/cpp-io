#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//定义一个信号量
sem_t zb,dc;

void * thread1(void *arg)
{
	printf("我是组装主板的!\n");
	for(;;)
	{
		sleep(3);
		printf("组装好了一个主板!\n");
		//释放一个主板信号量　zb++
		sem_post(&zb);
	}
}

void * thread2(void *arg)
{
	printf("我是组装电池的\n");
	for(;;)
	{
		printf("我需要主板\n");
		sem_wait(&zb); // 若zb信号量　不足阻塞等待
		printf("我拿到了一块主板,开始组装电池!\n");
		sleep(1);
		//释放电池信号量
		sem_post(&dc);
	}
}

void * thread3(void *arg)
{
	printf("我是装屏幕的!\n");
	for(;;)
	{
		printf("我需要组装好电池的主板!\n");
		sem_wait(&dc); 
		printf("我拿到了一个组装好电池的主板!\n");
		sleep(2);
		printf("一台手机组装好了!\n");
	}
}



int main()
{
	//初始化信号量
	sem_init(&zb, 0 ,0);
	sem_init(&dc, 0 ,0);

	pthread_t tid;
	pthread_create(&tid, NULL, thread1, NULL);
	pthread_create(&tid, NULL, thread1, NULL);
	pthread_create(&tid, NULL, thread1, NULL);
	pthread_create(&tid, NULL, thread2, NULL);
	pthread_create(&tid, NULL, thread3, NULL);
	pthread_create(&tid, NULL, thread3, NULL);

	pthread_join(tid,NULL);

	return 0;
}

