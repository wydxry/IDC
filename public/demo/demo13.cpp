/*
 * 程序名：demo13.cpp，此程序演示调用开发框架的GetXMLBuffer函数解析xml字符串
 * 作者：wydxry
 * 时间：2022.05.26 10:56
 */

#include "../_public.h"

// 用于存放足球运动员资料的结构体
struct st_player
{
    char name[51];    // 姓名
    char no[6];       // 球衣号码
    bool striker;     // 场上位置是否是前锋，true-是；false-不是
    int  age;         // 年龄
    double weight;    // 体重，kg
    long sal;         // 年薪，欧元
    char club[51];    // 效力的俱乐部
};

int main(int argc, char const *argv[])
{
    struct st_player p;
    memset(&p, 0, sizeof(struct st_player));

    char str[301];
    STRCPY(str, sizeof str, "<name>西施</name><no>10</no><striker>true</striker><age>30</age><weight>68.5</weight><sal>21000000</sal><club>Barcelona</club>");
    
    GetXMLBuffer(str, "name", p.name,50);
    GetXMLBuffer(str,"no", p.no,5);
    GetXMLBuffer(str, "striker", &p.striker);
    GetXMLBuffer(str, "age", &p.age);
    GetXMLBuffer(str, "weight", &p.weight);
    GetXMLBuffer(str, "sal", &p.sal);
    GetXMLBuffer(str, "club", p.club,50);
    
    printf("name = %s, no= %s, striker = %d, age = %d, weight = %.1f, sal = %ld, club = %s\n",\
         p.name, p.no, p.striker, p.age, p.weight, p.sal, p.club);
    // name = 西施, no= 10, striker = 1, age = 30, weight = 68.5, sal = 21000000, club = Barcelona
    return 0;
}
