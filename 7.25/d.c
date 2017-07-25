/*************************************************************************
	> File Name: d.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 10时57分36秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main( int argc,char **argv,char **env )
{
    int i;
    printf( "i am a process image!\n" );
    printf( "My pid =%d ,paraentpid =%d\n",getpid(),getppid());
    printf( "uid = %d ,gid = %d\n",getuid(),getgid() );
    for( i=0; i<argc; i++ )
    {
        printf( "argv[%d] : %s\n",i,*argv );
    }

}
