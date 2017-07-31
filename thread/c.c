/*************************************************************************
	> File Name: c.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月31日 星期一 11时35分53秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int main()
{
    pthread_t thid;
    thid = pthread_self();
    printf( "%d",pthread_equal(1,pthread_self()) );
    return 0;
}
