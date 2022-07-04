/**
 * @file 1.c
 * @author ToyosatomiminoMiko
 * @brief 立即回显
 * @version 0.1
 * @date 2022-07-04
 */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>


int getch(void)
{
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
int main()
{
    system("clear");
    int c;
    while ((c = getch()) != '\n') //从控制台流中读取字符，直到按回车键结束
    {
        system("clear");
        printf("%d", c); //输出读取内容
    }
}
