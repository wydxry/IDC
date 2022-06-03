/*
 *  程序名：deletetable.cpp, 此程序演示开发框架操作MySQL数据库（删除表中的记录）
 *  作者：wydxry
 *  时间：2022.06.03 19:07
*/

// 开发框架操作MySQL的头文件
#include "_mysql.h"       
#include <unistd.h>

int main(int argc,char *argv[])
{
    // 数据库连接类
    connection conn;

    // 登录数据库，返回值：0-成功；其它是失败，存放了MySQL的错误代码
    // 失败代码在conn.m_cda.rc中，失败描述在conn.m_cda.message中。
    if (conn.connecttodb("127.0.0.1,root,root,testmysql,3306", "utf8") != 0) {
        printf("connect database failed.\n%s\n", conn.m_cda.message); 
        return -1;
    }

    // 定义用于超女信息的结构，与表中的字段对应
    struct st_girls
    {
        long id;        // 超女编号
        char name[31];  // 超女姓名
        double weight;  // 超女体重
        char btime[20]; //报名时间
    }stgirls;
    
    // 操作SQL语句的对象
    sqlstatement stmt(&conn); 

    // 查询条件最小和最大的id
    int iminid, imaxid;

    // 准备删除表的SQL语句
    stmt.prepare("delete from girls where id>=:1 and id<=:2");
    
    /*
        注意事项：
        1、如果SQL语句的主体没有改变，只需要prepare()一次就可以了；
        2、结果集中的字段，调用bindout()绑定变量的地址；
        3、bindout()方法的返回值固定为0，不用判断返回值；
        4、如果SQL语句的主体已改变，prepare()后，需重新用bindout()绑定变量；
        5、调用execute()方法执行SQL语句，然后再循环调用next()方法获取结果集中的记录；
        6、每调用一次next()方法，从结果集中获取一条记录，字段内容保存在已绑定的变量中。
    */

    // 为SQL语句绑定输入变量的地址，bindin方法不需要判断返回值
    stmt.bindin(1, &iminid);
    stmt.bindin(2, &imaxid);

    // 指定待查询记录的最小id的值
    iminid = 1;   
    // 指定待查询记录的最大id的值
    imaxid = 3;    
    
    // 执行SQL语句，一定要判断返回值，0-成功，其它-失败
    // 失败代码在stmt.m_cda.rc中，失败描述在stmt.m_cda.message中
    if (stmt.execute() != 0) {
        printf("stmt.execute() failed.\n%s\n%s\n", stmt.m_sql, stmt.m_cda.message); 
        return -1;
    }

    // 请注意，stmt.m_cda.rpc变量非常重要，它保存了SQL被执行后影响的记录数
    printf("本次删除了girls表%ld条记录。\n", stmt.m_cda.rpc);

    // 提交数据库事务 否则删不掉
    conn.commit();   

    return 0;
}

/*
-- 超女基本信息表。
create table girls(id      bigint(10),    -- 超女编号。
                   name    varchar(30),   -- 超女姓名。
                   weight  decimal(8,2),  -- 超女体重。
                   btime   datetime,      -- 报名时间。
                   memo    longtext,      -- 备注。
                   pic     longblob,      -- 照片。
                   primary key (id));
*/
