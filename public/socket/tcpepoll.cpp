/*
 * 程序名：tcppoll.cpp，此程序用于演示采用epoll模型的使用方法
 * 作者：wydxry
 * 时间：2022.06.02 10:00
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>    
#include <arpa/inet.h>
#include <sys/fcntl.h>
#include <sys/epoll.h>

// 初始化服务端的监听端口
int initserver(int port);

int main(int argc, char const *argv[])
{
    if (argc != 2) { 
        printf("usage: ./tcpepoll port\n"); 
        return -1; 
    }

    // 初始化服务端用于监听的socket
    int listensock = initserver(atoi(argv[1]));
    if (listensock < 0) {
        printf("initserver() failed.\n"); 
        return -1;
    }

    // 创建epoll句柄
    int epollfd = epoll_create(1);

    // 为监听的socket准备可读事件
    struct epoll_event ev; // 声明事件的数据结构
    ev.events = EPOLLIN; // 读事件
    ev.data.fd = listensock; // 指定事件的自定义数据，会随着epoll_wait()返回的事件一并返回
    
    // 把监听的socket的事件加入epollfd中
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listensock, &ev);

    // 存放epoll返回的事件
    struct epoll_event evs[10];   

    while (true) {
        // 等待监视的socket有事件发生
        // int infds = epoll_wait(epollfd, evs, 10, -1);
        int infds = epoll_wait(epollfd, evs, 10, 5000);

        // 返回失败
        if (infds < 0) {
            perror("epoll() failed");
            break;
        }

        // 超时，在本程序中，select函数最后一个参数为空，不存在超时的情况，但以下代码还是留着
        if (infds == 0) {
            printf("epoll() timeout.\n");
            continue;
        }

        // 如果infds>0，表示有事件发生的socket的数量
        // 这里是客户端的socket事件，每次都要遍历整个数组，因为可能有多个socket有事件
        for (int i = 0; i < infds; i++) {
            printf("events=%d,data.fd=%d\n", evs[i].events, evs[i].data.fd);

            // 如果发生事件的是listensock，表示有新的客户端连上来
            if (evs[i].data.fd == listensock) {
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                int clientsock = accept(listensock, (struct sockaddr*)&client, &len);

                if (clientsock < 0) {
                    perror("accept() failed");
                    continue;
                }

                printf ("accept client(socket=%d) ok.\n", clientsock);

                // 为新客户端准备可读事件，并添加到epoll中
                ev.data.fd = clientsock;
                ev.events = EPOLLIN;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, clientsock, &ev); 

            } else {
                // 如果是客户端连接的socke有事件，表示有报文发过来或者连接已断开

                // 存放从客户端读取的数据
                char buf[1024];
                memset(buf, 0, sizeof buf);

                if (recv(evs[i].data.fd, buf, sizeof(buf), 0) <= 0) {
                    // 如果客户端的连接已断开
                    printf("client(eventfd=%d) disconnected.\n", evs[i].data.fd);
                    // 关闭客户端的socket
                    close(evs[i].data.fd); 

                } else {
                    // 如果客户端有报文发过来
                    printf("recv(eventfd=%d):%s\n", evs[i].data.fd, buf);
                    // 把接收到的报文内容原封不动的发回去
                    send(evs[i].data.fd, buf, strlen(buf), 0);

                }
            }
        }

    }
    return 0;
}

// 初始化服务端的监听端口
int initserver(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket() failed");
        return -1;
    }

    int opt = 1;
    unsigned int len = sizeof(opt);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, len);

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind() failed");
        close(sock);
        return -1;
    }

    if (listen(sock, 5) != 0) {
        perror("listen() failed");
        close(sock);
        return -1;
    }
    
    return sock;
}

