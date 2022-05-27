/*
 * 程序名：demo27.cpp，此程序演示开发框架的CIniFile类加载参数文件
 * 作者：wydxry
 * 时间：2022.05.27 16:33
 */

#include "../_public.h"

// 用于存放本程序运行参数的数据结构
struct st_args
{
    char logpath[301];
    char connstr[101];
    char datapath[301];
    char serverip[51];
    int port;
    bool online;
};

int main(int argc, char const *argv[])
{
    // 如果执行程序时输入的参数不正确，给出帮助信息。
    if (argc != 2) { 
        printf("\nusing:/project/public/demo/demo27 inifile\n"); 
        printf("samples:/project/public/demo/demo27 /project/public/ini/hssms.xml\n\n"); 
        return -1;
    }

    // 加载参数文件
    CIniFile IniFile;

    if (IniFile.LoadFile(argv[1]) == false) {
        printf("IniFile.LoadFile(%s) failed.\n", argv[1]); 
        return -1;
    }

    // 获取参数，存放在stargs结构中
    struct st_args p;
    memset(&p, 0, sizeof(struct st_args));
    IniFile.GetValue("logpath", p.logpath, 300);
    IniFile.GetValue("connstr", p.connstr, 100);
    IniFile.GetValue("datapath", p.datapath, 300);
    IniFile.GetValue("serverip", p.serverip, 50);
    IniFile.GetValue("port", &p.port);
    IniFile.GetValue("online", &p.online);
    
    printf("logpath = %s\n", p.logpath);
    printf("connstr = %s\n", p.connstr);
    printf("datapath = %s\n", p.datapath);
    printf("serverip = %s\n", p.serverip);
    printf("port = %d\n", p.port);
    printf("online = %d\n", p.online);
    return 0;
}
