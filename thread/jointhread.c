/*************************************************************************
	> File Name: jointhread.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月31日 星期一 15时44分53秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void assisthread( void *arg )
{
    printf( "i am helping to do some jobs\n" );
    sleep(3);
    pthread_exit(0);
}
int main()
{
    pthread_t assistthid;
    int status;

    pthread_creat( &assistthid,NULL,(void *)assisthread,NULL );
    pthread_join( assistthid,(void *)&status );
    printf( "assisthread's exit is casued %d\n",status );
    
    return 0;
}
