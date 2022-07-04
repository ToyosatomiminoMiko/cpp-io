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
    int table[12][12] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},

    };
    system("clear");
    int c;
    int player[2] = {0, 0};
    while ((c = getch()) != '\n') //从控制台流中读取字符，直到按回车键结束
    {
        system("clear");
        
        for (int i = 0; i < 12; i++)
        {
            
            for (int j = 0; j < 12; j++)
            {

                if (i == player[0] && j == player[1])
                {
                    printf("@");
                }
                else if (table[i][j] == 1)
                {
                    printf("#");
                }
                else if (table[i][j] == 0)
                {
                    printf(" ");
                }
            }
            
            printf("\n");
        }
        
        // printf("%d", c); //输出读取内容
        //  print(p);
        printf("(%d,%d)", player[0], player[1]);
        switch (c)
        {
        case 119:
            // printf("w");
            player[0] -= 1;
            continue;
        case 115:
            //printf('s');
            player[0] += 1;
            continue;
        case 97:
            // printf("a");
            player[1] -= 1;
            continue;
        case 100:
            // printf("d");
            player[1] += 1;
            continue;
        default:
            continue;
        };
    }
}
