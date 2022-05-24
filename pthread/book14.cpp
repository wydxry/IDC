// 线程同步-读写锁。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER; // 声明读写锁并初始化

void handle(int sig); // 信号15的处理函数

void *func(void *arg); // 线程主函数

int main(int argc, char const *argv[])
{
    signal(15, handle); // 设置信号15的处理函数

    pthread_t tid1, tid2, tid3;

    // 创建线程
    if (pthread_create(&tid1, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    sleep(1);

    if (pthread_create(&tid2, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    sleep(1);

    if (pthread_create(&tid3, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    // 等待子线程退出
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    pthread_rwlock_destroy(&rwlock); // 销毁锁
    return 0;
}

void *func(void *arg) {
    for (int i = 0; i < 100; i++) {
        printf("线程%lu开始申请读锁...\n", pthread_self());
        pthread_rwlock_rdlock(&rwlock); // 加锁
        printf("线程%lu开始申请读锁成功\n\n", pthread_self());
        sleep(5);
        pthread_rwlock_unlock(&rwlock); // 解锁
        printf("线程%lu已释放读锁\n\n", pthread_self());
        if (i == 3) sleep(8);
    }
}

void handle(int sig) { // 信号15的处理函数
    printf("开始申请写锁...\n");
    pthread_rwlock_wrlock(&rwlock); // 加锁
    printf("申请写锁成功\n\n");
    sleep(10);
    pthread_rwlock_unlock(&rwlock); // 解锁
    printf("写锁已释放\n\n");
}


