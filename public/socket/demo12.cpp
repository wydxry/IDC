/*
 * 程序名：demo12.cpp，此程序用于演示网银APP软件的服务端
 * 作者：wydxry
 * 时间：2022.05.26 20:13
*/

#include "../_public.h"

CLogFile logfile; // 服务程序的运行日志
CTcpServer TcpServer; // 创建服务端对象

bool bsession = false; // 客户端是否已登录：true-已登录;false-未登录或登录失败

void FathEXIT(int sig); // 父进程退出函数
void ChldEXIT(int sig); // 子进程退出函数

// 处理业务的主函数
bool _main(const char *recvbuf, char *sendbuf); 

// 登录业务处理函数
bool srv001(const char *recvbuf, char *sendbuf);

// 查询余额业务处理函数
bool srv002(const char *recvbuf, char *sendbuf);

// 转账业务
bool srv003(const char *recvbuf, char *sendbuf);

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Using:./demo12 port logfile\nExample:./demo12 5005 /tmp/demo12.log\n\n");
        return -1;
    }

    // 关闭全部的信号和输入输出。
    // 设置信号,在shell状态下可用 "kill + 进程号" 正常终止些进程
    // 但请不要用 "kill -9 +进程号" 强行终止
    CloseIOAndSignal(); 
    signal(SIGINT, FathEXIT); 
    signal(SIGTERM, FathEXIT);

    // 写日志
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
            logfile.Write("TcpServer.Accept() failed.\n");
            FathEXIT(-1);
        }
        
        // printf("客户端（%s）已连接。\n", TcpServer.GetIP());
        logfile.Write("客户端（%s）已连接。\n", TcpServer.GetIP());
        
        // 父进程继续回到Accept()
        if (fork() > 0) {
            TcpServer.CloseClient();
            continue;
        }

        // 子进程重新设置退出信号
        signal(SIGINT, ChldEXIT); 
        signal(SIGTERM, ChldEXIT);

        TcpServer.CloseListen();

        // 子进程与客户端进行通讯，处理业务
        // 与客户端通讯，接收客户端发过来的报文后，回复"已收到"
        char recvbuf[1024], sendbuf[1024];

        while (1) {
            memset(recvbuf, 0, sizeof recvbuf);
            memset(sendbuf, 0, sizeof sendbuf);

            // 接收客户端的请求报文
            if (TcpServer.Read(recvbuf) == false) {
                perror("recv");
                break;
            }
            
            // printf("服务器端接收信息：%s\n", recvbuf);
            logfile.Write("服务器端接收信息：%s\n", recvbuf);

            // 处理业务的主函数
            if (_main(recvbuf, sendbuf) == false) {
                perror("_main()");
                break;
            }

            // 向客户端发送响应报文
            if (TcpServer.Write(sendbuf) == false) {
                perror("send");
                break;
            }

            // printf("服务器端发送信息：%s\n", sendbuf);
            logfile.Write("服务器端发送信息：%s\n", sendbuf);
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

// 子进程退出函数
void ChldEXIT(int sig)  
{
  // 以下代码是为了防止信号处理函数在执行的过程中被信号中断。
  signal(SIGINT, SIG_IGN); 
  signal(SIGTERM, SIG_IGN);

  logfile.Write("子进程退出，sig=%d。\n",sig);

  TcpServer.CloseClient();    // 关闭客户端的socket。

  exit(0);
}

// 处理业务的主函数
bool _main(const char *recvbuf, char *sendbuf) {
    // 解析recvbuf, 获取服务代码（业务代码）
    int isrvcode = -1;

    cout << "isrvcode: " << isrvcode << endl;

    GetXMLBuffer(recvbuf, "srvcode", &isrvcode);

    if ((isrvcode != 1) && (bsession == false)) {
        strcpy(sendbuf, "<retcode>-1</retcode><message>用户未登录。</message>"); 
        return true;
    }

    cout << "isrvcode: " << isrvcode << endl;

    // 处理每种业务
    switch (isrvcode)
    {
        case 1:   // 登录。
            srv001(recvbuf, sendbuf); 
            break;
        case 2:   // 查询余额。
            srv002(recvbuf, sendbuf); 
            break;
        case 3:   // 转账。
            srv003(recvbuf, sendbuf); 
            break;
        default:
            logfile.Write("业务代码不合法：%s\n", recvbuf) ; 
            return false;
    }

    return true;
}

// 登录
bool srv001(const char *recvbuf, char *sendbuf) {
    // <srvcode>1</srvcode><tel>1392220000</tel><password>123456</password>

    // 解析recvbuf，获取业务参数
    char tel[21], passwd[31];
    GetXMLBuffer(recvbuf, "tel", tel, 20);
    GetXMLBuffer(recvbuf, "password", passwd, 30);

    logfile.Write("tel: %s\n", tel);
    logfile.Write("password: %s\n", passwd);
    
    printf("tel: %s\n", tel);
    printf("password: %s\n", passwd);

    // 处理业务
    // 把处理结果存入sendbuf中
    if ((strcmp(tel, "1392220000") == 0) && (strcmp(passwd, "123456") == 0)) {
        strcpy(sendbuf, "<retcode>0</retcode><message>成功。</message>");
        bsession = true;
    } else {
        strcpy(sendbuf, "<retcode>-1</retcode><message>失败。</message>");
    }

    return true;
}

// 查询余额业务处理函数
bool srv002(const char *recvbuf, char *sendbuf) {
    // <srvcode>2</srvcode><cardid>62620000000001</cardid>

    // 解析recvbuf，获取业务参数
    char cardid[31];
    GetXMLBuffer(recvbuf, "cardid", cardid, 30);

    // 处理业务
    // 把处理结果存入sendbuf中
    if (strcmp(cardid, "62620000000001") == 0) {
        strcpy(sendbuf, "<retcode>0</retcode><message>成功。</message><ye>100.58</ye>");
    } else {
        strcpy(sendbuf, "<retcode>-1</retcode><message>失败。</message>");
    }
    return true;
}

// 转账
bool srv003(const char *recvbuf, char *sendbuf) {
    
    // 编写转账业务的代码
    strcpy(sendbuf, "<retcode>0</retcode><message>成功。</message><ye>100.58</ye>");
    return true;
}