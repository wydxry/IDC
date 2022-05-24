// 线程的取消。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *func(void *arg); // 线程主函数

int var = 0;

int main(int argc, char const *argv[])
{
    pthread_t tid;

    // 创建线程
    if (pthread_create(&tid, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    usleep(100);
    pthread_cancel(tid);

    int res = 0;
    void *ret;
    printf("join...\n");
    res = pthread_join(tid, &ret);   
    printf("thid result = %d, ret = %ld\n", res, ret);
    printf("join ok.\n");

    printf("var = %d\n", var);

    return 0;
}

// 线程主函数
void *func(void *arg) {
    // pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    
    for (var = 0; var < 4000; var++) {
        pthread_testcancel();
    }
    return (void *) 1;
}
