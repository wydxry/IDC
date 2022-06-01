/*
 * 程序名：tcppoll.cpp，此程序用于演示采用poll模型的使用方法
 * 作者：wydxry
 * 时间：2022.06.01 20:59
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>

// ulimit -a
#define MAXNFDS 1024

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

    // fds存放需要监视的socket
    struct pollfd fds[MAXNFDS];
    for (int i = 0; i < MAXNFDS; i++) {
        // 初始化数组，把全部的fd设置为-1
        fds[i].fd = -1;
    }

    // 把listensock和读事件添加到数组中
    fds[listensock].fd = listensock;
    fds[listensock].events = POLLIN;
    
    // fds数组中需要监视的socket的大小
    int maxfd = listensock;       

    while (true) {
        int infds = poll(fds, maxfd + 1, 5000);

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
        // 这里是客户端的socket事件，每次都要遍历整个数组，因为可能有多个socket有事件
        for (int eventfd = 0; eventfd <= maxfd; eventfd++) {
            // 如果fd为负，忽略它
            if (fds[eventfd].fd < 0) continue;

            // 如果没有事件，continue
            if ((fds[eventfd].revents & POLLIN) == 0) continue;

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

                // 修改fds数组中clientsock的位置的元素
                fds[clientsock].fd = clientsock;
                fds[clientsock].events = POLLIN;
                fds[clientsock].revents = 0;

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
                    // 关闭客户端的socket
                    close(eventfd);      
                    fds[eventfd].fd = -1;      
                    
                    // 重新计算maxfd的值，注意，只有当eventfd==maxfd时才需要计算
                    if (eventfd == maxfd) {
                        for (int i = maxfd; i > 0; i--) {
                            if (fds[i].fd != -1) {
                                maxfd = i;
                                break;
                            }
                        }
                    }
                } else {
                    // 如果客户端有报文发过来
                    printf("recv(eventfd=%d):%s\n", eventfd, buf);

                    send(eventfd, buf, strlen(buf), 0);
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

