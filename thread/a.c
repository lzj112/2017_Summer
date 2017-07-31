/*************************************************************************
	> File Name: a.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月31日 星期一 10时19分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int *thread( void *arg )
{
    pthread_t new;
    new = pthread_self();
    printf( "this is a new thread, thread id = %lu\n",new );
    return NULL;
}
int main( void )
{
    pthread_t thid;
    printf( "main thread,id is %lu\n",pthread_self() );
    if( pthread_create( &thid,NULL,(void *)thread,NULL ) != 0 )
    {
        printf( "thread creation faild\n" );
        exit(1);
    }
    sleep( 1 );
    exit(0);
}
