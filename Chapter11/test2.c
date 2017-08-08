/*************************************************************************
	> File Name: test2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月08日 星期二 22时28分59秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>

#define MAX_LINE 1024
int main( int argc,char **argv )
{
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    int sfd;
    int port = 8000;
    char *str = "test string";
    char *serveIP = "127.0.0.1";
    if( argc > 1 )
    {
        str = argv[1];
    }
    sin.sin_family = AF_INET;
    inet_pton( AF_INET,serveIP,(void *)&sin.sin_addr );
    sin.sin_port = htons( port );
    sfd = socket( AF_INET,SOCK_STREAM,0 );
    connect(sfd,(struct sockaddr *)&sin,sizeof(sin));
    printf( "str = %s\n",str );
    printf( "str = %s\n",str );
    write(sfd,str,strlen(str)+1);
    read(sfd,buf,MAX_LINE);
    printf( "recive from serve: %s\n",buf );
    close(sfd);
    return 0;
}
