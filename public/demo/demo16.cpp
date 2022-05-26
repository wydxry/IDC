/*
 * 程序名：demo16.cpp，此程序演示开发框架中采用AddTime进行时间的运算
 * 作者：wydxry
 * 时间：2022.05.26 10:56
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    time_t ltime;
    char strtime[20];
    
    memset(strtime, 0, sizeof strtime);
    strcpy(strtime, "2020-01-01 12:00:00");

    AddTime(strtime, strtime, 0-1*24*60*60); // 减一天
    printf("strtime = %s\n", strtime); // strtime = 2019-12-31 12:00:00

    AddTime(strtime, strtime, 2*24*60*60); // 加两天
    printf("strtime = %s\n", strtime); // strtime = 2020-01-02 12:00:00

    return 0;
}
