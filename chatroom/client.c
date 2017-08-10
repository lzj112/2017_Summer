/*************************************************************************
	> File Name: slient.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 08时20分22秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAXLEN 4096     //聊天最长输入
#define PORT 4507
#define IP "127.0.0.1"
        

//用户信息
typedef struct a{          
    int flag;           //标志是登录还是注册
    int login;          //标志登录是否成功
    int power;          //权限 能否禁言 踢人
    char name[50];      //昵称
    char number[10];    //账号
    char passwd[20];    //密码
    char buf[MAXLEN];   //输入
}user;
user guy;


int log_in();
void set_in();
void menu();


int s_fd;

int main()
{
    struct sockaddr_in sin;
    int n;

    memset( &guy,0,sizeof(guy) );   //两个结构体置0
    memset( &sin,0,sizeof(sin) );

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    inet_aton(IP,&sin.sin_addr);

     if( (s_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 )   //建立套接字
    {
        printf( "socket error\n" );
        exit(0);
    }

    if( connect(s_fd,(struct sockaddr *)&sin,sizeof(sin)) )     //连接
    {
        printf( "connect error\n" );
        exit(0);
    }
    
    menu();

}



int log_in()
{
    int flag;
    guy.flag = 1;
    printf( "\t\n请输入账号：\n" );
    scanf( "%s",guy.number );
    printf( "\t\n请输入密码：\n" );
    scanf( "%s",guy.passwd );

    if( send(s_fd,(void *)&guy,sizeof(user),0) < 0 )         //发送
    {
        printf( "client send error\n" );
        exit(0);
    }

    if( recv(s_fd,(void *)&flag,sizeof(flag),0) < 0 )       //接收
    {
        printf( "client recv error\n" );
        exit(0);
    }

    if( flag == 1 )
    {
        printf( "\n\t登陆成功\n" );
        return 1;
    }
    else
        return 0;

}

void set_in()
{
    int flag;
    guy.flag = 2;
    char passwd[20];
    printf( "\t\n请输入账号：" );
    scanf( "%s",guy.number );
    printf( "\t\n请输入密码：" );
    scanf( "%s",guy.passwd );
    printf( "\t\n请确认密码：" );
    scanf( "%s",passwd );
    if( (strcmp(passwd,guy.passwd)) == 0 )
    {
        if( send(s_fd,(void *)&guy,sizeof(user),0) < 0)      //发送
        {
            printf( "set_in send error\n" );
            exit(0);
        }
        if( recv(s_fd,(void *)&flag,sizeof(flag),0) < 0 )    //接收
        {
            printf( "recv error\n" );
            exit(0);
        }
       
        printf( "--->%d<---\n",flag ); //  
        if( flag == 1 )
        {
            printf( "\n\t注册成功\n" );
            return ;
        }
        else
        {
            if( flag == 0 )
                printf( "\n账号已存在 注册失败\n" );
            memset( &guy,0,sizeof(guy) );
            return ;
        }
    }
    else
    {
        printf( "两次密码不同\n" );
        return ;
    }

}



void menu()             //登录界面
{
    int choose;
    while(1)
    {
        int n=0;
        printf( "\n*********************\n\t1.登录\n\t2.注册\n*********************\n" );
        scanf( "%d",&choose );
        while( choose > 2 || choose < 1 )
        {
            printf( "错误选项，重新选择\n" );
            scanf( "%d",&choose );
        }
        if( choose == 1 )   //登录
        {
            n = log_in();
            if( n == 1 )
                break;
            else
                memset( &guy,0,sizeof(guy) );
        }

        if( choose == 2 ) //注册
        {
            set_in();
        }
    }
}
