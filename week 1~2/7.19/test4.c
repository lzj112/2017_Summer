/*************************************************************************
	> File Name: test4.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 09时10分14秒
 *********************************************************************/
#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
int main ()
{
    struct stat buf;        
    stat("/home",&buf);
    int link=buf.st_nlink;
    int size=buf.st_size;
    printf("%d   ",(int)buf.st_nlink);
    printf("%d",(int)buf.st_size);
}

