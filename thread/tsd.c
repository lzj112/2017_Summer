/*************************************************************************
> File Name: tsd.c
> Author: 
> Mail: 
> Created Time: 2017年07月31日 星期一 22时39分40秒
************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_key_t key;

void *thread2( void *arg )
{
    int tsd = 5;

    printf( "thread2 %lu is running \n",pthread_self() );
    pthread_setspecific( key,&tsd );
    printf( "thread2 %lu returns %d\n",pthread_self(),*(int *)pthread_getspecific(key) );

}

void *thread1( void *arg )
{
    int tsd = 0;
    pthread_t thid2;

    printf( "thread1 %lu is running\n",pthread_self() );
    pthread_setspecific( key,&tsd );
    pthread_create( &thid2,NULL,thread2,NULL );
    sleep( 3 );
    printf( "thread1 %lu returns %d\n",pthread_self(),*(int *)pthread_getspecific(key) );
}
int main()
{
    pthread_t thid1;
    int statl;
    printf( "main thread begins running\n" );
    pthread_key_create( &key,NULL );
    pthread_create( &thid1,NULL,thread1,NULL );
    sleep(5);
    pthread_key_delete(key);
    printf( "main thread exit\n" );
    //    pthread_join(thid1,NULL);
    return 0;
}
