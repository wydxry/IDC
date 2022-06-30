// 线程参数的传递（用强制转换的方法传变量的值）。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int var;

void *thmain1(void *arg);
void *thmain2(void *arg);
void *thmain3(void *arg);
void *thmain4(void *arg);
void *thmain5(void *arg);

int main(int argc, char const *argv[])
{
    // 线程id typedef unsigned long pthread_t
    pthread_t tid1 = 0, tid2 = 0, tid3 = 0, tid4 = 0, tid5 = 0;

    // 创建线程
    var = 1;
    if (pthread_create(&tid1, NULL, thmain1, (void *)(long)var) != 0) {
        printf("pthread_craete failed.\n");
        exit(-1);
    }

    var = 2;
    if (pthread_create(&tid2, NULL, thmain2, (void *)(long)var) != 0) {
        printf("pthread_craete failed.\n");
        exit(-1);
    }
    
    var = 3;
    if (pthread_create(&tid3, NULL, thmain3, (void *)(long)var) != 0) {
        printf("pthread_craete failed.\n");
        exit(-1);
    }

    var = 4;
    if (pthread_create(&tid4, NULL, thmain4, (void *)(long)var) != 0) {
        printf("pthread_craete failed.\n");
        exit(-1);
    }

    var = 5;
    if (pthread_create(&tid5, NULL, thmain5, (void *)(long)var) != 0) {
        printf("pthread_craete failed.\n");
        exit(-1);
    }

    // 等待子线程退出
    printf("join...\n");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    printf("join ok.\n");

    return 0;
}

// 线程主函数
void *thmain1(void *arg) {
    printf("var1 = %d\n", (int)(long)arg);
    printf("线程1开始运行\n");
}

// 线程主函数
void *thmain2(void *arg) {
    printf("var2 = %d\n", (int)(long)arg);
    printf("线程2开始运行\n");
}

// 线程主函数
void *thmain3(void *arg) {
    printf("var3 = %d\n", (int)(long)arg);
    printf("线程3开始运行\n");
}

// 线程主函数
void *thmain4(void *arg) {
    printf("var4 = %d\n", (int)(long)arg);
    printf("线程4开始运行\n");
}

// 线程主函数
void *thmain5(void *arg) {
    printf("var5 = %d\n", (int)(long)arg);
    printf("线程5开始运行\n");
}
