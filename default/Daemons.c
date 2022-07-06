#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define ERR(X) do{perror(X); exit(0);}while(0)

//创建一个守护进程

int main()
{
	//1.创建子进程　杀死父进程
	pid_t pid = fork();
	if(pid < 0 ) 
	  ERR("fork err");
	if(pid > 0) exit(0);
	
	//2.创建新会话 脱离终端会话
	setsid();
	//3.重设文件权限掩码　为0
	umask(0);
	//4.修改工作目录为 /
	chdir("/");
	//5.关闭不需要的文件描述符
	close(0);
	close(1);
	close(2);
	//守护进程创建完毕
	
	//日志
	int a = 0;
	char buf[100];
	while(1)
	{
		int fd = open("/var/log/mylog",O_WRONLY| O_CREAT| O_APPEND);
		sprintf(buf,"a=%d\n",a++);
		write(fd,buf,strlen(buf));
		close(fd);
		sleep(1);
	}

	return 0;
}

