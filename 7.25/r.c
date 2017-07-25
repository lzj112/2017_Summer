/*************************************************************************
	> File Name: r.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 15时06分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
int main()
{
    pid_t pid;
    pid=fork();
    if( pid<0 )
    {
        perror("fork error");
        exit(1);
    }
    //子进程
    if( pid == 0 )
    {
        printf(" i am the child process.\n");
        //输出进程ID和父进程ID
        printf(" pid = %d ppid = %d\n",getpid(),getppid());
        printf(" i will sleep 5 seconds.\n");
        //睡眠五秒，保证父进程先退出
        sleep(5);
        printf(" pid = %d  ppid = %d\n",getpid(),getppid());
        printf(" child process is exit\n");
    }
    //父进程
    else 
    {
        printf(" i am the father process\n");
        //父进程睡眠1s,保证子进程输出进程ID
        printf("father process is exit\n");
    }
    return 0;
}

