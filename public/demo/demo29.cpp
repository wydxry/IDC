/*
 * 程序名：demo29.cpp，此程序演示采用开发框架的CTcpServer类实现socket通信的服务端
 * 作者：wydxry
 * 时间：2022.05.27 17:00
 */

#include "../_public.h"

// 创建服务端对象
CTcpServer TcpServer;

int main(int argc, char const *argv[])
{
    // 初始化TcpServer的通信端口5005
    if (TcpServer.InitServer(5005) == false) {
        printf("TcpServer.InitServer(5005) failed.\n"); 
        return -1;
    }

    // 等待客户端连接
    if (TcpServer.Accept() == false) {
        printf("TcpServer.Accept() failed.\n"); 
        return -1;
    }

    printf("客户端(%s)已连接。\n", TcpServer.GetIP());
    
    // 存放数据的缓冲区
    char buf[1024];  

    while (true) {
        memset(buf, 0, sizeof buf);
        // 接收客户端发来的请求报文
        if (TcpServer.Read(buf, 300) == false) {
            break;
        }

        // 回复客户端已收到
        strcat(buf, " 已收到");     
        printf("服务端向客户端发送信息：%s\n", buf);
        if (TcpServer.Write(buf) == false) {
            break;
        }

    }

    // 程序直接退出，析构函数会释放资源
    printf("客户端已断开。\n");    

    return 0;
}
