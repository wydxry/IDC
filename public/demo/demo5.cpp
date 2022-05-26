/*
 * 程序名：demo5.cpp，此程序演示开发框架中SPRINTF函数的使用。
 * 作者：wydxry
 * 时间：2022.05.26 09:04
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    char str[31]; 

    // 安全的sprintf函数。
    // 将可变参数(...)按照fmt描述的格式输出到dest字符串中。
    SPRINTF(str, sizeof str, "name: %s, no: %d", "messi", 10);
    printf("str = %s\n", str); // str = name: messi, no: 10

    SPRINTF(str, sizeof str, "name: %s, no: %d, job: %s", "messi", 10, "striker");
    printf("str = %s\n", str); // str = name: messi, no: 10, job: stri

    return 0;
}
