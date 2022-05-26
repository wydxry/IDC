/*
 * 程序名：demo07.cpp，此程序用于演示采用TcpClient类实现socket通讯的客户端
 * 作者：wydxry
 * 时间：2022.05.26 16:46
*/

#include "../_public.h"

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Using:./demo01 ip port\nExample:./demo01 127.0.0.1 5005\n\n"); 
        return -1;
    }

    bool ret; // 指示信息

    // socket通讯的客户端类
    CTcpClient TcpClient;

    // 向服务端发起连接请求
    if (TcpClient.ConnectToServer(argv[1], atoi(argv[2])) == false) {
        printf("TcpClient.ConnectToServer(%s,%s) failed.\n", argv[1], argv[2]); 
        return -1;
    }

    char buf[102400];

    // 与服务端通讯，发送一个报文后等待回复，然后再发下一个报文
    for (int i = 0; i < 100000; i++) {
        SPRINTF(buf, sizeof buf, "这是第%d个数据, 编号%03d", i, i);
        // 向服务端发送请求报文
        if (TcpClient.Write(buf) == false) {
            perror("send");
            break;
        }
        printf("客户端发送信息: %s\n", buf);

        memset(buf, 0, sizeof buf);
        // 接收服务端的回应报文
        if (TcpClient.Read(buf) == false) {
            perror("recv");
            break;
        }
        printf("客户端接收信息: %s\n", buf);

        sleep(1); // 每隔一秒后再次发送报文
    }

    return 0;
}


