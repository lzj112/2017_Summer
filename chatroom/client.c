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
#include<signal.h>

#define MAXLEN 1000     //聊天最长输入
#define PORT 4507
#define IP "127.0.0.1"
        

//用户信息
typedef struct a{ 
    int fd;
    int flag;           //标志是登录还是注册
    int login;          //标志各种功能 2为登录成功 其他看menu
    int power;          //权限 能否禁言 踢人
    char txt[100];            //文件传输权限
    char number[10];    //账号
    char passwd[20];    //密码
    char object[10];    //聊天对象
    char pathname[100]; //文件名
    char buf[MAXLEN];   //输入
}user;
 
 
//消息管理
typedef struct b{
    int flag;   //标志是哪一种消息请求
    int fd;
    char buf[MAXLEN];
    struct b *next;
}news;

int chatting;
int chat_flag = 1;
int flag;  //判断客户端是否收到了服务器发来的消息


void delxiaoxi();
void s();
void save_wenjian();
void ask();
void tp();
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
        memset( guy.number,0,sizeof(guy.number) );
        strcpy( guy.number,number );
        switch(choose)
        {
            case 0:
                break;
            case 1: //添加好友
            {
                printf( "\n请输入添加账号：" );
                scanf( "%s",guy.object );       //输入要添加的账号
                if( strcmp(guy.object,guy.number) == 0 )
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
                memset(guy.number,0,sizeof(guy.number));
                strcpy(guy.number,number);
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
            case 6:     //摇一摇
            {
                guy.login = 6;
                send( s_fd,(void *)&guy,sizeof(guy),0 );
                break;
            }
            case 7:        //删除好友
            {
                del_friend();
                break;
            }
            case 8:         //查看聊天记录
            {
                guy.login = 8;
                send( s_fd,(void *)&guy,sizeof(guy),0 );
                break;
            }
            case 9:         //文件传输
            {
                char ch[10];
                printf( "\n\t1.请求对方\n\t2.发送文件\n\t按零返回\n" );
                scanf( "%s",ch );
                while( strcmp(ch,"1")!=0 && strcmp(ch,"2")!=0 && strcmp(ch,"0")!=0 )
                {
                    printf( "choose error\n" );
                    scanf( "%s",ch );
                } 
                if( strcmp(ch,"0") == 0 )
                {
                    break;
                }
                if( strcmp( ch,"1" ) == 0 )
                {
                    ask();
                }
                if( strcmp(ch,"2") == 0 )
                {
                    tp();
                }
                break;
            }
        }
    }
    return 0;
}

int menu()      //主界面
{
    int ch;
    char n[100];

        printf( "\n\t*****************************************\n" );
        printf( "\t\t1.添加好友\n" );
        printf( "\t\t2.打开好友列表\n" );
        printf( "\t\t3.发起私聊\n" );
        printf( "\t\t4.发起群聊\n" );
        printf( "\t\t5.消息管理\n" );
        printf ("\t\t6.摇一摇(附近的人)\n");
        printf( "\t\t7.删除好友\n" );
        printf( "\t\t8.查看聊天记录\n" );
        printf( "\t\t9.文件传输\n" );
        printf( "\t\t按0退出聊天室\n" );
        printf( "\t*****************************************\n" );

        scanf( "%s",n );
        //choose = atoi(n);
       while(strcmp(n,"1")!=0&&strcmp(n,"2")!=0&&strcmp(n,"3")!=0&&strcmp(n,"4")!=0&&strcmp(n,"5")!=0&&strcmp(n,"6")!=0&&strcmp(n,"7")!=0&&strcmp(n,"8")!=0&&strcmp(n,"9")!=0&&strcmp(n,"0")!=0)
       {
           printf( "错误选项，重新选择\n" );
           scanf( "%s",n );
       }
        ch = atoi(n);
   return ch;
}

int log_in()   //登录
{
    int flag;
    guy.flag = 1;
    guy.login = 2;
    char *tmp;

    printf( "请输入账号：\n" );
    scanf( "%s",guy.number );
    tmp = getpass( "请输入密码:\n" );
    strcpy( guy.passwd,tmp );    

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
        printf( "\n*********************\n\t1.登录\n\t2.注册\n\t3.按0退出\n*********************\n" );
        scanf( "%s",ch );
        getchar();
        while( strcmp(ch,"1") != 0 && strcmp( ch,"2" ) != 0 && strcmp( ch,"0" ) != 0 )
        {
            printf( "错误选项，重新选择\n" );
            scanf( "%s",ch );
        }
        if( strcmp(ch,"1") == 0 )   //登录
        {
            n = log_in();
            if( n == 1 )
            {
                break;
            }
            else
                memset( &guy,0,sizeof(guy) );
        }

        if( strcmp(ch,"2") == 0 ) //注册
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
            memset( guy.number,0,sizeof(guy.number) );
            strcpy(guy.number,number);
            printf( "\n" );
            if( guy.login == 1 )  //有好友添加信息
            {
                printf( "\n--->好友添加消息+1>\n" );
                baocun( &guy );
            }
            if( guy.login == 11 )
            {
                printf( "\n--->好友添加消息+1>\n" );
                printf( "%s\n",guy.buf );
            }
            if( guy.login == 111 )
            {
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
                memset( guy.number,0,sizeof(guy.number) );
                strcpy( guy.number,number );

                if( chatting == 0 )
                {
                    printf( "<私聊消息++>\n" );
                    baocun( &guy );
                }
                if( chatting == 1 )     //如果在聊天就打印在屏幕上
                {
                    printf( "%s\n",guy.buf );
                    printf( "输入内容:\n" );
                }
            }
            if( guy.login == 43 )       //群聊消息
            {
                memset( guy.number,0,sizeof(guy.number) );
                strcpy( guy.number,number );
                if( chatting == 1 )     //正在聊天 就答应在屏幕上
                {
                    printf( "%s(%s)\n",guy.buf,guy.object );
                    printf( "输入内容:\n" );
                }
                else
                {
                    printf( "<群消息++>\n" );
                    baocun(&guy);
                }
            }
            
            if( guy.login == 45 )       //展示群成员
            {
                printf( "(%s):%s\n",guy.object,guy.buf );
            }

            if( guy.login == 6 )    //摇一摇
            {
                printf( "%s\n",guy.buf );
            }
            if( guy.login == 8 )    //查看聊天记录
            {
                printf( "%s\n",guy.buf );
            }
            if( guy.login == 9 )    //文件传输的请求
            {
                printf( "<请求回复++>\n" );
                baocun( &guy );
            }
            if( guy.login == 99 )   //请求的回复
            {
                printf( "对于你想给%s传文件对方回复你%s\n",guy.object,guy.buf );
                if( strcmp(guy.buf,"yes") == 0 )
                {
                    char tmp[100] = {0};
                    strcpy(tmp,guy.object);
                    strcat(tmp,guy.buf);
                    strcpy(guy.txt,tmp);
                    
                    baocun(&guy);
                }
            }
            if( guy.login == 999 )  //保存接受的文件
            {
                save_wenjian();
            }
            
            if( guy.login == 123 || guy.login == 456 )      //上下线提醒
            {
                printf( "----->%s\n",guy.buf );
            }
        }
    }
}

void baocun( user *guy )   //保存服务器发来的信息
{
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
    char c[20];
    news *p ;
    while(1)
    {
        printf( "\n********************************" );
        printf("\n\t1.好友添加\n\t2.私聊\n\t3.群聊\n\t4.离线消息\n\t5.请求回复\n\t6.清空消息盒子\n\t按零返回\n");
        scanf( "%s",c );
        getchar();
        while( strcmp(c,"1")!=0 && strcmp(c,"2")!=0 && strcmp(c,"3")!=0 && strcmp(c,"4")!=0 && strcmp(c,"0")!=0 && strcmp(c,"5")!=0&&strcmp(c,"6")!=0 )
        {
            printf( "错误选项\n" );
            scanf( "%s",c );
            getchar();
        }
        
        if( strcmp(c,"0") == 0 )   //按零退出
        { 
            break;
        }
        if( strcmp(c,"1") == 0 )   //处理好友添加的请求
        {
            int t,flag=0;
            char ch[50];
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
            scanf( "%s",ch );
            getchar();
            t = atoi(ch);
            if( t == 0 )
            {
                return ;
            }
            p = head->next;
            while( p )
            {
                if( p->fd == t )
                {
                    flag = 1;
                    break;
                }
                p = p->next;
            }
            if( flag == 0 )
            {
                printf( "无\n" );
                return ;
            }
            printf( "\n%s please input 'y' or 'n'\n",p->buf );
            memset(guy.buf,0,sizeof(guy.buf));
            scanf( "%s",guy.buf );
            guy.fd = p->fd; 
            guy.login = 11;
            send( s_fd,(void *)&guy,sizeof(user),0 );
        }
        
        if( strcmp(c,"2") == 0 )        //私聊消息
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

        if( strcmp(c,"3") == 0 )    //群聊消息
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

        if( strcmp(c,"4") == 0 )  //离线消息
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
        if( strcmp(c,"5") == 0 )    //文件传输请求回复
        {
            guy.login = 99;

            p = head->next;
            while( p )
            {
                if( p->flag == 9 )
                {
                    printf( "%s请按'yes' or 'no'\n",p->buf );
                    memset(guy.buf,0,sizeof(guy.buf));
                    scanf( "%s",guy.buf );
                    getchar();
                    guy.fd = p->fd;
                    send( s_fd,(void *)&guy,sizeof(guy),0 );
                }
                p = p->next;
            }
        }
        if( strcmp(c,"6") == 0 )
        {
            delxiaoxi();
        }
    }
}

void s( int sig )
{
    chat_flag = 0;
}

void person_chat()  //私聊
{
    guy.login = 3;
    chatting = 1;
    chat_flag = 1;
    
    char object[10] = {0};
    printf( "\n********************************\n\tu are talkinggggg~(ctrl+c+Enter退出)\n" );
    printf( "选择聊天对象的账号:\n" );
    scanf( "%s",guy.object );
    getchar();
    strcpy( object,guy.object );

    while( chat_flag )
    {
        signal( SIGINT,s );
        if( chat_flag == 0 )
        {
            break;
        }
        printf( "输入内容:\n" );
        fgets( guy.buf,MAXLEN,stdin );
        strcpy( guy.object,object );
        send( s_fd,(void *)&guy,sizeof(user),0 );        
    }
    chatting = 0;
    chat_flag = 1;
    signal( SIGINT,SIG_DFL );
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
    char object[10];
    char n[50];
    printf( "\n*************************" );
    printf( "\n\t0.这里是消息盒子\n\t1.0返回\n\t2.创建群\n\t3.群聊\n\t4.邀请人进群\n\t5.查看群成员\n\t6.解散群\n" );
    scanf( "%s",n );
    while( strcmp(n,"2")!=0 && strcmp(n,"3") != 0 && strcmp(n,"4")!=0&&strcmp(n,"0")!=0&&strcmp(n,"5")!=0&&strcmp(n,"6")!=0 )
    {
        printf( "错误选项\n" );
        scanf( "%s",n );
    }
    if( strcmp(n,"0") == 0 )
    {
        return ;
    }
    if( strcmp(n,"2") == 0 ) //创建群
    {
        guy.login = 42;
        printf( "输入群账号:\n" );
        scanf( "%s",guy.buf );
        getchar();
        guy.power = 1;
        send( s_fd,(void *)&guy,sizeof(guy),0 );
    }
    if( strcmp( n,"3" ) == 0 )      //群聊
    {
        guy.login = 43;
        printf( "选择群账号:" );
        scanf( "%s",guy.object );
        getchar();
        strcpy(object,guy.object);
        printf( "\n*********************************************\n" );
        printf( "\t\t\t群聊(ctrl+c+Enter退出)\n" );
        while( chat_flag )
        {
            signal( SIGINT,s );
            if( chat_flag == 0 )
            {
                break;
            }
            chatting = 1;
            printf( "输入内容:\n" );
            fgets( guy.buf,4096,stdin );
            strcpy( guy.object,object );

            send( s_fd,(void *)&guy,sizeof(guy),0);
        }
        chatting = 0;
        chat_flag = 1;
    }
    if( strcmp( n,"4" ) == 0 )  //邀请人进群
    {
        guy.login = 44;
        printf( "邀请进的群账号:\n" );
        scanf( "%s",guy.buf );
        getchar();
        printf( "邀请人的账号:\n" );
        scanf( "%s",guy.object );
        getchar();

        send( s_fd,(void *)&guy,sizeof(guy),0 );
    }
    if( strcmp(n,"5") == 0 )    //查看群成员
    {
        guy.login = 45;
        printf( "请输入群账号:\n" );
        scanf( "%s",guy.object );
        send( s_fd,(void *)&guy,sizeof(guy),0 );
    }
    if( strcmp(n,"6") == 0 )    //解散群
    {
        guy.login = 46;
       // if( guy.power == 1 )
        //{
            printf( "输入解散的群号:\n" );
            scanf( "%s",guy.object );
            send( s_fd,(void *)&guy,sizeof(guy),0 );
        /*}
        else
        {
            printf( "只有群主才能这么做\n" );
            return ;
        }*/
    }
}


void ask()      //向对象发出请求传输文件
{
    guy.login = 9;
    char tmp[100] = {0};
    printf( "输入想传输文件的账号;\n" );
    scanf( "%s",guy.object );
    getchar();
    
    strcpy( tmp,guy.number );
    strcat( tmp,"想给你传一份文件" );
    strcpy( guy.buf,tmp );
    
    send( s_fd,(void *)&guy,sizeof(guy),0 );

}

void tp()       //文件传输
{
    char tmp[100] = {0};
    char pathname[50];
    FILE *fp;

    printf( "输入想传输文件的账号:\n" );
    scanf( "%s",guy.object );
    getchar();
    strcpy( tmp,guy.object );
    strcat(tmp,"yes");
    
    if( strcmp(tmp,guy.txt) != 0 )
    {
        printf( "未取得对方同意\n" );
        return ;
    }

    printf( "输入传输的文件名:\n" );
    scanf( "%s",pathname );
    getchar();
    
    fp = fopen( pathname,"rb" );
    if( fp == NULL )
    {
        printf( "找不到该文件\n" );
        return ;
    }

    guy.login = 999;
    strcpy(  guy.pathname,pathname );
    memset( guy.buf,0,sizeof(guy.buf) );

    while( fscanf( fp,"\n%[^\n]",guy.buf) != EOF )
    {
        send( s_fd,(void *)&guy,sizeof(guy),0 );
        usleep(10000);
        memset( guy.buf,0,sizeof(guy.buf) );
    }
    printf( "\n" );
    fclose(fp);
}

void save_wenjian()         //保存接受的文件
{
    FILE *fp;
    strcat(guy.pathname,"...");
    if( (fp = fopen(guy.pathname,"ab")) == NULL )
    {
        fp = fopen(guy.pathname,"wb");
    }
    fprintf( fp,"%s\n",guy.buf );
    fclose(fp);
}

void delxiaoxi()    //清空消息盒子
{
    news *p = head->next;
    news *pp;
    while( p )
    {
        pp = p->next;
        free(p);
        p = pp;
    }
    head->next = NULL;
}
