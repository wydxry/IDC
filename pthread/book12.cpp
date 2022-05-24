// 线程同步-互斥锁。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int var;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 声明互斥锁

void *func(void *arg);

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁

    // 创建线程
    pthread_t tid1, tid2;
    if (pthread_create(&tid1, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    if (pthread_create(&tid2, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    // 等待子线程
    printf("join...\n");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("join ok.\n");

    printf("var = %d\n", var);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void *func(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex); // 加锁
        var++;
        pthread_mutex_unlock(&mutex); // 解锁
    }
}