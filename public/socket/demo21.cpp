/*
 * 程序名：demo21.cpp，此程序是网络通信的客户端程序，用于演示异步通信（poll）效率
 * 作者：wydxry
 * 时间：2022.06.01 20:52
*/

#include "../_public.h"

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Using:./demo21 ip port\nExample:./demo21 127.0.0.1 5005\n\n"); 
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
    int  ibuflen=0;

    CLogFile logfile(1000);
    logfile.Open("../tmp/demo21.log", "a+");

    int j = 0;

    // 与服务端通讯，发送一个报文后等待回复，然后再发下一个报文
    for (int i = 0; i < 1000000; i++) {
        SPRINTF(buf, sizeof buf, "这是第%d个数据, 编号%03d", i, i);
        // 向服务端发送请求报文
        if (TcpClient.Write(buf) == false) {
            perror("send");
            break;
        }
        // printf("客户端发送信息: %s\n", buf);
        logfile.Write("客户端发送信息: %s\n", buf);

        // 接收服务端的回应报文
        while (true) {
            memset(buf, 0, sizeof buf);
            // 接收服务端的回应报文
            if (TcpRead(TcpClient.m_connfd, buf, &ibuflen, -1) == false) {
                perror("recv");
                break;
            }
            // printf("客户端接收信息: %s\n", buf);
            logfile.Write("客户端接收信息: %s\n", buf);
            j++;
        }
    }

    // 接收服务端的回应报文
    while (j < 1000000) {
        memset(buf, 0, sizeof buf);
        // 接收服务端的回应报文
        if (TcpRead(TcpClient.m_connfd, buf, &ibuflen) == false) {
            perror("recv");
            break;
        }
        // printf("客户端接收信息: %s\n", buf);
        logfile.Write("客户端接收信息: %s\n", buf);
        j++;
    }

    return 0;
}


