#include <stdio.h>
#include <pthread.h>
int a,b;

//定义一个互斥锁
pthread_mutex_t mutex; 

void * thread(void *arg)
{
	for(;;)
	{
		//上锁
		pthread_mutex_lock(&mutex);
		a +=1;
		b +=1;
		//解锁
		pthread_mutex_unlock(&mutex);
	}
}


int main()
{
	a = 0; b = 0;
	//初始化锁
	pthread_mutex_init(&mutex,NULL);

	pthread_t tid;
	pthread_create(&tid, NULL, thread , NULL);

	for(;;)
	{
		//上锁
		pthread_mutex_lock(&mutex);

		if(a != b) printf("%d,%d\n",a,b);
		//解锁
		pthread_mutex_unlock(&mutex);
	}
	return 0;
}



