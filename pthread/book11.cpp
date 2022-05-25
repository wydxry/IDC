// 线程安全
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <atomic>
#include <iostream>

void *func(void *arg);

// int var = 0;
std::atomic<int> var;

int main(int argc, char const *argv[])
{
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

    // 等待子线程退出。
    printf("join...\n");
    pthread_join(tid1, NULL);  
    pthread_join(tid2, NULL);
    printf("join ok.\n");

    // printf("var = %d\n", var);
    
    std::cout << "var = " << var << std::endl;

    return 0;
}

// 线程主函数
void *func(void *arg) {
    for (int i = 0; i < 100000; i++) {
        var++;
        // __sync_fetch_and_add(&var, 1);
    }
}