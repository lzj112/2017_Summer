/*************************************************************************
	> File Name: MAX.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月04日 星期五 14时02分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<sys/wait.h>
#include<pthread.h>

pthread_mutex_t mutex;
unsigned long int max,t,sum;


void display_time()
{
    int seconds;
    seconds = time( (time_t *)NULL );
    printf( "Time = %d",seconds );
}

void *thread1(void *arg)
{
    display_time();
    unsigned long int n=*( unsigned long int * )arg;
    t = max/n;
    
    pthread_mutex_lock( &mutex );
    for( ;t>0;t-- )
    {
        sum+=max--;
    }
    pthread_mutex_unlock( &mutex );
    pthread_mutex_destroy( &mutex );

    display_time();
    exit( 0 );
}

int main()
{
    unsigned long int n;
    int status;
    pthread_t tid;
    sum = 0;

    printf( "MAX : " );
    scanf( "%lu",&max );
    printf( "   n : " );
    scanf( "%lu",&n );
    printf( "\n" );
    

    while( n )
    {
        pthread_mutex_init( &mutex,NULL );
        pthread_create( &tid,NULL,(void *)thread1,(void *)&n );
        wait( &status );
        //sleep( 2 );
        n--;
    }
    printf( "1~MAX = %lu\n",sum );
    return 0;
}
