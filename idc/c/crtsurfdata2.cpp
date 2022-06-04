/*
 *  程序名：crtsurfdata2.cpp  本程序用于生成全国气象站点观测的分钟数据
 *  作者：wydxry
 *  时间：2022.05.25 
 *  任务：全国气象站点参数加载到容器中
*/

#include "_public.h"

CLogFile logfile; // 日志类

// 省   站号  站名 纬度   经度  海拔高度
// 安徽,58015,砀山,34.27,116.2,44.2

// 全国气象站点参数结构体
struct st_site
{
    char provname[31]; // 省份
    char siteid[11]; // 站号
    char sitename[31]; // 站名
    double lat; // 纬度
    double lon; // 经度
    double height; // 海拔高度
};

// 存放全国气象站点参数的容器
vector<struct st_site> vsites;

bool LoadSite(const char *inifile);

int main(int argc, char const *argv[])
{
    if (argc != 4) {
        // 如果参数非法，给出帮助文档。
        printf("Using:./crtsurfdata1 inifile outpath logfile\n");
        printf("Example:/project/idc1/bin/crtsurfdata1 /project/idc1/ini/stcode.ini /tmp/surfdata /log/idc/crtsurfdata1.log\n\n");

        printf("inifile 全国气象站点参数文件名。\n");
        printf("outpath 全国气象站点数据文件存放的目录。\n");
        printf("logfile 本程序运行的日志文件名。\n\n");

        return -1;
    } else {
        // 参数合法
        printf("参数合法.\n");
    }

    // 打开程序的日志文件
    if (logfile.Open(argv[3], "a+", false) == false) {
        printf("logfile.Open(%s) failed.\n", argv[3]); 
        return -1;
    } else {
        printf("成功打开日志文件.\n");
    }

    logfile.Write("crtsurfdata2 开始运行。\n");

    // 把站点参数文件中加载到vsites容器中
    bool res = LoadSite(argv[1]);
    if (res) {
        printf("成功载入文件\n");
    } else {
        printf("未成功载入文件\n");
    }

    logfile.WriteEx("crtsurfdata2 运行结束。\n");

    return 0;
}

// 把站点参数文件中加载到vsites容器中
bool LoadSite(const char *inifile) {
    CFile File;

    // 打开站点参数文件
    if (File.Open(inifile, "r") == false) {
        logfile.Write("File.Open(%s) failed.\n", inifile); 
        return false;
    }

    char strBuffer[301];

    CCmdStr CmdStr; // CCmdStr类用于拆分有分隔符的字符串

    struct st_site site;

    while (true) {
        // 从站点参数文件中读取一行，如果已读取完，跳出循环。
        if (File.Fgets(strBuffer, 300, true) == false) break;

        // 把读取到的一行拆分。
        CmdStr.SplitToCmd(strBuffer, ",", true);

        if (CmdStr.CmdCount() != 6) continue;     // 扔掉无效的行

        // 把站点参数的每个数据项保存到站点参数结构体中
        memset(&site, 0, sizeof(struct st_site));
        CmdStr.GetValue(0, site.provname, 30); // 省份
        CmdStr.GetValue(1, site.siteid, 10); // 站号
        CmdStr.GetValue(2, site.sitename, 30); // 站名
        CmdStr.GetValue(3, &site.lat); // 纬度
        CmdStr.GetValue(4, &site.lon); // 经度
        CmdStr.GetValue(5, &site.height); // 海拔高度
        
        // 把站点参数结构体放入站点参数容器
        vsites.push_back(site);
    }

    // 查看是否载入成功
    for (int i = 0; i < vsites.size(); i++) {
        logfile.Write("provname = %s, siteid = %s, sitename = %s, lat = %.2f, lon = %.2f, height = %.2f\n", \
                    vsites[i].provname, vsites[i].siteid, vsites[i].sitename, vsites[i].lat, vsites[i].lon, vsites[i].height);
    }

    return true;
}