/*
 * 程序名：demo15.cpp，此程序演示开发框架中整数表示的时间和字符串表示的时间之间的转换
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

    ltime = strtotime(strtime); // 转换为整数的时间
    printf("ltime = %ld\n", ltime); // ltime = 1577851200

    memset(strtime, 0, sizeof strtime);
    timetostr(ltime, strtime, "yyyy-mm-dd hh24:mi:ss"); // 转换为字符串的时间
    printf("strtime = %s\n", strtime); // strtime = 2020-01-01 12:00:00

    return 0;
}
