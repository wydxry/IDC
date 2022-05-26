/*
 * 程序名：demo12.cpp，此程序演示开发框架中字符串替换UpdateStr函数的使用
 * 作者：wydxry
 * 时间：2022.05.26 10:28
 */

#include "../_public.h"

// 字符串替换函数
// 在字符串str中，如果存在字符串str1，就替换为字符串str2。
// str：待处理的字符串。
// str1：旧的内容。
// str2：新的内容。
// bloop：是否循环执行替换。

int main(int argc, char const *argv[])
{
    char str[301];

    STRCPY(str, sizeof str, "name:messi,no:10,job:striker.");
    UpdateStr(str, ":", "=");     
    printf("str = %s\n", str);    // str = name=messi,no=10,job=striker.

    STRCPY(str, sizeof str, "name:messi,no:10,job:striker.");
    UpdateStr(str, "name:", "");     
    printf("str = %s\n", str);    // str = messi,no:10,job:striker.

    STRCPY(str, sizeof str, "messi----10----striker");
    UpdateStr(str, "--", "-", false);     
    printf("str = %s\n", str);    // str = messi--10--striker

    STRCPY(str, sizeof str, "messi----10----striker");
    UpdateStr(str, "--", "-", true);     
    printf("str = %s\n", str);    // str = messi-10-striker

    return 0;
}
