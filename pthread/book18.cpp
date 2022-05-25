// 用互斥锁和条件变量实现高速缓存。
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <vector>
using namespace std;

void incache(int sig);
void *outcache(void *arg);

// 缓存队列消息的结构体
struct st_message
{
    int msgid;  // 消息的id
    char message[1024]; // 消息的内容
}stmsg;

vector<struct st_message> vcache; // 用vector容器做缓存

pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // 声明条件变量并初始化
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 声明互斥锁并初始化

int main(int argc, char const *argv[])
{
    signal(15, incache);

    // 创建三个消费者线程
    pthread_t tid1, tid2, tid3;

    if (pthread_create(&tid1, NULL, outcache, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    if (pthread_create(&tid2, NULL, outcache, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    if (pthread_create(&tid3, NULL, outcache, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}

// 生产者、数据入队
void incache(int sig) {
    static int msgid = 1; // 消息的计数器

    static st_message stmsg; // 消息内容
    memset(&stmsg, 0, sizeof(struct st_message));

    pthread_mutex_lock(&mutex); // 给消息队列加锁

    // 生产数据，放入缓存队列
    for (int i = 0; i < 4; i++) {
        stmsg.msgid = msgid++;
        vcache.push_back(stmsg);
    }

    pthread_mutex_unlock(&mutex); // 给缓存队列解锁

    // pthread_cond_signal(&cond);    // 发送条件信号，激活一个线程
    pthread_cond_broadcast(&cond); // 发送条件信号，激活全部的线程
}


void thcleanup(void *arg) {
    // 在这里释放关闭文件、断开网络连接、回滚数据库事务、释放锁等等。
    printf("cleanup ok.\n");

    pthread_mutex_unlock(&mutex);

    /*
    A condition  wait  (whether  timed  or  not)  is  a  cancellation  point. When the cancelability type of a thread is set to PTHREAD_CAN_CEL_DEFERRED, a side-effect of acting upon a cancellation request while in a condition wait is that the mutex is (in effect)  re-acquired before  calling the first cancellation cleanup handler. The effect is as if the thread were unblocked, allowed to execute up to the point of returning from the call to pthread_cond_timedwait() or pthread_cond_wait(), but at that point notices  the  cancellation  request  and instead  of  returning to the caller of pthread_cond_timedwait() or pthread_cond_wait(), starts the thread cancellation activities, which includes calling cancellation cleanup handlers.
    意思就是在pthread_cond_wait时执行pthread_cancel后，
    要先在线程清理函数中要先解锁已与相应条件变量绑定的mutex，
    这样是为了保证pthread_cond_wait可以返回到调用线程。
    */
}


// 消费者、数据出队线程的主函数
void *outcache(void *arg) {
    pthread_cleanup_push(thcleanup, NULL); // 把线程清理函数入栈

    struct st_message stmsg; // 用于存放出队的消息
    
    while (true) {
        pthread_mutex_lock(&mutex); // 给缓存队列加锁
        
        // 如果缓存队列为空，等待，用while防止条件变量虚假唤醒
        while (vcache.empty()) {
            pthread_cond_wait(&cond, &mutex);
        }

        // 从缓存队列中获取第一条记录，然后删除该记录
        memcpy(&stmsg, &vcache[0], sizeof(struct st_message)); // 内存拷贝
        vcache.erase(vcache.begin());

        pthread_mutex_unlock(&mutex); // 给缓存队列解锁
        
        // 以下是处理业务的代码。
        printf("phid = %ld, mesgid = %d\n", pthread_self(), stmsg.msgid);
        usleep(100);
    }

    printf("\n");

    pthread_cleanup_pop(1);  // 把线程清理函数出栈
} 