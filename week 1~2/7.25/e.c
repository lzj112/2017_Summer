/*************************************************************************
	> File Name: e.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 11时02分57秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
int main( int arhc,char **argv,char **env )
{
    pid_t pid;
    int stat_val;
    printf( "Exec example!\n" );
    pid=fork();
    switch( pid )
    {
        case -1:
        perror("process creation failed!\n");
        exit(1);
        case 0:
        printf("child process is running !\n");
        printf("my pid = %d,parent pid = %d\n",getpid(),getpid());
        printf( "uid = %d,gid = %d\n",getuid(),getgid() );
        execve( "d",argv,env );
        printf("process never go to here!\n");
        exit(0);
        default:
        printf("parent process is running\n");
        break;
    }
    wait(&stat_val);
    exit(0);
}
