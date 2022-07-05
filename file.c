#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>

char rwx(int i)
{
    char s;
    switch (i)
    {
    case 4:
        s = 'r';
        break;
    case 2:
        s = 'w';
        break;
    case 1:
        s = 'x';
        break;
    default:
        s = '-';
        break;
    }
    return s;
}

int main()
{
    struct stat st; // 待装入
    if (stat("1.txt", &st) == -1)
    // int stat(const char *file_name, struct stat *buf);
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

    printf("权限:%d",
            rwx(st.st_mode & S_IRUSR)/*,
            rwx(st.st_mode & S_IWUSR),
            rwx(st.st_mode & S_IXUSR),
            rwx(st.st_mode & S_IRGRP),
            rwx(st.st_mode & S_IWGRP),
            rwx(st.st_mode & S_IXGRP),
            rwx(st.st_mode & S_IROTH),
            rwx(st.st_mode & S_IWOTH),
            rwx(st.st_mode & S_IXOTH)*/);
    return 0;
}
/*

S_IFMT      0170000     文件类型的位遮罩
S_IFSOCK    0140000     socket
S_IFLNK     0120000     符号链接(symbolic link)
S_IFREG     0100000     一般文件
S_IFBLK     0060000     区块装置(block device)
S_IFDIR     0040000     目录
S_IFCHR     0020000     字符装置(character device)
S_IFIFO     0010000     先进先出(fifo)
S_ISUID     0004000     文件的(set user-id on execution)位
S_ISGID     0002000     文件的(set group-id on execution)位
S_ISVTX     0001000     文件的sticky位
S_IRWXU     00700       文件所有者的遮罩值(即所有权限值)
S_IRUSR     00400       文件所有者具可读取权限
S_IWUSR     00200       文件所有者具可写入权限
S_IXUSR     00100       文件所有者具可执行权限
S_IRWXG     00070       用户组的遮罩值(即所有权限值)
S_IRGRP     00040       用户组具可读取权限
S_IWGRP     00020       用户组具可写入权限
S_IXGRP     00010       用户组具可执行权限
S_IRWXO     00007       其他用户的遮罩值(即所有权限值)
S_IROTH     00004       其他用户具可读取权限
S_IWOTH     00002       其他用户具可写入权限
S_IXOTH     00001       其他用户具可执行权限
*/
