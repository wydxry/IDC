/*
 * 程序名：demo04.cpp，此程序用于演示粘包的socket服务端
 * 作者：wydxry
 * 时间：2022.05.26 16:00
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Using:./demo02 port\nExample:./demo02 5005\n\n"); 
        return -1;
    }

    // 第1步：创建服务端的socket
    int listenfd;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        // perror: Print a message describing the meaning of the value of errno
        perror("socket");
        return -1;
    }

    // 第2步：把服务端用于通讯的地址和端口绑定到socket上
    struct sockaddr_in serveraddr; // 服务端地址信息的数据结构
    memset(&serveraddr, 0, sizeof serveraddr);
    serveraddr.sin_family = AF_INET; // 协议族，在socket编程中只能是AF_INET (TCP/IP – IPv4)
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // 任意ip地址
    serveraddr.sin_port = htons(atoi(argv[1])); // 指定通讯端口

    int ret = 0;
    ret = bind(listenfd, (struct sockaddr *)&serveraddr, sizeof serveraddr);
    if (ret != 0) {
        perror("bind");
        close(listenfd);
        return -1;
    }

    int opt = 1;
    unsigned int len = sizeof opt;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, len);

    // 第3步：把socket设置为监听模式
    /* listen: Prepare to accept connections on socket FD.
    N connection requests will be queued before further requests are refused.
    Returns 0 on success, -1 for errors.  */
    ret = listen(listenfd, 5); 
    if (ret == -1) {
        perror("listen");
        close(listenfd);
        return -1;
    }

    // 第4步：接受客户端的连接
    int clientfd; // 客户端的socket
    int socklen = sizeof(struct sockaddr_in); // struct sockaddr_in的大小
    struct sockaddr_in clientaddr; // 客户端的地址信息
    clientfd = accept(listenfd, (struct sockaddr*)&clientaddr, (socklen_t*)&socklen);
    printf("客户端 (%s) 已连接。\n", inet_ntoa(clientaddr.sin_addr));

    // 第5步：与客户端通讯，接收客户端发过来的报文
    char buffer[102400];
    while (true) {
        memset(buffer, 0, sizeof buffer);
        // 接收客户端的请求报文
        ret = recv(clientfd, buffer, sizeof buffer, 0);
        if (ret == -1) {
            perror("recv");
            break;
        }

        printf("服务器端接收信息：%s\n", buffer);
    }

    // 第6步：关闭socket，释放资源
    close(listenfd);
    close(clientfd);

    return 0;
}
