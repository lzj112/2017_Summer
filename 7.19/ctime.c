/*************************************************************************
	> File Name: ctime.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 09时36分02秒
 ************************************************************************/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include <grp.h>
int main ()
{
    char time[64]; 
    struct stat buf;        
    stat("/home",&buf);
    strcpy(time,ctime(&buf.st_mtime));
    time[strlen(time)-1]='\0';
 printf("%s",time);
  //  for(int i=0;i<strlen(time);i++)
    //printf("%c",time[i]);
}

