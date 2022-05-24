// 线程同步-信号量。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int var;

sem_t sem; // 声明信号量

void *func(void *arg); // 线程主函数

int main(int argc, char const *argv[])
{   
    sem_init(&sem, 0, 1); // 初始化信号量
    // sem_init(&sem, 1, 2); // 初始化信号量

    pthread_t tid1, tid2;

    // 创建线程
    if (pthread_create(&tid1, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    if (pthread_create(&tid2, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    // 等待子线程退出
    printf("join...\n");
    pthread_join(tid1, NULL);  
    pthread_join(tid2, NULL);  
    printf("join ok.\n");

    printf("var = %d\n", var);

    // sem_destroy(&sem);  // 销毁信号量

    return 0;
}

// 线程主函数
void *func(void *arg) {
    for (int i = 0; i < 10000000; i++) {
        sem_wait(&sem); // 加锁
        var++;
        sem_post(&sem); // 解锁
    }
}