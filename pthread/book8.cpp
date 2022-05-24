// 线程资源的回收（线程清理函数）。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *func(void *arg);
void thcleanup1(void *arg); // 线程清理函数1
void thcleanup2(void *arg); // 线程清理函数2
void thcleanup3(void *arg); // 线程清理函数3

int main(int argc, char const *argv[])
{
    pthread_t tid;
    
    // 创建线程
    if (pthread_create(&tid, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    int res = 0;
    void *ret;
    printf("join...\n");
    res = pthread_join(tid, &ret);
    printf("tid result = %d , ret = %ld\n", res, ret);
    printf("join ok.\n");

    return 0;
}

// 线程主函数
void *func(void *arg) {
    pthread_cleanup_push(thcleanup1, NULL); // 把线程清理函数1入栈（关闭文件指针）
    pthread_cleanup_push(thcleanup2, NULL); // 把线程清理函数2入栈（关闭socket）
    pthread_cleanup_push(thcleanup3, NULL); // 把线程清理函数3入栈（回滚数据库事务）

    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf("func sleep(%d) ok.\n", i + 1);
    }

    pthread_cleanup_pop(3);
    pthread_cleanup_pop(2);
    pthread_cleanup_pop(1);
}

void thcleanup1(void *arg) {
    // 在这里释放关闭文件、断开网络连接、回滚数据库事务、释放锁等等。
    printf("cleanup1 ok.\n");
};

void thcleanup2(void *arg) {
    // 在这里释放关闭文件、断开网络连接、回滚数据库事务、释放锁等等。
    printf("cleanup2 ok.\n");
};

void thcleanup3(void *arg) {
    // 在这里释放关闭文件、断开网络连接、回滚数据库事务、释放锁等等。
    printf("cleanup3 ok.\n");
};



