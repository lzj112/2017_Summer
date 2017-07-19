/*************************************************************************
	> File Name: 789.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 10时51分57秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
//#include<linux.h>
#include<sys/stat.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>
#include<sys/types.h>
int main()
{
    DIR *dir;
    char *p="~/git";
    dir=opendir(p);
    if(dir==NULL)
    perror("open");
    return 0;
}

