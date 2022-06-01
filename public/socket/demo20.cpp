/*
 * 程序名：demo20.cpp，此程序是网络通信的服务端程序，用于演示同步通信的效率
 * 作者：wydxry
 * 时间：2022.06.01 19:52
*/

#include "../_public.h"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Using:./demo20 port\nExample:./demo20 5005\n\n"); 
        return -1;
    }

    // socket通讯的服务端类
    CTcpServer TcpServer;

    // 服务端初始化
    if (TcpServer.InitServer(atoi(argv[1])) == false) {
        printf("TcpServer.InitServer(%s) failed.\n", argv[1]); 
        return -1;
    }

    // 等待客户端的连接请求
    if (TcpServer.Accept() == false) {
        printf("TcpServer.Accept() failed.\n"); 
        return -1;
    }

    printf("客户端（%s）已连接。\n", TcpServer.GetIP());

    CLogFile logfile;
    logfile.Open("../tmp/demo20.log", "a+");

    // 与客户端通讯，接收客户端发过来的报文后，回复"已收到"
    char buf[102400];
    while (1) {
        memset(buf, 0, sizeof buf);
        // 接收客户端的请求报文
        if (TcpServer.Read(buf) == false) {
            perror("recv");
            break;
        }
        // printf("服务器端接收信息：%s\n", buf);
        logfile.Write("服务器端接收信息：%s\n", buf);


        strcpy(buf, "已收到");
        // 向客户端发送响应报文
        if (TcpServer.Write(buf) == false) {
            perror("send");
            break;
        }
        // printf("服务器端发送信息：%s\n", buf);
        logfile.Write("服务器端发送信息：%s\n", buf);
    }
    return 0;
}
