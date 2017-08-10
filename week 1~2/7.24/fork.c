/*************************************************************************
	> File Name: fork.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 15时55分07秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main( void )
{
    pid_t pid;
    printf( "Process CreationStudy\n" );
    pid = fork();
    switch(pid){
        case 0:
        printf("case 0 son:%d father :%d\n",pid,getppid());
        break;
        case -1:
        perror( "failed\n" );
        break;
        default:
        printf( "default son: %d father : %d\n",pid,getppid() );
        break;
    }
    exit(0);
}
