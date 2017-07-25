/*************************************************************************
	> File Name: wait.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 15时20分17秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    pid_t pid;
    char *msg;
    int k,exit_code;
    printf( "study how to exit code\n" );
    pid = fork();
    switch( pid )
    {
        case 0:
            msg="child process is running\n";
            k=20;
            exit_code=37;
            break;
        case -1:
            perror( "process creation failed\n" );
            exit(1);
        default:
            exit_code=0;
            break;
    }
    //父子进程都会执行下段代码，子进程pid为0，父进程pid为子进程的id
    if( pid != 0 )
    {
        int stat_val;
        pid_t child_pid;
        child_pid=wait( &stat_val );
        printf( "child process has exited,pid = %d\n",child_pid );
        if( WIFEXITED( stat_val ) )
        {
            printf( "child process with code %d\n",WEXITSTATUS( stat_val ) );
        }
        else 
        {
            printf( "child process exited abnormally\n" );
        }
    }
    else 
    {
        while( k-->0 )
        {
            puts(msg);
            sleep(1);
        }
    }
    exit( exit_code );
}
