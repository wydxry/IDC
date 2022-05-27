/*
 * 程序名：demo28.cpp，此程序演示采用开发框架的CTcpClient类实现socket通信的客户端
 * 作者：wydxry
 * 时间：2022.05.27 16:53
 */

#include "../_public.h"

// 创建客户端的对象
CTcpClient TcpClient;


int main(int argc, char const *argv[])
{
    // 向服务端发起连接请求
    if (TcpClient.ConnectToServer("127.0.0.1", 5005) == false) {
        printf("TcpClient.ConnectToServer(\"127.0.0.1\", 5005) failed.\n"); 
        return -1;
    }

    // 存放数据的缓冲区
    char buf[1024];
    memset(buf, 0, sizeof buf);
    
    // 与服务端交互五次
    for (int i = 0; i < 5; i++) {
        memset(buf, 0, sizeof buf);
        snprintf(buf, 50, "这是第%d个数据", i);
        printf("客户端向服务端发送信息：%s\n", buf);
        
        // 向服务端发送请求报文
        if (TcpClient.Write(buf) == false) {
            break;
        }

        memset(buf, 0, sizeof buf);
        // 接收服务端的回应报文
        if (TcpClient.Read(buf) == false) {
            break;
        }
        printf("客户端接收服务端的信息：%s\n", buf);

        sleep(1);
    }

    // 程序直接退出，析构函数会释放资源

    return 0;
}
