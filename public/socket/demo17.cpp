/*
 * 程序名：demo17.cpp，此程序演示HTTP客户端，发送http请求报文
 * 作者：wydxry
 * 时间：2022.06.01 17:52
*/

#include "../_public.h"

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Using:./demo17 ip port\nExample:./demo17 www.weather.com.cn 8080\n\n");
        return -1;
    }

    // socket通讯的客户端类
    CTcpClient TcpClient;

    // 向服务端发起连接请求
    if (TcpClient.ConnectToServer(argv[1], atoi(argv[2])) == false) {
        printf("TcpClient.ConnectToServer(%s,%s) failed.\n", argv[1], argv[2]); 
        return -1;
    }

    char buf[102400];
    memset(buf, 0, sizeof buf);

    // 生成http请求报文。
    sprintf(buf,\
            "GET / HTTP/1.1\r\n"\
            "Host: %s:%s\r\n"\
            "\r\n",argv[1],argv[2]);
    
    // 用原生的send函数把http报文发送给服务端。
    send(TcpClient.m_connfd, buf, strlen(buf), 0);

    // 接收服务端返回的网页内容。
    while (true) {
        memset(buf, 0, sizeof buf);
        if (recv(TcpClient.m_connfd, buf, 102400, 0) <= 0) return 0;
        printf("%s", buf);
    }

    return 0;
}
