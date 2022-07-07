#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

//int ta = 20;
//自定义线程参数结构体类型
typedef struct arg_t
{
	int a;
	char s[20];
	//....
}arg_t;

//定义线程函数　
void * threadFunc(void * arg)
{
	//int i = (int)arg;
	//线程参数arg的使用范例
	int i = ((arg_t *)arg ) -> a;

	printf("线程运行起来了!,%s\n", ((arg_t *)arg ) ->s);
	for(; i <   ((arg_t *)arg ) -> a + 5 ; i++ )
	{
		printf("in thread i =%d\n",i);
		sleep(1);
	}
	//线程函数退出　即线程结束了
	int *ret = malloc(sizeof(int));
	*ret = i;
	return ret;
	pthread_exit(ret);
}


int main()
{
	//创建线程
	pthread_t tid1,tid2;
	//ta = 10;
	arg_t t1 = {10,"hello thread1"};
	if( pthread_create(&tid1, NULL, threadFunc, (void *)&t1) != 0)
	{
		printf("thread_create err\n");
		return 0;
	}
	else 
	  printf("线程创建成功! tid=%lx\n",tid1);
	//ta = 30;
	arg_t t2 = {20, "hello thread2"};
	if( pthread_create(&tid2, NULL, threadFunc, (void*)&t2) != 0)
	{
		printf("thread_create err\n");
		return 0;
	}
	else 
	  printf("线程创建成功! tid=%lx\n",tid2);

	// 主线程 (main进程)不能先于线程退出
	// 主线程　结束了　所有线程都将结束
	// 等待两个线程结束
	int *ret;
#if 0
	pthread_join(tid1,(void **)&ret);
	printf("线程tid1结束了 %d\n",*ret);
	free(ret);
#endif
	
	//强制结束指定线程
	sleep(2);
	pthread_cancel(tid1);

	pthread_join(tid2,(void **)&ret);
	printf("线程tid2结束了 %d\n",*ret);
	free(ret);
	
	return 0;
}


