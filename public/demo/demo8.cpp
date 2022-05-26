/*
 * 程序名：demo8.cpp，此程序演示开发框架中字符串大小写转换函数的使用
 * 作者：wydxry
 * 时间：2022.05.26 09:04
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    char str1[31]; // C

    STRCPY(str1, sizeof str1, "12abz45ABz8西施。");
    ToUpper(str1);
    printf("str = %s\n", str1); // str = 12ABZ45ABZ8西施。

    STRCPY(str1, sizeof str1, "12abz45ABz8西施。");
    ToLower(str1);
    printf("str = %s\n", str1); // str = 12abz45abz8西施。

    string str2; // C++

    str2 = "12abz45ABz8西施。";
    ToUpper(str2);
    printf("str = %s\n", str2.c_str()); // str = 12ABZ45ABZ8西施。
    cout << "str = " << str2 << endl;   // str = 12ABZ45ABZ8西施。

    str2 = "12abz45ABz8西施。";
    ToLower(str2);
    printf("str = %s\n", str2.c_str()); // str = 12abz45abz8西施。
    cout << "str = " << str2 << endl;   // str = 12abz45abz8西施。

    return 0;
}
