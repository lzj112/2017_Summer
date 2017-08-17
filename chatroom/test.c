/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月17日 星期四 15时18分55秒
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
int flag;
void s()
{
    flag = 0;
}
int main()
{
    flag = 1;
    while(flag)
    {
        printf( "===========\n" );
        signal(SIGINT,s);
        sleep(2);
    }
    printf( "-------------\n" );
    return 0;
}
