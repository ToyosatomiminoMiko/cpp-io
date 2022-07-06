#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>

#define  ERR(X) do{perror(X);return -1;}while(0)

int pristat(const char *filename)
{
	struct stat buf;
	if(stat(filename, &buf) == -1)
		ERR("stat err");
	mode_t m = buf.st_mode;
	char c; // 打印文件类型
	switch(m & S_IFMT)
	{
		case S_IFSOCK: c = 's'; break;
		case S_IFLNK : c = 'l';	break;
		case S_IFREG : c = '-'; break;
		case S_IFBLK : c = 'b'; break;
		case S_IFDIR : c = 'd'; break;
		case S_IFCHR : c = 'c'; break;
		case S_IFIFO : c = 'p'; break;
	}
	printf("%c",c);
	//打印文件权限
	const char p[] = "xwrxwrxwr";
	for(int i = 8; i >= 0; i--)
	{
		if(m & (1<<i)) printf("%c",p[i]);
		else printf("-");
	}
	printf(" ");
	//链接数
	printf("%ld",buf.st_nlink);
	//文件所有者与所属组
	struct passwd * pwd = getpwuid(buf.st_uid);
	if(pwd)
		printf(" %s",pwd->pw_name);
	pwd = getpwuid(buf.st_gid);
	if(pwd)
		printf(" %s",pwd->pw_name);
	//文件大小
	printf(" %ld ",buf.st_size);
	//文件时间
	struct tm *tm = localtime((const time_t *)&buf.st_atim);
	char buf1[100];
	sprintf(buf1,"%d/%d/%d %02d:%02d:%02d ",tm->tm_year+1900,
				tm->tm_mon+1,tm->tm_mday,
				tm->tm_hour,tm->tm_min,tm->tm_sec);

	printf("%s ",buf1);	
	printf("\033[;32m%s\033[0m\n", filename);
	return 0;
}



int main()
{
	DIR *dp = opendir("./");
	if(dp == NULL)
		ERR("opendir err");
	
	while(1)
	{
		struct dirent * dent = readdir(dp);
		if(dent == NULL)
			break;
		if(dent->d_name[0] != '.')
		{
			pristat(dent->d_name);
		}
	}

	return 0;
}




