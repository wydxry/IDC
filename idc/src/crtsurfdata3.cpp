/*
 *  程序名：crtsurfdata3.cpp  本程序用于生成全国气象站点观测的分钟数据
 *  作者：Celees
 *  时间：2022.05.25 
 *  任务：模拟生成全国气象站点分钟观测数据
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

// 全国气象站点分钟观测数据结构
struct st_surfdata
{
    char siteid[11];     // 站号
    char datatime[21];   // 数据时间：格式yyyymmddhh24miss
    int  t;              // 气温：单位，0.1摄氏度。
    int  p;              // 气压：0.1百帕。
    int  u;              // 相对湿度，0-100之间的值。
    int  wd;             // 风向，0-360之间的值。
    int  wf;             // 风速：单位0.1m/s
    int  r;              // 降雨量：0.1mm。
    int  vis;            // 能见度：0.1米。
};

// 存放全国气象站点参数的容器
vector<struct st_site> vsites;

// 存放全国气象站点分钟观测数据的容器
vector<struct st_surfdata> vsurfdata;  

// 把站点参数文件中加载到vstcode容器中
bool LoadSite(const char *inifile);

// 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器中
void CrtSurfData();

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

    logfile.Write("crtsurfdata3 开始运行。\n");

    // 把站点参数文件中加载到vsites容器中
    bool res = LoadSite(argv[1]);
    if (res) {
        printf("成功载入文件\n");
    } else {
        printf("未成功载入文件\n");
    }

    // 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器中
    CrtSurfData();

    logfile.WriteEx("crtsurfdata3 运行结束。\n");

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

// 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器
void CrtSurfData() {
    // 设置随机数种子。
    srand(time(0));

    // 获取当前时间，当作观测时间
    char curtime[21];
    memset(&curtime, 0, sizeof curtime);
    LocalTime(curtime, "yyyymmddhh24miss");

    struct st_surfdata stsurfdata;

    // 遍历气象站点参数的vstcode容器
    for (int i = 0; i < vsites.size(); i++) {
        memset(&stsurfdata, 0, sizeof(struct st_surfdata));

        // 用随机数填充分钟观测数据的结构体
        strncpy(stsurfdata.siteid, vsites[i].siteid, 10); // 站号。
        strncpy(stsurfdata.datatime, curtime, 14);  // 数据时间：格式yyyymmddhh24miss
        stsurfdata.t = rand() % 351;       // 气温：单位，0.1摄氏度
        stsurfdata.p = rand() % 265+10000; // 气压：0.1百帕
        stsurfdata.u = rand() % 100+1;     // 相对湿度，0-100之间的值。
        stsurfdata.wd = rand() % 360;      // 风向，0-360之间的值。
        stsurfdata.wf = rand() % 150;      // 风速：单位0.1m/s
        stsurfdata.r = rand() % 16;        // 降雨量：0.1mm
        stsurfdata.vis = rand() % 5001 + 100000;  // 能见度：0.1米

        // 把观测数据的结构体放入vsurfdata容器。
        vsurfdata.push_back(stsurfdata);
    }
}