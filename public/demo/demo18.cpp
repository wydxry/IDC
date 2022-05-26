/*
 * 程序名：demo18.cpp，此程序演示开发框架中采用MKDIR函数根据绝对路径的文件名或目录名逐级的创建目录
 * 作者：wydxry
 * 时间：2022.05.26 10:56
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    MKDIR("/home/wydxry/ProjectCpp/demo/public/demo/test", false);
    MKDIR("/home/wydxry/ProjectCpp/demo/public/demo/test/test.xml", true);
    return 0;
}
