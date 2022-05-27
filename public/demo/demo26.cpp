/*
 * 程序名：demo26.cpp，此程序演示开发框架的CLogFile类的日志文件的切换
 * 作者：wydxry
 * 时间：2022.05.27 16:27
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    CLogFile logfile;

    // 打开日志文件，如果"../tmp/log"不存在，就创建它，但是要确保当前用户具备创建目录的权限
    if (logfile.Open("../tmp/log/demo26.log") == false) {
        printf("logfile.Open(../tmp/log/demo26.log) failed.\n");
        return -1;
    }

    logfile.Write("demo26程序开始运行\n");

    // 产生足够大的日志
    for (int i = 0; i < 10000000; i++) {
        // 如果日志文件大于100M，就把当前的日志文件备份成历史日志文件，切换成功后清空当前日志文件的内容
        // 备份后的文件会在日志文件名后加上日期时间
        // 注意，在多进程的程序中，日志文件不可切换，多线的程序中，日志文件可以切换
        logfile.Write("本程序演示日志文件的切换，这是第%010d条记录\n", i);
    }

    logfile.Write("demo26程序结束运行\n");

    return 0;
}
