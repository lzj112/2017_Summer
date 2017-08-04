/*************************************************************************
	> File Name: t.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月04日 星期五 14时56分25秒
 ************************************************************************/
#include<stdlib.h>
#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <signal.h>
#include <ctype.h> 
int main()
{
    pthread_t tid;
    tid=fork();
    printf( ">%lu<--    ",tid );
    if( tid >0 )
    {
        kill(tid,SIGTERM);
        //signal(tid,SIGTERM);
    }
    printf( "  ---->%lu<",tid );
    exit(0);
}
