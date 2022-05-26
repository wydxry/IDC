/*
 * 程序名：demo20.cpp，此程序演示开发框架的文件操作函数的用法
 * 作者：wydxry
 * 时间：2022.05.26 10:56
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    // 复制文件。
    if (COPY("/home/wydxry/ProjectCpp/demo/public/demo/test/test.xml","/home/wydxry/ProjectCpp/demo/public/demo/test/test.cpp") == false) {
        printf("COPY(/home/wydxry/ProjectCpp/demo/public/demo/test/test.xml) %d:%s\n", errno, strerror(errno));
    }

    // 删除文件。
    if (REMOVE("/home/wydxry/ProjectCpp/demo/public/demo/test/test.xml") == false) {
        printf("REMOVE(/home/wydxry/ProjectCpp/demo/public/demo/test/test.xml) %d:%s\n", errno, strerror(errno));
    }

    // 重命名文件。
    if (RENAME("/home/wydxry/ProjectCpp/demo/public/demo/test/test.cpp","/home/wydxry/ProjectCpp/demo/public/demo/test/new_test.xml") == false) {
        printf("/home/wydxry/ProjectCpp/demo/public/demo/test/test.cpp) %d:%s\n", errno, strerror(errno));
    }

    // 获取文件的大小。
    printf("size = %d\n", FileSize("/home/wydxry/ProjectCpp/demo/public/demo/test/new_test.xml")); // size = 5

    // 重置文件的时间。
    UTime("/home/wydxry/ProjectCpp/demo/public/demo/test/new_test.xml", "2022-05-26 11:57:29");

    // 获取文件的时间。
    char mtime[21]; 
    memset(mtime, 0, sizeof(mtime));
    FileMTime("/home/wydxry/ProjectCpp/demo/public/demo/test/new_test.xml", mtime, "yyyy-mm-dd hh24:mi:ss");
    printf("mtime = %s\n", mtime);   // mtime = 2022-05-26 11:57:29
    
    return 0;
}
