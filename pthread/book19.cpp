// 只用信号量实现高速缓存。
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <semaphore.h>
#include <vector>
using namespace std;

struct st_message
{
    int msgid;  // 消息的id
    char message[1024]; // 消息的内容
}stmsg;

void incache(int sig);
void *outcache(void *arg);

vector<struct st_message> vcache;  // 用vector容器做缓存

sem_t notify, lock;     // 声明信号量

int main(int argc, char const *argv[])
{
    signal(15, incache); // 接收15的信号，调用生产者函数

    sem_init(&notify, 0, 0);   // 初始化通知的信号量，第3个参数为0
    sem_init(&lock, 0, 1);     // 初始化加锁的信号量，第3个参数为1

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

    sem_destroy(&notify);
    sem_destroy(&lock);

    return 0;
}

// 生产者、数据入队
void incache(int sig) {
    static int msgid = 1; // 消息的计数器

    static st_message stmsg; // 消息内容
    memset(&stmsg, 0, sizeof(struct st_message));

    sem_wait(&lock);
    
    // 生产数据，放入缓存队列
    for (int i = 0; i < 4; i++) {
        stmsg.msgid = msgid++;
        vcache.push_back(stmsg);
    }

    sem_post(&lock);
    // sem_post函数的作用是给信号量的值加上一个“1”，它是一个“原子操作”
    // 即同时对同一个信号量做加“1”操作的两个线程是不会冲突的；而同时对同一个文件进行读、加和写操作的两个程序就有可能会引起冲突

    for (int i = 0; i < 4; i++) {
        sem_post(&notify); // 把信号量的值加1，将唤醒消费者线程
    }
    
}

// 消费者、数据出队线程的主函数
void *outcache(void *arg) {

    struct st_message stmsg; // 用于存放出队的消息
    
    while (true) {
        sem_wait(&lock); // 给缓存队列加锁
        
        // 如果缓存队列为空，等待，用while防止条件变量虚假唤醒
        while (vcache.empty()) {
            sem_post(&lock);              // 给缓存队列解锁
            sem_wait(&notify);            // 等待信号量的值大于0
            sem_wait(&lock);              // 给缓存队列加锁
        }

        // 从缓存队列中获取第一条记录，然后删除该记录
        memcpy(&stmsg, &vcache[0], sizeof(struct st_message)); // 内存拷贝
        vcache.erase(vcache.begin());

        sem_post(&lock); // 给缓存队列解锁
        
        // 以下是处理业务的代码。
        printf("phid = %ld, mesgid = %d\n", pthread_self(), stmsg.msgid);
        usleep(100);
    }
} 