// 线程和信号。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void *func(void *arg);
void sigfunc(int sig) {
    printf("sigfunc catch signal %d\n", sig);
}

int main(int argc, char const *argv[])
{
    signal(2, sigfunc);

    // 创建线程
    pthread_t tid;
    if (pthread_create(&tid, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    sleep(5);
    pthread_kill(tid, 15);
    sleep(30);

    int res = 0;

    printf("join...\n");
    res = pthread_join(tid, NULL);
    printf("%d\n", res);
    printf("join ok.\n");

    return 0;
}

// 线程主函数
void *func(void *arg) {
    printf("sleep ....\n");
    sleep(10);
    printf("sleep ok.\n");

    return (void *) 1;
}
