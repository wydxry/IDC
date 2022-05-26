/*
 * 程序名：demo14.cpp，此程序演示开发框架中LocalTime时间函数的使用
 * 作者：wydxry
 * 时间：2022.05.26 10:56
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    char strtime[20];
    memset(strtime, 0, sizeof strtime);

    LocalTime(strtime, "yyyy-mm-dd hh24:mi:ss", -30); // 获取30秒前的时间
    printf("time = %s\n", strtime); // time = 2022-05-26 11:05:35

    LocalTime(strtime, "yyyy-mm-dd hh24:mi:ss"); // 获取当前的时间
    printf("time = %s\n", strtime); // time = 2022-05-26 11:06:05

    LocalTime(strtime, "yyyy-mm-dd hh24:mi:ss", 30); // 获取30后前的时间
    printf("time = %s\n", strtime); // time = 2022-05-26 11:06:35

    return 0;
}
