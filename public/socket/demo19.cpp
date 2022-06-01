/*
 * 程序名：demo19.cpp，此程序是网络通信的客户端程序，用于演示异步通信（多进程）的效率
 * 作者：wydxry
 * 时间：2022.06.01 19:52
*/

#include "../_public.h"

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Using:./demo19 ip port\nExample:./demo19 127.0.0.1 5005\n\n"); 
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

    CLogFile logfile(1000);
    logfile.Open("../tmp/demo19.log", "a+");

    int pid = fork();

    // 与服务端通讯，发送一个报文后等待回复，然后再发下一个报文
    for (int i = 0; i < 100000; i++) {
        if (pid > 0) {
            SPRINTF(buf, sizeof buf, "这是第%d个数据, 编号%03d", i, i);
            // 向服务端发送请求报文
            if (TcpClient.Write(buf) == false) {
                perror("send");
                break;
            }
            // printf("客户端发送信息: %s\n", buf);
            logfile.Write("客户端发送信息: %s\n", buf);

        } else {
            memset(buf, 0, sizeof buf);
            // 接收服务端的回应报文
            if (TcpClient.Read(buf) == false) {
                perror("recv");
                break;
            }
            // printf("客户端接收信息: %s\n", buf);
            logfile.Write("客户端接收信息: %s\n", buf);

        }
    }

    return 0;
}


