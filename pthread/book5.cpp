// 线程线程退出（终止）的状态。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct st_ret
{
    int ret_code; // 返回代码
    char message[1024]; // 返回内容
};

void *func(void *arg);

int main(int argc, char const *argv[])
{
    pthread_t tid = 0;

    // 创建线程
    if (pthread_create(&tid, NULL, func, NULL) != 0) {
        printf("pthread_create failed.\n"); 
        exit(-1);
    }

    // 等待子线程退出
    struct st_ret *p = 0;
    pthread_join(tid, (void **)&p);
    printf("retcode = %d, message = %s\n", p->ret_code, p->message);
    delete p;
    printf("join ok.\n");

    return 0;
}

// 线程主函数
void *func(void *arg) {
    printf("线程开始运行。\n");

    // 注意，如果用结构体的地址作为线程的返回值，必须保存在线程主函数结束后地址仍是有效的。
    // 所以，要采用动态分配内存的方法，不能用局部变量。
    struct st_ret *ret = new struct st_ret;
    ret->ret_code = 123;
    strcpy(ret->message,"测试内容。");

    pthread_exit((void *)ret);
}