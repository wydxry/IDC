/*
 * 程序名：demo3.cpp，此程序演示开发框架中STRCAT函数的使用。
 * 作者：wydxry
 * 时间：2022.05.25 21:51
 */

#include "../_public.h"

int main(int argc, char *argv[])
{
    char str[11];   // 字符串str的大小是11字节。
    STRCPY(str, sizeof(str), "www");  
    printf("str = %s\n", str);        // str = www

    STRCAT(str, sizeof(str), ".fr");  // str原有的内容加上待追加的内容没有超过str可以存放的大小。
    printf("str = %s\n", str);        // str = www.fr

    STRCAT(str, sizeof(str), "eecplus.net");  // str原有的内容加上待追加的内容超过了str可以存放的大小。
    printf("str = %s\n",str);                // str = www.freecp
    return 0;
}
