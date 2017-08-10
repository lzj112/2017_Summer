/*************************************************************************
	> File Name: fork3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 16时25分33秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
    pid_t pid;
    pid = fork();
    switch( pid )
    {
        case 0:
            while(1)
            {
                printf("a background process,pid :%d\n,parabtID: %d\n",getpid(),getppid());
                sleep(1);
            }
        case -1:
            perror("process creation failed\n");
            exit(-1);
        default:
            printf("i am parent process ,my pid is :%d\n",getpid());
            exit(0);
    }
    return 0;
}
