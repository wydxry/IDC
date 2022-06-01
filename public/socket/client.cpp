/*
 * 程序名：client.cpp，此程序用于演示I/O复用客户端
 * 作者：wydxry
 * 时间：2022.06.01 21:42
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// 初始化服务端的监听端口
int initserver(int port);

int main(int argc, char const *argv[])
{
    if (argc != 3) { 
        printf("usage:./client ip port\n");
        return -1; 
    }

    int sockfd;
    struct sockaddr_in servaddr;
    char buf[1024];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket() failed.\n"); 
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        printf("connect(%s:%s) failed.\n", argv[1], argv[2]); 
        close(sockfd);  
        return -1;
    }
 
    printf("connect ok.\n");

    int bufsize = 0;
    socklen_t optlen = sizeof(bufsize);
    // 获取接收缓冲区的大小
    getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &bufsize, &optlen);
    printf("recv bufsize = %d\n", bufsize);
    // 获取发送缓冲区的大小
    getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &bufsize, &optlen);
    printf("send bufsize = %d\n", bufsize);

    for (int i = 0; i < 5000000000; i++) {
        // 从命令行输入内容。
        memset(buf, 0, sizeof(buf));
        printf("please input:"); 
        scanf("%s", buf);
        // strcpy(buf,"1111111111111111111111111");

        if (send(sockfd, buf, strlen(buf), 0) <= 0) {
            printf("write() failed.\n");  
            close(sockfd);  
            return -1;
        }

        memset(buf, 0, sizeof buf);
        if (recv(sockfd, buf, sizeof(buf), 0) <= 0) {
            printf("read() failed.\n");  
            close(sockfd);  
            return -1;
        }

        printf("recv:%s\n",buf);
    }

    return 0;
}
