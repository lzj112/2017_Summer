/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月08日 星期二 21时19分18秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define MAX_LINE 1024
#define INET_ADDR_STR 16

void  my_fun( char *p )
{
    if( p == NULL )
    {
        return ;
    }
    for( ; *p != '\0'; p++ )
    {
        if((*p >= 'a') && (*p <= 'z'))
        {
            *p = *p -32;
        }
    }
    return ;
}

int main( int argc,char **argv )
{
    struct sockaddr_in sin;
    struct sockaddr_in cin;
    int l_fd;
    int c_fd;
    socklen_t len;
    char buf[MAX_LINE];
    char addr_p[INET_ADDR_STR];
    int port = 8000;
    int n;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    l_fd = socket( AF_INET,SOCK_STREAM,0 );
    bind( l_fd,(struct sockaddr *)&sin,0 );
    listen( l_fd,16 );

    printf( "waitting 0.0!" );
    while(1)
    {
        c_fd = accept( l_fd,(struct sockaddr*)&cin,&len );
        n = read(c_fd,buf,MAX_LINE);
        inet_ntop(AF_INET,&cin.sin_addr,addr_p,INET_ADDR_STR);
        printf( "client IP is %s,port is %d\n",addr_p,ntohs(cin.sin_port) );
        printf( "content is :%s\n",buf );
        my_fun(buf);
        write(c_fd,buf,n);
        close(c_fd);
    }
    printf( "buf = %s\n",buf );
    if( (close(l_fd)) == -1 )
    {
        perror("fail to close\n");
        exit(1);
    }
    return 0;

}
