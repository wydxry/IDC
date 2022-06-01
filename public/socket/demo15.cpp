/*
 * 程序名：demo15.cpp，此程序演示采用开发框架的CTcpServer类实现socket通讯多线程的服务端
 * 作者：wydxry
 * 时间：2022.06.01 17:10
*/

#include "../_public.h"

// 服务程序的运行日志
CLogFile logfile;

// 创建服务端对象
CTcpServer TcpServer;

// 进程的退出函数
void EXIT(int sig);

// 用于锁定vthid的自旋锁
pthread_spinlock_t vthidlock;  

// 存放全部线程id的容器
vector<pthread_t> vthid;       

// 线程主函数
void *thmain(void *arg);       

// 线程清理函数
void thcleanup(void *arg);     

int main(int argc, char const *argv[])
{   
    if (argc != 3) {
        printf("Using:./demo15 port logfile\nExample:./demo15 5005 /tmp/demo15.log\n\n"); 
        return -1;
    }

    // 关闭全部的信号和输入输出。
    // 设置信号,在shell状态下可用 "kill + 进程号" 正常终止些进程
    // 但请不要用 "kill -9 +进程号" 强行终止
    CloseIOAndSignal(); 
    signal(SIGINT, EXIT); 
    signal(SIGTERM, EXIT);

    if (logfile.Open(argv[2], "a+") == false) { 
        printf("logfile.Open(%s) failed.\n", argv[2]); 
        return -1; 
    }

    // 服务端初始化
    if (TcpServer.InitServer(atoi(argv[1])) == false) {
        logfile.Write("TcpServer.InitServer(%s) failed.\n", argv[1]); 
        return -1;
    }

    pthread_spin_init(&vthidlock, 0);

    while (true) {
        // 等待客户端的连接
        if (TcpServer.Accept() == false) {
            logfile.Write("TcpServer.Accept() failed.\n"); 
            EXIT(-1);
        }

        logfile.Write("客户端（%s）已连接。\n", TcpServer.GetIP());

        // 创建一个新的线程，让它与客户端通讯
        pthread_t tid;
        if (pthread_create(&tid, NULL, thmain, (void *)(long)TcpServer.m_connfd) != 0) {
            logfile.Write("pthread_create() failed.\n"); 
            TcpServer.CloseListen(); 
            continue;
        }

        pthread_spin_lock(&vthidlock);
        // 把线程id放入容器
        vthid.push_back(tid);
        pthread_spin_unlock(&vthidlock);


    }


    return 0;
}

void EXIT(int sig) {
    // 以下代码是为了防止信号处理函数在执行的过程中被信号中断。
    signal(SIGINT, SIG_IGN); 
    signal(SIGTERM, SIG_IGN);

    logfile.Write("进程退出，sig=%d。\n", sig);

    // 关闭监听的socket
    TcpServer.CloseListen();    

    // 取消全部的线程
    for (int i = 0; i < vthid.size(); i++) {
        pthread_cancel(vthid[i]);
    }

    // for (auto& t: vthid) {
    //     pthread_cancel(t);
    // }

    // 让子线程有足够的时间退出
    sleep(1);        

    pthread_spin_destroy(&vthidlock);

    exit(0);
}

// 线程主函数
void *thmain(void *arg) {
    // 把线程清理函数入栈（关闭客户端的socket）
    pthread_cleanup_push(thcleanup, arg);

    // 客户端的socket
    int connfd = (int)(long)arg; 

    // 线程取消方式为立即取消
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);   

    // 把线程分离出去
    pthread_detach(pthread_self());  

    // 子线程与客户端进行通讯，处理业务。
    int  ibuflen;
    char buf[102400];

    // 与客户端通讯，接收客户端发过来的报文后，回复ok
    while (true) {
        memset(buf, 0, sizeof buf);
        
        // 接收客户端的请求报文
        if (TcpRead(connfd, buf, &ibuflen, 30) == false) break; 
        logfile.Write("接收：%s\n", buf);

        strcpy(buf, "ok");
        // 向客户端发送响应结果
        if (TcpWrite(connfd, buf)==false) break; 
        logfile.Write("发送：%s\n", buf);
    }

    // 关闭客户端的连接
    close(connfd);

    // 把本线程id从存放线程id的容器中删除
    pthread_spin_lock(&vthidlock);

    for (int i = 0; i < vthid.size(); i++) {
        if (pthread_equal(pthread_self(), vthid[i])) { 
            vthid.erase(vthid.begin() + i); 
            break; 
        }
    }

    pthread_spin_unlock(&vthidlock);

    // 把线程清理函数出栈
    pthread_cleanup_pop(1); 
             
}

// 线程清理函数
void thcleanup(void *arg) {
    // 关闭客户端的socket
    close((int)(long)arg);

    logfile.Write("线程%lu退出。\n", pthread_self());
}