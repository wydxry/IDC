/*
 * 程序名：demo11.cpp，此程序演示开发框架拆分字符串的类CCmdStr的使用
 * 作者：wydxry
 * 时间：2022.05.26 10:28
 */

#include "../_public.h"

// CCmdStr类用于拆分有分隔符的字符串。
// 字符串的格式为：字段内容1+分隔符+字段内容2+分隔符+字段内容3+分隔符+...+字段内容n。

// 用于存放足球运动员资料的结构体
struct st_player
{
    char name[51];    // 姓名
    char no[6];       // 球衣号码
    bool striker;     // 场上位置是否是前锋，true-是；false-不是。
    int  age;         // 年龄
    double weight;    // 体重，kg。
    long sal;         // 年薪，欧元。
    char club[51];    // 效力的俱乐部
};

int main(int argc, char const *argv[])
{
    struct st_player p;
    memset(&p, 0, sizeof(struct st_player));

    char str[301];
    STRCPY(str, sizeof str, "messi  ,10,true,30,68.5,2100000,Barcelona");
    printf("str = %s\n", str); // str = messi  ,10,true,30,68.5,2100000,Barcelona

    CCmdStr CmdStr;
    CmdStr.SplitToCmd(str, ",");    // 以逗号拆分str
    CmdStr.GetValue(0, p.name, 50); // 获取姓名
    CmdStr.GetValue(1, p.no, 5);    // 获取球衣号码
    CmdStr.GetValue(2, &p.striker); // 场上位置
    CmdStr.GetValue(3, &p.age);     // 获取年龄
    CmdStr.GetValue(4, &p.weight);  // 获取体重
    CmdStr.GetValue(5, &p.sal);     // 获取年薪，欧元
    CmdStr.GetValue(6, p.club, 50); // 获取效力的俱乐部

    printf("name = %s, no= %s, striker = %d, age = %d, weight = %.1f, sal = %ld, club = %s\n",\
         p.name, p.no, p.striker, p.age, p.weight, p.sal, p.club);
    // name = messi  , no= 10, striker = 1, age = 30, weight = 68.5, sal = 2100000, club = Barcelona
    return 0;
}
