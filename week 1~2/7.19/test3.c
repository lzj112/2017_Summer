/*************************************************************************
	> File Name: test3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 09时01分54秒
 ************************************************************************/
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
            struct passwd *passwd;
            passwd = getpwuid (buf.st_uid);
            printf ("User:\t%s\n", passwd->pw_name);
            struct group *group;
            group = getgrgid (buf.st_gid);
            printf ("Group:\t%s\n", group->gr_name);


}

