/*************************************************************************
	> File Name: taxi2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月03日 星期四 21时39分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

void *taxi_arrive( void *p )
{
    char *name = (char *)p;

    printf( "taxi %s has arrived and waitting\n",name );
    
    pthread_mutex_lock( &mutex );
    pthread_cond_wait( &cond,&mutex );
    pthread_mutex_unlock( &mutex );

    printf( "taxi %s has left with a clientele\n",name );
    pthread_exit(0);
}

void *traveler_arrive( void *p )
{
    char *name = ( char * )p;

    printf( "traveler %s has arrived\n",name );

    pthread_cond_signal( &cond );
    pthread_exit(0);
}

int main()
{
    char *name;
    pthread_t tid;
    pthread_mutex_init( &mutex,NULL );
    pthread_cond_init( &cond,NULL );
    
    name="jack";
    pthread_create( &tid,NULL,taxi_arrive,name );
   // sleep(1);
    name="susan";
    pthread_create( &tid,NULL,traveler_arrive,name );
    sleep(1);
    name="mike";
    pthread_create( &tid,NULL,taxi_arrive,name );
    sleep(1);
    return 0;

}
