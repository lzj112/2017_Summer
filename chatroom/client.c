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
#include<pthread.h>
#include<arpa/inet.h>
#include<signal.h>

#define MAXLEN 4096     //聊天最长输入
#define PORT 4507
#define IP "127.0.0.1"
        

//用户信息
typedef struct a{ 
    int fd;
    int flag;           //标志是登录还是注册
    int login;          //标志各种功能 2为登录成功 其他看menu
    int power;          //权限 能否禁言 踢人
    char name[50];      //昵称
    char number[10];    //账号
    char passwd[20];    //密码
    char object[10];    //聊天对象
    char buf[MAXLEN];   //输入
}user;
 
 
//消息管理
typedef struct b{
    int flag;   //标志是哪一种消息请求
    int fd;
    char buf[MAXLEN];
    struct b *next;
}news;


int flag;  //判断客户端是否收到了服务器发来的消息


void group_chat();
void look_precord( );
void del_friend();
void person_chat();
int log_in();
void set_in();
int denglu();
int menu();
void *request();
void baocun( user *guy );
void xiaoxi();

pthread_t tid;
int s_fd;
user guy;
news *head,*p1,*p2; 
char number[50];      //备份账号

int main()
{
    signal( SIGPIPE,SIG_IGN );
    struct sockaddr_in sin;
    int n,choose,ret;
    
    memset( &guy,0,sizeof(guy) );   //两个结构体置0
    memset( &sin,0,sizeof(sin) );
    
    head = (news *)malloc( sizeof(news) );  //初始化头指针
    head->next = NULL;
    p1 = head;
    p2 = head;

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
    
    ret = denglu();  //登录

    strcpy( number,guy.number );


    if( ret == 0 )
    {
        return 0;
    }

    pthread_create( &tid,NULL,(void *)request,NULL );

    while( choose = menu() )    //主界面，各种功能
    {
        
        switch(choose)
        {
            case 0:
                break;
            case 1: //添加好友
            {
                printf( "\n请输入添加账号：" );
                scanf( "%s",guy.buf );       //输入要添加的账号
                if( strcmp(guy.buf,guy.number) == 0 )
                {
                    printf( "长点心　这是你自己...\n" );
                    break;
                }
                guy.login = 1;
                if( send( s_fd,(void *)&guy,sizeof(guy),0 ) < 0 )
                {
                    printf( "case 1 send error\n" );
                    exit(0);
                }
                break;
            }
            case 2:         //好友列表
            {
                guy.login = 22;
                send( s_fd,(void *)&guy,sizeof(guy),0 );
                break;
            }
            case 3:         //私聊
            {
                person_chat();
                break;
            }
            case 4:         //群聊
            {
                group_chat();
                break;
            }
            case 5:   //消息管理
            {
                xiaoxi();
                break;
            }
            case 7:        //删除好友
            {
                del_friend();
                break;
            }
        }
    }
    return 0;
}

int menu()      //主界面
{
    int n;

        printf( "\n\t*****************************************\n" );
        printf( "\t\t1.添加好友\n" );
        printf( "\t\t2.打开好友列表\n" );
        printf( "\t\t3.发起私聊\n" );
        printf( "\t\t4.发起群聊\n" );
        printf( "\t\t5.消息管理\n" );
        printf ("\t\t6.摇一摇(附近的人)\n");
        printf( "\t\t7.删除好友\n" );
        printf( "\t\t按0退出聊天室\n" );
        printf( "\t*****************************************\n" );
        printf("menu===\n");
        scanf( "%d",&n );
       while( n>7 || n<0 )
       {
           printf( "错误选项，重新选择\n" );
           scanf( "%d",&n );
       }
       return n;
}

int log_in()   //登录
{
    int flag;
    guy.flag = 1;
    guy.login = 2;

    printf( "\t\n请输入账号：\n" );
    scanf( "%s",guy.number );
    printf( "\t\n请输入密码：\n" );
    scanf( "%s",guy.passwd );
    
    printf( "%s %s\n",guy.number,guy.passwd);
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
        printf( "\n登陆成功\n" );
        return 1;
    }
    else
        return 0;

}

void set_in()       //注册
{
    int flag;
    guy.flag = 2;
    guy.login = 2;

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



int denglu()             //登录界面
{
    char ch[50];
    while(1)
    {
        int n=0;
        printf( "\n*********************\n\ta.登录\n\tb.注册\n\tc.按0退出\n*********************\n" );
        scanf( "%s",ch );
        getchar();
        while( strcmp(ch,"a") != 0 && strcmp( ch,"0" ) != 0 && strcmp( ch,"b" ) != 0 )
        {
            printf( "错误选项，重新选择\n" );
            scanf( "%s",ch );
        }
        if( strcmp(ch,"a") == 0 )   //登录
        {
            n = log_in();
            if( n == 1 )
            {
                break;
            }
            else
                memset( &guy,0,sizeof(guy) );
        }

        if( strcmp(ch,"b") == 0 ) //注册
        {
            set_in();
        }
        if( strcmp( ch,"0" ) == 0 )
        {
            return 0;
        }
    }
    return 1;
}

void *request( void *arg )    //接收别的客户端发来的请求 添加好友 聊天什么的
{
    int ret;
    while(1)
    {
        if( (ret = recv( s_fd,(void *)&guy,sizeof(user),0 )) >0  )
        {
            if( guy.login == 1 )  //有好友添加信息
            {
                printf( "\n--->消息+1>  " );
                printf( "%s \n",guy.buf );
                memset( guy.number,0,sizeof(guy.number) );
                strcpy( guy.number,number );
                baocun( &guy );
            }
            else if( guy.login == 11 )
            {
                printf( "\n--->消息+1>  " );
                printf( "%s\n",guy.buf );
            }
            if( guy.login == 22 )     //展示好友
            {
                printf( "你的好友有：\n" );
                printf( "%s",guy.buf );
            }
            if( guy.login == 0 )   //有离线消息
            {
                printf("<离线消息++>\n");
                baocun( &guy );
            }
            if( guy.login == 3 )  //私聊消息
            {
                printf( "<私聊消息++>\n" );
                baocun( &guy );
            }
            if( guy.login == 43 )       //群聊消息
            {
                printf( "<群消息++>\n" );
                baocun( &guy );
            }
        }
    }
}

void baocun( user *guy )   //保存服务器发来的信息
{
    //printf( "%d %s\n",guy->login,guy->buf );
    p1 = (news *)malloc( sizeof(news) );
    p2->next = p1;
    p1->flag = guy->login;
    p1->fd = guy->fd;
    strcpy( p1->buf,guy->buf );
    p2 = p1;
    p1->next = NULL;
    p2->next = NULL;
}

void xiaoxi()   //在主线程处理服务器发来的消息
{
    int t;
    int n;
    news *p ;
    while(1)
    {
        printf("\n********************\n\t1.好友添加\n\t2.私聊\n\t3.群聊\n\t4.离线消息\n\t5.按零退出返回上一级菜单\n");
        scanf( "%d",&n );
        getchar();
        while( n>4 || n<0 )
        {
            printf( "错误选项\n" );
            scanf( "%d",&n );
            getchar();
        }
        
        if( n == 0 )   //按零退出
        { 
            break;
        }
        
        if( n == 1 )   //处理好友添加的请求
        {
            int t;
            p = head->next;
            while( p)
            {
                if( p->flag == 1 )
                {
                    printf( "\n<%d> :  %s\n",p->fd,p->buf );
                }
                p = p->next;
            }
            printf( "请输入对应编号处理:(或按零返回上层页面)\n" );
            scanf( "%d",&t );
            if( t == 0 )
            {
                return ;
            }
            p = head->next;
            while( p )
            {
                if( p->fd == t )
                {
                    break;
                }
                p = p->next;
            }
            printf( "\n%s please input 'y' or 'n'\n",p->buf );
            memset(guy.buf,0,sizeof(guy.buf));
            scanf( "%s",guy.buf );
            guy.login = 11;
            send( s_fd,(void *)&guy,sizeof(user),0 );
        }
        
        if( n == 2 )        //私聊消息
        {
            p = head->next;
            while( p )
            {
                if( p->flag == 3 )
                {
                    printf( "%s\n",p->buf );
                }
                p = p->next;
            }
            break;
        }

        if( n == 3 )    //群聊消息
        {
            p = head->next;
            while( p )
            {
                if( p->flag == 43 )
                {
                    printf( "%s\n",p->buf );
                }
                p = p->next;
            }
            break;
        }

        if( n == 4 )  //离线消息
        {
            p = head->next;
            while( p )
            {
                if( p->flag == 0 )
                    printf( "%s\n",p->buf );
                p = p->next;
            }
            break;
        }
    }
}

void person_chat()  //私聊
{
    guy.login = 3;
    printf( "\n********************************\n\tu are talkinggggg~\n" );
    printf( "选择聊天对象的账号:\n" );
    scanf( "%s",guy.object );
    getchar();
    printf( "输入内容:" );
    fgets( guy.buf,MAXLEN,stdin );
    send( s_fd,(void *)&guy,sizeof(user),0 );
}

void del_friend()     //删除好友
{
    char ch;
    guy.login = 7;
    printf( "输入删除好友账号:\n" );
    scanf( "%s",guy.buf );
    getchar();
    
    printf( "你确认要删除它么 'y' or 'n'\n" );
    ch = getchar();
    if( ch == 'n' )
    {
        return ;
    }
    if( ch == 'y' )
    {
        send( s_fd,(void *)&guy,sizeof(guy),0 );
    }
}
void group_chat()       //群聊
{
    char n[50];
    printf( "\n*************************" );
    printf( "\n\t1.查看加入的群\n\t2.创建群\n\t3.群聊\n\t4.邀请人进群\n" );
    scanf( "%s",n );
    while( strcmp(n,"1")!=0 && strcmp(n,"2")!=0 && strcmp(n,"3") != 0 && strcmp(n,"4")!=0 )
    {
        printf( "错误选项\n" );
        scanf( "%s",n );
    }

    if( strcmp(n,"1") == 0 )  //查看已加入的群
    {
        guy.login = 41; 
        
    }
    if( strcmp(n,"2") == 0 ) //创建群
    {
        guy.login = 42;
    }
    if( strcmp( n,"3" ) == 0 )      //群聊
    {
        guy.login = 43;
        printf( "选择群账号:" );
        scanf( "%s",guy.object );
        getchar();
        printf( "输入内容:\n" );
        fgets( guy.buf,4096,stdin );

        send( s_fd,(void *)&guy,sizeof(guy),0);
    }
    if( strcmp( n,"4" ) == 0 )  //邀请人进群
    {
        guy.login = 44;
    }
}


//void look_precord(  )  //查看聊天记录

