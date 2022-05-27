/*
 * 程序名：demo13.cpp，此程序用于演示网银APP软件的客户端, 增加了心跳报文
 * 作者：wydxry
 * 时间：2022.05.27 09:37
*/

#include "../_public.h"

CTcpClient TcpClient;

bool srv000(); // 心跳
bool srv001(); // 登录业务
bool srv002(); // 我的账户（查询余额）

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Using:./demo11 ip port\nExample:./demo11 127.0.0.1 5005\n\n"); 
        return -1;
    }

    // 向服务端发起连接请求
    if (TcpClient.ConnectToServer(argv[1], atoi(argv[2])) == false) {
        printf("TcpClient.ConnectToServer(%s,%s) failed.\n", argv[1], argv[2]); 
        return -1;
    }

    // 登录业务
    if (srv001() == false) {
        printf("srv001() failed.\n"); 
        return -1;
    }

    // 我的账户（查询余额）
    if (srv002() == false) {
        printf("srv002() failed.\n"); 
        return -1;
    }

    sleep(10);

    for (int i = 3; i < 5; i++) {
        if (srv000() == false) {
            break;
        }
        sleep(i);
    }

    // 我的账户（查询余额）
    if (srv002() == false) {
        printf("srv002() failed.\n"); 
        return -1;
    }

    return 0;
}

// 心跳
bool srv000() {
    char buf[1024];
    SPRINTF(buf, sizeof buf, "<srvcode>0</srvcode>");
    printf("客户端向服务端发送信息：%s\n", buf);

    // 向服务端发送请求报文
    if (TcpClient.Write(buf) == false) {
        perror("send");
        return false;
    }

    memset(buf, 0, sizeof buf);
    // 接收服务端的回应报文
    if (TcpClient.Read(buf) == false) {
        perror("recv");
        return false;
    }
    printf("客户端接收服务端的信息：%s\n", buf);

    return true;
}

// 登录业务
bool srv001() {
    char buf[1024];
    SPRINTF(buf, sizeof buf, "<srvcode>1</srvcode><tel>1392220000</tel><password>123456</password>");
    printf("客户端向服务端发送信息: %s\n", buf);
    // 向服务端发送请求报文
    if (TcpClient.Write(buf) == false) {
        perror("send");
        return false;
    }

    memset(buf, 0, sizeof buf);
    // 接收服务端的回应报文
    if (TcpClient.Read(buf) == false) {
        perror("recv");
        return false;
    }
    printf("客户端接收服务端的信息：%s\n", buf);

    // 解析服务端返回的xml信息
    int ret = -1;
    GetXMLBuffer(buf, "retcode", &ret);
    if (ret != 0) {
        printf("登录失败\n");
        return false;
    }

    printf("登录成功\n");

    return true;
} 

// 我的账户（查询余额）
bool srv002() {
    char buf[1024];
    SPRINTF(buf, sizeof buf, "<srvcode>2</srvcode><cardid>62620000000001</cardid>");
    printf("客户端向服务端发送信息: %s\n", buf);
    // 向服务端发送请求报文
    if (TcpClient.Write(buf) == false) {
        perror("send");
        return false;
    }

    memset(buf, 0, sizeof buf);
    // 接收服务端的回应报文
    if (TcpClient.Read(buf) == false) {
        perror("recv");
        return false;
    }
    printf("客户端接收服务端的信息：%s\n", buf);

    // 解析服务端返回的xml信息
    int ret = -1;
    GetXMLBuffer(buf, "retcode", &ret);
    if (ret != 0) {
        printf("查询余额失败\n");
        return false;
    }

    double ye = 0;
    GetXMLBuffer(buf, "ye", &ye);

    printf("查询余额成功(%.2f)。\n", ye); 

    return true;

}