/*
 * 程序名：demo10.cpp，此程序演示采用开发框架的CTcpServer类实现socket通讯多进程的服务端
 * 作者：wydxry
 * 时间：2022.05.26 16:58
*/

/*
 * 1）在多进程的服务程序中，如果杀掉一个子进程，和这个子进程通讯的客户端会断开，但是，不
 *    会影响其它的子进程和客户端，也不会影响父进程。
 * 2）如果杀掉父进程，不会影响正在通讯中的子进程，但是，新的客户端无法建立连接。
 * 3）如果用killall+程序名，可以杀掉父进程和全部的子进程。
 *
 * 多进程网络服务端程序退出的三种情况：
 * 1）如果是子进程收到退出信号，该子进程断开与客户端连接的socket，然后退出。
 * 2）如果是父进程收到退出信号，父进程先关闭监听的socket，然后向全部的子进程发出退出信号。
 * 3）如果父子进程都收到退出信号，本质上与第2种情况相同。
 * 
 */

#include "../_public.h"

CLogFile logfile; // 服务程序的运行日志
CTcpServer TcpServer; // 创建服务端对象

void FathEXIT(int sig);  // 父进程退出函数
void ChldEXIT(int sig);  // 子进程退出函数

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Using:./demo10 port logfile\nExample:./demo10 5005 /tmp/demo10.log\n\n"); 
        return -1;
    }

    // 关闭全部的信号和输入输出。
    // 设置信号,在shell状态下可用 "kill + 进程号" 正常终止些进程
    // 但请不要用 "kill -9 +进程号" 强行终止
    CloseIOAndSignal(); 
    signal(SIGINT, FathEXIT); 
    signal(SIGTERM, FathEXIT);

    if (logfile.Open(argv[2], "a+") == false) {
        printf("logfile.Open(%s) failed.\n", argv[2]); 
        return -1;
    }

    // 服务端初始化
    if (TcpServer.InitServer(atoi(argv[1])) == false) {
        printf("TcpServer.InitServer(%s) failed.\n", argv[1]); 
        return -1;
    }

    while (true) {
        // 等待客户端的连接请求
        if (TcpServer.Accept() == false) {
            // printf("TcpServer.Accept() failed.\n"); 
            // return -1;
            logfile.Write("TcpServer.Accept() failed.\n"); FathEXIT(-1);
        }

        // printf("客户端（%s）已连接。\n", TcpServer.GetIP());
        logfile.Write("客户端（%s）已连接。\n", TcpServer.GetIP());

        // 父进程继续回到Accept()
        if (fork() > 0) {
            TcpServer.CloseClient(); 
            continue;
        }

        // 子进程重新设置退出信号。
        signal(SIGINT, ChldEXIT); 
        signal(SIGTERM, ChldEXIT);

        TcpServer.CloseListen();

        // 子进程与客户端进行通讯，处理业务
        // 与客户端通讯，接收客户端发过来的报文后，回复"已收到"
        char buf[102400];
        while (1) {
            memset(buf, 0, sizeof buf);
            // 接收客户端的请求报文
            if (TcpServer.Read(buf) == false) {
                perror("recv");
                break;
            }
            printf("服务器端接收信息：%s\n", buf);

            strcpy(buf, "已收到");
            // 向客户端发送响应报文
            if (TcpServer.Write(buf) == false) {
                perror("send");
                break;
            }
            printf("服务器端发送信息：%s\n", buf);
        }

        ChldEXIT(0);
    }
    
    return 0;
}

// 父进程退出函数
void FathEXIT(int sig) {
    // 以下代码是为了防止信号处理函数在执行的过程中被信号中断
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);

    logfile.Write("父进程退出，sig=%d。\n", sig);

    TcpServer.CloseListen();    // 关闭监听的socket

    kill(0, 15); // 通知全部的子进程退出

    exit(0);
}

// 子进程退出函数。
void ChldEXIT(int sig)  
{
  // 以下代码是为了防止信号处理函数在执行的过程中被信号中断。
  signal(SIGINT, SIG_IGN); 
  signal(SIGTERM, SIG_IGN);

  logfile.Write("子进程退出，sig=%d。\n",sig);

  TcpServer.CloseClient();    // 关闭客户端的socket。

  exit(0);
}