/*
 * 程序名：demo16.cpp，此程序演示HTTP服务端，接收http请求报文
 * 作者：wydxry
 * 时间：2022.06.01 17:38
*/

#include "../_public.h"

bool SendHtmlFile(const int sockfd,const char *filename);

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Using:./demo16 port\nExample:./demo16 8080\n\n"); 
        return -1;
    }

    CTcpServer TcpServer;

    // 服务端初始化
    if (TcpServer.InitServer(atoi(argv[1])) == false) {
        printf("TcpServer.InitServer(%s) failed.\n", argv[1]); 
        return -1;
    }

    // 等待客户端的连接请求
    if (TcpServer.Accept() == false) {
        printf("TcpServer.Accept() failed.\n"); 
        return -1;
    }

    printf("客户端（%s）已连接。\n", TcpServer.GetIP());

    char buf[102400];
    memset(buf, 0, sizeof buf);

    // 接收http客户端发送过来的报文
    recv(TcpServer.m_connfd, buf, 1000, 0);

    printf("%s\n", buf);

    // 先把响应报文头部发送给客户端
    memset(buf, 0, sizeof buf);
    sprintf(buf,\
            "HTTP/1.1 200 OK\r\n"\
            "Server: demo16\r\n"\
            "Content-Type: text/html;charset=utf-8\r\n"\
            "\r\n");
            // "Content-Length: 108909\r\n\r\n");
    
    if (Writen(TcpServer.m_connfd, buf, strlen(buf)) == false) return -1;

    // logfile.Write("%s", buf);

    // 再把html文件的内容发送给客户端。
    SendHtmlFile(TcpServer.m_connfd, "SURF_ZH_20211203191856_28497.csv");

    return 0;
}

// 把html文件的内容发送给客户端
bool SendHtmlFile(const int sockfd,const char *filename) {
    int bytes = 0;
    char buf[5000];

    FILE *fp = NULL;

    if ((fp = FOPEN(filename, "rb")) == NULL) return false;

    while (true) {
        memset(buf, 0, sizeof buf);
        
        if ((bytes = fread(buf, 1, 5000, fp)) == 0) break;

        if (Writen(sockfd, buf, bytes) == false) {
            fclose(fp);
            fp = NULL;
            return false;
        }
    } 

    fclose(fp);

    return true;
}