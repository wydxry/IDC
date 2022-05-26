/*
 * 程序名：demo7.cpp，此程序演示开发框架中删除字符串左、右、两边指定字符的使用
 * 作者：wydxry
 * 时间：2022.05.26 09:04
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    char str[31];

    STRCPY(str, sizeof str, " wydxry  ");
    printf("origin str = %s.\n", str); // origin str =  wydxry  .
    DeleteLChar(str, ' '); // 删除str左边的空格
    printf("str = %s.\n", str);        // str = wydxry  .

    STRCPY(str, sizeof str, " wydxry  ");
    printf("origin str = %s.\n", str); // origin str =  wydxry  .
    DeleteRChar(str, ' '); // 删除str右边的空格
    printf("str = %s.\n", str);        // str =  wydxry.

    STRCPY(str, sizeof str, " wydxry  ");
    printf("origin str = %s.\n", str); // origin str =  wydxry  .
    DeleteLRChar(str,' '); // 删除str两边的空格
    printf("str = %s.\n", str);        // str = wydxry.

    return 0;
}
