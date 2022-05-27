/*
 * 程序名：demo24.cpp，此程序演示开发框架中采用CDir类和CFile类处理数据文件的用法
 * 作者：wydxry
 * 时间：2022.05.27 15:35
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    // 获取某目录及其子目录中的文件列表信息
    CDir Dir;

    // 扫描/tmp/data目录下文件名匹配"surfdata_*.xml"的文件
    if (Dir.OpenDir("../tmp/data", "surfdata_*.xml") == false) {
        printf("Dir.OpenDir(../tmp/data) failed.\n");
        return -1;
    }

    CFile File;
    while (Dir.ReadDir() == true) {
        // Dir.m_FullFileName: 文件全名，包括目录名
        printf("处理文件%s...", Dir.m_FullFileName);

        if (File.Open(Dir.m_FullFileName, "r") == false) {
            printf("failed.File.Open(%s) failed.\n", Dir.m_FullFileName); 
            return -1;
        }

        char buf[301];
        while (true) {
            memset(buf, 0, sizeof(buf));
            if (File.FFGETS(buf, 300, "<endl/>") == false) break; // 行内容以"<endl/>"结束
            printf("str =%s", buf);
        }

        // 处理完文件中的数据后，关闭文件指针，并删除文件
        File.CloseAndRemove();

        printf("ok\n");
    }

    return 0;
}
