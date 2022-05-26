/*
 * 程序名：demo08.cpp，此程序用于演示采用TcpServer类实现socket通讯的服务端
 * 作者：wydxry
 * 时间：2022.05.26 16:58
*/

#include "../_public.h"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Using:./demo02 port\nExample:./demo02 5005\n\n"); 
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

    // 与客户端通讯，接收客户端发过来的报文后，回复"已收到"
    char buf[102400];
    while (1) {
        memset(buf, 0, sizeof buf);
        // 接收客户端的请求报文
        if (TcpServer.Read(buf) == false) {
            perror("recv");
            break;
        }
        printf("服务器端接收信息：%s\n", buf);

        strcpy(buf, "已收到");
        // 向客户端发送响应报文
        if (TcpServer.Write(buf) == false) {
            perror("send");
            break;
        }
        printf("服务器端发送信息：%s\n", buf);
    }
    return 0;
}
