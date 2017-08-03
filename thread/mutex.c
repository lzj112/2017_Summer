/*************************************************************************
	> File Name: mutex.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月01日 星期二 09时42分48秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

pthread_mutex_t mutex;          //初始化锁

void print(char *p)
{
    pthread_mutex_lock( &mutex ); //上锁
    printf("%s\n",p);
    pthread_mutex_unlock( &mutex ); //解锁
}

void *thread1( void *arg )
{
    char *p="hellow";
    print(p);
}

void *thread2(void *arg )
{
    char *p="world";
    print( p );
}

int mian()
{
    pthread_t tid1,tid2;

    pthread_mutex_init(&mutex, NULL); //初始化互斥锁 

    pthread_create(&tid1,NULL,thread1,NULL);
    pthread_create(&tid2,NULL,thread2,NULL);

    pthread_mutex_destroy( &mutex );        //销毁锁
    pthread_exit(0);
   // return 0;
}
