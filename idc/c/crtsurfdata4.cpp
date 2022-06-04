/*
 *  程序名：crtsurfdata4.cpp  本程序用于生成全国气象站点观测的分钟数据
 *  作者：wydxry
 *  时间：2022.05.25 
 *  任务：模拟生成全国气象站点分钟观测数据并保存为csv文件
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

char strddatetime[21]; // 观测数据的时间

// 存放全国气象站点参数的容器
vector<struct st_site> vsites;

// 存放全国气象站点分钟观测数据的容器
vector<struct st_surfdata> vsurfdata;  

// 把站点参数文件中加载到vstcode容器中
bool LoadSite(const char *inifile);

// 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器中
void CrtSurfData();

// 把容器vsurfdata中的全国气象站点分钟观测数据写入文件。
bool CrtSurfFile(const char *outpath,const char *datafmt);

int main(int argc, char const *argv[])
{
    if (argc != 5) {
        // 如果参数非法，给出帮助文档。
        printf("Using:./crtsurfdata4 inifile outpath logfile datafmt\n");
        printf("Example:/project/idc1/bin/crtsurfdata4 /project/idc1/ini/stcode.ini /tmp/idc/surfdata /log/idc/crtsurfdata4.log xml,json,csv\n\n");

        printf("inifile 全国气象站点参数文件名。\n");
        printf("outpath 全国气象站点数据文件存放的目录。\n");
        printf("logfile 本程序运行的日志文件名。\n");
        printf("datafmt 生成数据文件的格式，支持xml、json和csv三种格式，中间用逗号分隔。\n\n");

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

    logfile.Write("crtsurfdata4 开始运行。\n");

    // 把站点参数文件中加载到vsites容器中
    bool res = LoadSite(argv[1]);
    if (res) {
        printf("成功载入文件\n");
    } else {
        printf("未成功载入文件\n");
    }

    // 模拟生成全国气象站点分钟观测数据，存放在vsurfdata容器中
    CrtSurfData();

    // 把容器vsurfdata中的全国气象站点分钟观测数据写入文件。
    if (strstr(argv[4], "xml") != 0) {
        CrtSurfFile(argv[2], "xml");
    } else if (strstr(argv[4], "json") != 0) {
        CrtSurfFile(argv[2], "json");
    } else if (strstr(argv[4], "csv") != 0) {
        CrtSurfFile(argv[2], "csv");
    } else {
        printf("第五个参数不合法\n");
    }

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

// 把容器vsurfdata中的全国气象站点分钟观测数据写入文件
bool CrtSurfFile(const char *outpath,const char *datafmt) {
    CFile File;

    // 拼接生成数据的文件名，例如：/tmp/idc/surfdata/SURF_ZH_20210629092200_2254.csv
    char strFileName[301];
    sprintf(strFileName, "%s/SURF_ZH_%s_%d.%s", outpath, strddatetime, getpid(), datafmt);

    cout << strFileName << endl;

    // 打开文件
    if (File.OpenForRename(strFileName, "w") == false) {
        logfile.Write("File.OpenForRename(%s) failed.\n", strFileName); 
        return false;
    }

    // 写入第一行标题
    if (strcmp(datafmt, "csv") == 0) {
        File.Fprintf("站点代码,数据时间,气温,气压,相对湿度,风向,风速,降雨量,能见度\n");
    }

    // 遍历存放观测数据的vsurfdata容器
    for (int i = 0; i < vsurfdata.size(); i++) {
        // 写入一条记录
        if (strcmp(datafmt,"csv") == 0) {
            File.Fprintf("%s,%s,%.1f,%.1f,%d,%d,%.1f,%.1f,%.1f\n", \
            vsurfdata[i].siteid, vsurfdata[i].datatime, vsurfdata[i].t/10.0, vsurfdata[i].p/10.0, \
            vsurfdata[i].u, vsurfdata[i].wd, vsurfdata[i].wf/10.0, vsurfdata[i].r/10.0, vsurfdata[i].vis/10.0);
        }
    }

    // 关闭文件
    File.CloseAndRename();
    logfile.Write("生成数据文件%s成功，数据时间%s，记录数%d。\n", strFileName, strddatetime, vsurfdata.size());

    return true;
}