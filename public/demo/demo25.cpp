/*
 * 程序名：demo25.cpp，此程序演示采用开发框架的CLogFile类记录程序的运行日志
 * 作者：wydxry
 * 时间：2022.05.27 15:43
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    // 日志文件操作类
    CLogFile logfile;
    // 打开日志文件，如果"/tmp/log"不存在，就创建它，但是要确保当前用户具备创建目录的权限
    if (logfile.Open("../tmp/log/demo25.log") == false) {
        printf("logfile.Open(../tmp/log/demo25.log) failed.\n"); 
        return -1;
    }

    logfile.Write("demo25程序开始运行\n");

    // 获取某目录及其子目录中的文件列表信息
    CDir Dir;

    // 扫描../tmp/data目录下文件名匹配"surfdata_*.xml"的文件
    if (Dir.OpenDir("../tmp/data", "surfdata_*.xml") == false) {
        // printf("Dir.OpenDir(../tmp/data) failed.\n");
        logfile.Write("Dir.OpenDir(../tmp/data) failed.\n");
        return -1;
    }

    CFile File;
    while (Dir.ReadDir() == true) {
        // Dir.m_FullFileName: 文件全名，包括目录名
        printf("处理文件%s...", Dir.m_FullFileName);

        if (File.Open(Dir.m_FullFileName, "r") == false) {
            // printf("failed.File.Open(%s) failed.\n", Dir.m_FullFileName); 

            // Write方法会写入当前的时间，WriteEx方法不写时间
            logfile.WriteEx("failed.File.Open(%s) failed.\n", Dir.m_FullFileName);

            return -1;
        }

        char buf[301];
        while (true) {
            memset(buf, 0, sizeof(buf));
            if (File.FFGETS(buf, 300, "<endl/>") == false) break; // 行内容以"<endl/>"结束
            // printf("str = %s", buf);
            logfile.Write("str = %s", buf);
        }

        // 处理完文件中的数据后，关闭文件指针，并删除文件
        File.CloseAndRemove();

        // printf("ok\n");
        logfile.WriteEx("ok\n");
    }

    logfile.Write("demo25程序运行结束\n");

    return 0;
}
