/*
 * 程序名：demo03.cpp，此程序用于演示粘包的socket客户端
 * 作者：wydxry
 * 时间：2022.05.26 15:55
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// TCP粘包是指发送方发送的若干包数据到接收方接收时粘成一包，从接收缓冲区看，后一包数据的头紧接着前一包数据的尾

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Using:./demo01 ip port\nExample:./demo01 127.0.0.1 5005\n\n"); 
        return -1;
    }

    int ret = -1; // 指示信息

    // 第1步：创建客户端的socket
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    // 第2步：向服务器发起连接请求
    struct hostent* h;
    if ((h = gethostbyname(argv[1])) == 0) {
        // 指定服务器的ip地址
        printf("gethostbyname failed.\n"); 
        close(sockfd); 
        return -1; 
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2])); // 指定服务端的通讯端口
    memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);

    if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof servaddr) != 0) {
        // 向服务器端发起连接请求
        perror("connect");
        close(sockfd);
        return -1;
    }
    

    // 第3步：与服务端通讯，连续发送10000000个报文
    char buffer[102400];
    for (int i = 0; i < 10000000; i++) {
        memset(buffer, 0, sizeof buffer);
        sprintf(buffer, "这是第%d个数据, 编号为%03d", i + 1, i + 1);
        
        // 向服务端发送请求报文
        ret = send(sockfd, buffer, strlen(buffer), 0);
        if (ret == -1) {
            perror("send");
            break;
        }

        printf("客户端发送信息：%s\n", buffer);
    }

    // 第4步：关闭socket，释放资源
    close(sockfd);

    return 0;
}


