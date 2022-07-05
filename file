#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>

int main()
{
    struct stat st;
    if (stat("01.c", &st) == -1)
    {
        perror("stat err");
        return -1;
    }
    printf("类型:%o\n", st.st_mode & S_IFMT);
    printf("权限:%o\n", st.st_mode & 0x1ff);
    printf("硬链接数:%ld\n", st.st_nlink);
    printf("文件大小:%ld\n", st.st_size);
    struct passwd *pwd = getpwuid(st.st_uid);
    if (pwd)
        printf("文件所有者:%s\n", pwd->pw_name);

    // 文件的修改时间
    struct tm *tm = localtime((const time_t *)&st.st_atim);
    char buf[100];
    sprintf(buf, "%d/%d/%d %02d:%02d:%02d\n", tm->tm_year + 1900,
            tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec);

    printf("文件最后使用时间:%s", buf);
    return 0;
}
