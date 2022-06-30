// 线程的创建和终止
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int var = 0;

void *thmain1(void *arg);
void *thmain2(void *arg);

int main(int argc, char const *argv[])
{
    pthread_t thid1 = 0; // 线程id typedef unsigned long pthread_t
    pthread_t thid2 = 0; // 线程id typedef unsigned long pthread_t

    // 创建线程
    if (pthread_create(&thid1, NULL, thmain1, NULL) != 0) {
        printf("pthread_create failed.\n");
        exit(-1);
    }

    // 创建线程
    if (pthread_create(&thid2, NULL, thmain2, NULL) != 0) {
        printf("pthread_create failed.\n");
        exit(-1);
    }

    // 等待子线程退出
    printf("join...\n");
    pthread_join(thid1, NULL);
    pthread_join(thid2, NULL);
    printf("join ok.\n");

    return 0;
}

void func1() {
    return;
}

// 线程主函数
void *thmain1(void *arg) {
    for (int i = 0; i < 5; i++) {
        var = i + 1;
        sleep(1);
        printf("pthmain1 sleep(%d) ok.\n", var);
        if (i == 2) {
            func1();
        }
    }
}

void func2() {
    pthread_exit(0);
}

// 线程主函数
void *thmain2(void *arg) {
    for (int i = 0; i < 5; i++) {
        sleep(1);
        printf("pthmain2 sleep(%d) ok.\n", var);
        if (i == 2) {
            func2();
        }
    }
}