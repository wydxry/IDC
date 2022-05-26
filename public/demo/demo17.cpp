/*
 * 程序名：demo17.cpp，此程序演示开发框架中的CTimer类（计时器）的用法
 * 作者：wydxry
 * 时间：2022.05.26 10:56
 */

#include "../_public.h"

int main(int argc, char const *argv[])
{
    CTimer Timer;
    
    printf("elapsed = %lf\n", Timer.Elapsed()); // elapsed = 0.000000
    sleep(1); 
    printf("elapsed = %lf\n", Timer.Elapsed()); // elapsed = 1.000863
    sleep(1);
    printf("elapsed = %lf\n", Timer.Elapsed()); // elapsed = 1.000792
    usleep(1000);
    printf("elapsed = %lf\n", Timer.Elapsed()); // elapsed = 0.002004
    usleep(100);
    printf("elapsed = %lf\n", Timer.Elapsed()); // elapsed = 0.000554
    usleep(10);
    printf("elapsed = %lf\n", Timer.Elapsed()); // elapsed = 0.000436
    return 0;
}
