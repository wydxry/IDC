/*
 * 程序名：demo9.cpp，此程序演示开发框架中PickNumber函数的使用
 * 作者：wydxry
 * 时间：2022.05.26 09:04
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    char str[26];  

    // PickNumber: 从一个字符串中提取出数字的内容，存放到另一个字符串中。
    // 第三个参数：是否包括符号（+和-），true-包括；false-不包括。
    // 第四个参数：是否包括小数点的圆点符号，true-包括；false-不包括。

    STRCPY(str, sizeof str, "iab+12.3xy");
    PickNumber(str, str, false, false);
    printf("str = %s\n", str); // str = 123

    STRCPY(str, sizeof str, "iab+12.3xy");
    PickNumber(str, str, true, false);
    printf("str = %s\n", str); // str = +123

    STRCPY(str, sizeof str, "iab+12.3xy");
    PickNumber(str, str, true, true);
    printf("str = %s\n", str); // str = +12.3

    return 0;
}
