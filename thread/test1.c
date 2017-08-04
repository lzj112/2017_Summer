/*************************************************************************
	> File Name: test1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月04日 星期五 14时33分28秒
 ************************************************************************/

/*  POSIX 下进程控制的实验程序残缺版 */ 
#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <signal.h>
#include <ctype.h> 
#include<pthread.h>
#include<sys/wait.h>
#include<stdlib.h>
/* 允许建立的子进程个数最大值 */
#define MAX_CHILD_NUMBER 10 
/* 子进程睡眠时间 */
#define SLEEP_INTERVAL 2 
int proc_number=0; 
/* 子进程的自编号，从0开始 */
void do_something(); 

int main(int argc, char* argv[])
{   
    /* 子进程个数 */
    int child_proc_number = MAX_CHILD_NUMBER; 
    int i, ch,status; 
    pid_t  child_pid; 
    pid_t pid[10]={0}; /* 存放每个子进程的id */ 
    if (argc > 1) /* 命令行参数第一个参数表示子进程个数*/ 
    {
        child_proc_number = atoi(argv[1]); 
        child_proc_number= (child_proc_number > 10) ? 10 :child_proc_number;
    }
    printf( "%d\n",child_proc_number );
    for (i=0; i<child_proc_number; i++)
    { 
        child_pid = fork();
        switch( child_pid )
	    {
            case -1:
        	{
            	printf( "process creation failed\n" );
            	exit(1);
        	}
            case 0:
        	{
            	proc_number = i;
                printf( "proc_number  = %d\n",proc_number );
           	    do_something();
            }
            default:
            {
                pid[i] = child_pid;
            }
        }
    }
    /* 让用户选择杀死进程，数字表示杀死该进程，q退出 */
    while ((ch = getchar()) != 'q')  
    { 
        if (isdigit(ch)) 
        {
            int t=ch-'0';
            for(i=0;i<child_proc_number;i++)
            {
                if( pid[i] == t )
                {
                    kill( pid[i],SIGTERM );
                    wait( &status );
                    break;
                }
            }
        }
    } 
    for( i=0;i<child_proc_number;i++ )
    {
        kill( pid[i],SIGTERM );
    }
    return 0;
} 
void do_something() 
{
    int i;
    //for(;;) 
    //{  
        printf("This is process No.%d and its pid is %d\n",   proc_number,  getpid());
        sleep(SLEEP_INTERVAL); // 主动阻塞两秒钟
    //}
}

