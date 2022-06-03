/*
 *  程序名：filetoblob.cpp  此程序演示开发框架操作MySQL数据库（把图片文件存入BLOB字段）
 *  作者：wydxry
 *  时间：2022.06.03 19:37
*/

// 开发框架操作MySQL的头文件
#include "_mysql.h"       

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
        long id;               // 超女编号
        char pic[100000];      // 超女图片的内容
        unsigned long picsize; // 图片内容占用的字节数
    }stgirls;
    
    // 操作SQL语句的对象
    sqlstatement stmt(&conn); 

    // 准备修改表的SQL语句
    stmt.prepare("update girls set pic=:1 where id=:2");
    stmt.bindinlob(1, stgirls.pic, &stgirls.picsize);
    stmt.bindin(2, &stgirls.id);

    // 修改超女信息表中id为1、2的记录
    for (int i = 1; i < 3; i++) {
        // 结构体变量初始化
        memset(&stgirls, 0, sizeof(struct st_girls));

        // 为结构体变量的成员赋值
        stgirls.id = i;
        // 把图片的内容加载到stgirls.pic中
        if (i == 1) stgirls.picsize = filetobuf("1.jpg", stgirls.pic);
        if (i == 2) stgirls.picsize = filetobuf("2.jpg", stgirls.pic);
    
        // 执行SQL语句，一定要判断返回值，0-成功，其它-失败
        // 失败代码在stmt.m_cda.rc中，失败描述在stmt.m_cda.message中
        if (stmt.execute() != 0) {
            printf("stmt.execute() failed.\n%s\n%s\n", stmt.m_sql, stmt.m_cda.message); 
            return -1;
        }
        
        // stmt.m_cda.rpc是本次执行SQL影响的记录数
        printf("成功插入了%ld条记录。\n", stmt.m_cda.rpc);
    }

    printf("update table girls ok.\n");

    // 提交数据库事务
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
