/*************************************************************************
	> File Name: chdir.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月26日 星期三 16时36分31秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
    if (chdir(argv[1]) )
    {
        printf(" chdir error\n");
    }
}
