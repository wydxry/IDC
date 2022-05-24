// 线程参数的传递（用结构体的地址传递多个参数）。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct st_args
{
    int number; // 线程编号
    char name[20]; // 线程名
};

void *func(void *arg);

int main(int argc, char const *argv[])
{
    
    pthread_t tid = 0; // 线程id typedef unsigned long pthread_t

    // 创建线程
    struct st_args *stargs = new struct st_args;
    stargs->number = 10;
    strcpy(stargs->name, "一个线程");
    if (pthread_create(&tid, NULL, func, stargs) != 0) {
        printf("pthread_create failed.\n");
        exit(-1);
    }

    // 等待子线程退出
    printf("join...\n");
    pthread_join(tid, NULL);
    printf("join...\n");

    return 0;
}

void *func(void *arg) {
    struct st_args *p = (struct st_args *) arg;
    printf("number = %d, name = %s\n", p->number, p->name);
    delete p;
    printf("线程开始运行\n");
}