/*
 * 程序名：demo22.cpp，此程序演示开发框架中FGETS函数的用法
 * 作者：wydxry
 * 时间：2022.05.27 12:19
 */

#include "../_public.h"

// FGETS函数
// 从文本文件中读取一行。
// fp：已打开的文件指针。
// buffer：用于存放读取的内容。
// readsize：本次打算读取的字节数，如果已经读取到了结束标志，函数返回。
// endbz：行内容结束的标志，缺省为空，表示行内容以"\n"为结束标志。
// 返回值：true-成功；false-失败，一般情况下，失败可以认为是文件已结束。

int main(int argc, char const *argv[])
{
    FILE *fp;

    if ((fp = FOPEN("../tmp/test.xml", "r")) == NULL) {
        printf("FOPEN(../tmp/test.xml) %d:%s\n", errno, strerror(errno)); 
        return -1;
    }

    char buf[301];

    while (true) {
        memset(buf, 0, sizeof buf);
        // if (fgets(buf, 300, fp) == 0) break;     // 行内容以"\n"结束
        if (FGETS(fp, buf, 300, "<endl/>") == false) break; // 行内容以"<endl/>"结束
        printf("str = %s\n", buf);
    }
    
    fclose(fp);

    return 0;
}
