/*************************************************************************
	> File Name: taxi1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月03日 星期四 21时24分10秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void *traveler_arrive( void *p )
{
    char *name = (char  *)p;
    printf( "Traveler %s needs a taxi now.\n",name );
    pthread_mutex_lock( &mutex );
    pthread_cond_wait( &cond,&mutex );
    pthread_mutex_unlock( &mutex );

    printf( "%s has gotten a taxi now\n",name );
    pthread_exit( 0 );
}

void *taxi_arrive( void *p )
{
    char *name = (char *)p;
    printf( "taxi %s has arrived\n",name );

    pthread_cond_signal( &cond );

    pthread_exit( 0 );
}
int main()
{
    char *name;
    pthread_t tid;
    pthread_mutex_init( &mutex,NULL );
    pthread_cond_init( &cond,NULL );
    
    name = "Jack";
    pthread_create( &tid,NULL,(void *)taxi_arrive,name );
    sleep(1);
    name = "Susan";
    pthread_create( &tid,NULL,(void *)traveler_arrive,name );
    sleep(1);
    name = "Mike";
    pthread_create( &tid,NULL,(void *)taxi_arrive,name );
    sleep(1);
    exit(0);
}
