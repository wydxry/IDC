/*
 * 程序名：demo6.cpp，此程序演示开发框架中SNPRINTF函数的使用
 * 作者：wydxry
 * 时间：2022.05.26 09:04
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    char str[31];

    // 安全的snprintf函数。
    // 将可变参数(...)按照fmt描述的格式输出到dest字符串中。
    SNPRINTF(str, sizeof str, 5, "messi");
    printf("str = %s\n", str); // str = mess

    SNPRINTF(str, sizeof str, 15, "name: %s, no: %d, job: %s", "messi", 10, "striker");
    printf("str = %s\n", str); // str = name: messi, n

    SNPRINTF(str, sizeof str, 30, "name: %s, no: %d, job: %s", "messi", 10, "striker");
    printf("str = %s\n", str); // str = name: messi, no: 10, job: str

    return 0;
}
