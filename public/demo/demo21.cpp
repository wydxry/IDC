/*
 * 程序名：demo21.cpp，此程序演示开发框架中FOPEN函数的用法
 * 作者：wydxry
 * 时间：2022.05.26 10:56
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    FILE *fp;

    // 用FOPEN函数代替fopen库函数，如果目录test/test.cpp不存在，会创建它
    if ((fp = FOPEN("test/test.xml", "w")) == 0) {
        printf("FOPEN(test/test.xml) %d:%s\n", errno, strerror(errno)); 
        return -1;
    }

    // 向文件中写入数据
    fprintf(fp, "<data>\n<name>wydxry<name>\n</data>\n");
    // <data><name>wydxry<name></data>
    
    fclose(fp);

    return 0;
}
