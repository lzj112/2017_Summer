/*************************************************************************
	> File Name: diffork.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 17时12分00秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int globvar = 5;
int main( void )
{
    pid_t pid;
    int var = 1;
    int i;
    printf("fork is different with vfork\n");

    //pid=fork();
    pid = vfork();
    switch (pid)
    {
        case 0:
        i=3;
        while(i-->0)
        {
            printf("child is running\n");
            globvar++;
            var++;
            sleep(1);
        }
        printf("child globvar = %d,var = %d\n",globvar,var);
        exit(0);
        case -1:
            perror("process creationg failed\n");
            exit(1);
        default:
        i=5;
        while(i-->0)
        {
            printf("parent is running\n");
            globvar++;
            var++;
            sleep(1);
        }
        printf("parent globvar = %d ,var = %d\n",globvar,var);
        exit(0);
    }
}
