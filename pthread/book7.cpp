// 线程资源的回收（分离线程）。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *func(void *arg);

int main(int argc, char const *argv[])
{
    pthread_t tid;
    pthread_attr_t attr; // 申明线程属性的数据结构。
    pthread_attr_init(&attr); // 初始化
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); // 设置线程的属性
    
    // 创建线程。
    if (pthread_create(&tid, &attr, func, NULL) !=0 ) { 
        printf("pthread_create failed.\n"); 
        exit(-1); 
    }
    
    pthread_attr_destroy(&attr); // 销毁数据结构

    // pthread_detach(pthread_self());

    sleep(5);

    int res = 0;
    void *ret;

    printf("join...\n");
    res = pthread_join(tid, &ret); 
    printf("tid result = %d, ret = %ld\n", res, ret);
    printf("join ok.\n");

    return 0;
}

// 线程主函数
void *func(void *arg) {
    pthread_detach(pthread_self());

    for (int i = 0; i < 3; i++) {
        sleep(1); 
        printf("func sleep(%d) ok.\n", i+1);
    }
    return (void *) 1;
}