// 线程资源的回收，用pthread_join非分离的线程。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *func1(void *arg);
void *func2(void *arg);

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2;
    
    // 创建线程。
    if (pthread_create(&tid1, NULL, func1, NULL)!=0) { 
        printf("pthread_create failed.\n"); 
        exit(-1); 
    }
    if (pthread_create(&tid2, NULL, func2, NULL)!=0) { 
        printf("pthread_create failed.\n"); 
        exit(-1); 
    }

    sleep(10);

    void *ret;
    printf("join...\n");
    
    int result = 0;
    result = pthread_join(tid2, &ret);
    printf("tid2 result = %d, ret = %ld\n", result, ret);
    result = pthread_join(tid1, &ret);
    printf("tid1 result = %d, ret = %ld\n", result, ret);

    ret = 0;
    result = pthread_join(tid2, &ret);   
    printf("thid2 result = %d, ret = %ld\n", result, ret);
    result = pthread_join(tid1, &ret);   
    printf("thid1 result = %d, ret = %ld\n", result, ret);
    printf("join ok.\n");


    return 0;
}

void *func1(void *arg) {
    for (int i = 0; i < 5; i++) {
        sleep(1);
        printf("func1 sleep(%d) ok.\n", i+1);
    }
    return (void *) 1;
}

void *func2(void *arg) {
    for (int i = 0; i < 5; i++) {
        sleep(1);
        printf("func2 sleep(%d) ok.\n", i+1);
    }
    return (void *) 2;
}
