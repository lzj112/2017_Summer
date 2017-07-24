/*************************************************************************
	> File Name: fork2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 16时07分50秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
    pid_t pid;
    char *m;
    int k;
    printf("process careation\n");
    pid=fork();
    switch(pid)
    {
        case 0:
        m="child process is running";
        k=3;
        break;
        case -1:
        perror("process creation failed\n");
        break;
        default:
        m="parent process is running";
        k=5;
        break;
    }
    while(k>0)
    {
        puts(m);
        sleep(1);
        k--;
    }
    exit(0);
}
