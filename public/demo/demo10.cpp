/*
 * 程序名：demo10.cpp，此程序演示开发框架正则表达示MatchStr函数的使用
 * 作者：wydxry
 * 时间：2022.05.26 09:04
 */

#include "../_public.h"

// MatchStr函数
// 正则表达式，判断一个字符串是否匹配另一个字符串。
// str：需要判断的字符串，精确表示的字符串，如文件名"_public.cpp"。
// rules：匹配规则表达式，用星号"*"表示任意字符串，多个字符串之间用半角的逗号分隔，如"*.h,*.cpp"。
// 注意，str参数不支持"*"，rules参数支持"*"，函数在判断str是否匹配rules的时候，会忽略字母的大小写。

int main(int argc, char const *argv[])
{
    char str[31];
    STRCPY(str, sizeof str, "_public.h");

    // 以下代码将输出yes
    if (MatchStr(str, "*.h, *.cpp")) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    // 以下代码将输出yes
    if (MatchStr(str, "*.H")) {
        printf("yes\n");
    } else {
        printf("no\n");
    }

    // 以下代码将输出no
    if (MatchStr(str, "*.cpp")) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
    return 0;
}
