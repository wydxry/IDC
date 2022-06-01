/*
 * 程序名：tcpselect.cpp，此程序用于演示采用select模型的使用方法
 * 作者：wydxry
 * 时间：2022.06.01 20:59
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>

// 初始化服务端的监听端口
int initserver(int port);

int main(int argc, char const *argv[])
{
    if (argc != 2) { 
        printf("usage: ./tcpselect port\n"); 
        return -1; 
    }

    // 初始化服务端用于监听的socket
    int listensock = initserver(atoi(argv[1]));
    if (listensock < 0) {
        printf("initserver() failed.\n"); 
        return -1;
    }

    // 读事件socket的集合，包括监听socket和客户端连接上来的socket
    fd_set readfds; 
    // 初始化读事件socket的集合
    FD_ZERO(&readfds);
    // 把listensock添加到读事件socket的集合中
    FD_SET(listensock, &readfds);

    // 记录集合中socket的最大值
    int maxfd = listensock;

    while (true) {
        // 事件：1)新客户端的连接请求accept；
        //       2)客户端有报文到达recv，可以读；
        //       3)客户端连接已断开；
        //       4)可以向客户端发送报文send，可以写
        // 可读事件  可写事件
        // select() 等待事件的发生(监视哪些socket发生了事件)
        fd_set tmpfds = readfds;
        struct timeval timeout;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        int infds = select(maxfd + 1, &tmpfds, NULL, NULL, &timeout);

        // 返回失败
        if (infds < 0) {
            perror("select() failed");
            break;
        }

        // 超时，在本程序中，select函数最后一个参数为空，不存在超时的情况，但以下代码还是留着
        if (infds == 0) {
            printf("select() timeout.\n");
            continue;
        }

        // 如果infds>0，表示有事件发生的socket的数量
        for (int eventfd = 0; eventfd <= maxfd; eventfd++) {
            // 如果没有事件，continue
            if (FD_ISSET(eventfd, &tmpfds) <= 0) continue;

            // 如果发生事件的是listensock，表示有新的客户端连上来
            if (eventfd == listensock) {
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                int clientsock = accept(listensock, (struct sockaddr*)&client, &len);
                if (clientsock < 0) {
                    perror("accept() failed");
                    continue;
                }

                printf ("accept client(socket=%d) ok.\n", clientsock);

                // 把新客户端的socket加入可读socket的集合
                FD_SET(clientsock, &readfds);
                // 更新maxfd的值
                if (maxfd < clientsock) maxfd = clientsock;
            } else {
                // 如果是客户端连接的socke有事件，表示有报文发过来或者连接已断开

                // 存放从客户端读取的数据
                char buf[1024];
                memset(buf, 0, sizeof buf);

                if (recv(eventfd, buf, sizeof(buf), 0) <= 0) {
                    // 如果客户端的连接已断开
                    printf("client(eventfd=%d) disconnected.\n", eventfd);
                    close(eventfd);            // 关闭客户端的socket
                    FD_CLR(eventfd, &readfds);  // 把已关闭客户端的socket从可读socket的集合中删除
                    
                    // 重新计算maxfd的值，注意，只有当eventfd==maxfd时才需要计算
                    if (eventfd == maxfd) {
                        for (int i = maxfd; i > 0; i--) {
                            if (FD_ISSET(i, &readfds)) {
                                maxfd = i;
                                break;
                            }
                        }
                    }
                } else {
                    // 如果客户端有报文发过来
                    printf("recv(eventfd=%d):%s\n", eventfd, buf);

                    // 把接收到的报文内容原封不动的发回去
                    fd_set tmpfds;
                    FD_ZERO(&tmpfds);
                    FD_SET(eventfd, &tmpfds);

                    if (select(eventfd + 1, NULL, &tmpfds, NULL, NULL) <= 0) {
                        perror("select() failed");
                    } else {
                        send(eventfd, buf, strlen(buf), 0);
                    }

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

