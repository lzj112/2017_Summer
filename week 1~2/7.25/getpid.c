/*************************************************************************
	> File Name: getpid.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 15时41分09秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    pid_t pid;
    if( (pid=fork()) == -1)
    {
        printf( "process creation failed\n" );
        exit(1);
    }
    if( pid == 0 )
    {
        printf("pid = %d, ppid = %d\n",getpid(),getppid());
    }
    exit(0);
}
