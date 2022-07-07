#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

// int ta = 20;
//自定义线程参数结构体类型
typedef struct arg_t
{
    int a;
} arg_t;

void func(int i)
{
    for (int n = 2; n < i ; n++)
    {
        if (i % n == 0)
        {
            return;
        }
        else
        {
            printf("prime:%d\n", i);
            return;
        }
    }
}

//定义线程函数　
void *threadFunc(void *arg) // 实际类型为:(arg_t *)
{
    // int i = (int)arg;
    //线程参数arg的使用范例
    int i = ((arg_t *)arg)->a;
    printf("%d\n", i);
    //线程函数退出　即线程结束了
    func(i);
    return NULL;
}

int main()
{
    //创建线程
    pthread_t tid1, tid2;

    arg_t t1 = {10};
    if (pthread_create(&tid1, NULL, threadFunc, (void *)&t1) != 0)
    {
        printf("thread_create err\n");
        return 0;
    }
    else
    {
        printf("线程创建成功! tid=%lx\n", tid1);
    }
    arg_t t2 = {20};
    if (pthread_create(&tid2, NULL, threadFunc, (void *)&t2) != 0)
    {
        printf("thread_create err\n");
        return 0;
    }
    else
    {
        printf("线程创建成功! tid=%lx\n", tid2);
    }

    // 主线程 (main进程)不能先于线程退出
    // 主线程　结束了　所有线程都将结束
    // 等待线程结束
    void *thread_result;
    if (pthread_join(tid1, &thread_result) != 0)
    {
        printf("等待线程失败");
    }
    if (pthread_join(tid2, &thread_result) != 0)
    {
        printf("等待线程失败");
    }
    printf("程序结束...\n");
    return 0;
}