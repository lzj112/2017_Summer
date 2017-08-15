/*************************************************************************
	> File Name: serve.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 08时20分15秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include<errno.h>
#include<signal.h>

#define MAXLINE 20          //listen最大等待队列
#define PORT 4507           //端口号


typedef struct b{           //用户各种信息
    int fd;
    int flag;
    int login;
    int power;
    char name[50];
    char number[10];
    char passwd[20];
    char buf[4096];
}user;

typedef struct a{       //每个人的好友
    char number[10];
    struct a *next;
}fri;


typedef struct c{        //所有在线用户的信息
    int fd;
    int flag;           //标记是否在线
    char number[10];
    char passwd[20];
    struct c *next;
}peo;

typedef struct d{         //用户的离线消息
    char buf[MAXLINE];
    struct d *next;
}off;

user people;
peo *head;
fri *phead;
off *ohead;
char number[50];  //备份自己账号


void wenjian2( char *number );
void wenjian1( char *number );
void look_fri();
void send_offline( int conn_fd );
void take_offline( char *number );
void off_line( user *people );
int check_friend( char *number );
int check_line( char *number );
void take_friend( char *p );
void save_friend( char *number,char *friend );
void xiaxian( int conn_fd );
void reply( user *people );
void take_out();
int check_login( user *people,int conn_fd );
int check_setin( user *people);
void save();
void tianjia( user *people,int conn_fd );
void *menu();

int main()
{
    signal( SIGPIPE,SIG_IGN );
    pthread_t tid;
    struct sockaddr_in cin,sin;
    socklen_t sin_len;
    int conn_fd,sock_fd;
    int optval;
    
    memset( &cin,0,sizeof(cin) );       //置0

    cin.sin_family = AF_INET;
    cin.sin_port = htons(PORT);
    cin.sin_addr.s_addr = htonl(INADDR_ANY);

    head = (peo *)malloc( sizeof(peo) ); //初始化链表头指针
    head->next = NULL;
    phead = (fri *)malloc( sizeof(fri) );
    phead->next = NULL;
    ohead = (off *)malloc( sizeof(off) );
    ohead->next = NULL;

    take_out();  //创建链表取出用户信息存入
    int count = 0; 

    //创建套接字
    if( (sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 )
    {
        printf( "socket error\n" );
        exit(0);
    }

    //设置该套接字市值可以重新绑定端口
    optval = 1;
    if( setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0 )
    {
        printf( "setsockopt error\n" );
    }

    //绑定套接字到本地端口
    if( bind(sock_fd,(struct sockaddr *)&cin,sizeof(struct sockaddr)) < 0 )
    {
        printf( "bind error\n" );
        exit(0);
    }

    //化为监听套接字
    if( listen(sock_fd,MAXLINE) < 0 )
    {
        printf( "listen error\n" );
        exit(0);
    }
    sin_len = sizeof( struct sockaddr_in );
    while( 1 )
    {
        printf( "waittinggggggggggggggg....\n" );

        //接收客户端
        if( (conn_fd = accept(sock_fd,(struct sockaddr *)&sin,&sin_len)) < 0 )
        {
            printf( "accept error \n" );
        }
        
        printf( "有客户端连接\n" );
        
       
        //开辟辅线程处理
        if( pthread_create( &tid,NULL,(void *)menu,(void *)&conn_fd ) != 0 )
        {
            printf( "pthread creation failed\n" );
        }
    }
}

void *menu( void *arg )        //主要函数，调用子函数，进行各种功能都在这里调用子函数完成
{
    int ret,flag;
    memset( &people,0,sizeof(people) );
    int conn_fd = *(int *)arg;
    strcpy( number,people.number );


    //接收数据
    while(1)
    {
        if( (ret = recv( conn_fd,(void *)&people,sizeof(user),0 )) <= 0 )    //接受信息
    	{
            if( errno == EINTR )
            	printf( "接收信号返回　仍然正常\n" );
            else
            {
                xiaxian(conn_fd);
                pthread_exit(0);
            }
        }
        
        if( people.login == 2 )   //请求登录注册
        {
            if( people.flag == 1 ) //登录
            {
                flag = check_login( &people,conn_fd );
                if( flag == 0 )
                {
                    memset( &people,0,sizeof(people) );
                }
                send( conn_fd,(void *)&flag,sizeof(flag),0 );
            }
            
            else if( people.flag == 2 ) //注册
            {
                flag = check_setin( &people );
                if( flag == 1 )     //注册成功了，保存
                {
                    save(head);
                }
                else
                {
                    memset( &people,0,sizeof(people) );
                }
                send( conn_fd,(void *)&flag,sizeof(flag),0 );
            }
        }

        if( people.login == 1 || people.login == 11 )         //请求添加好友
        {
            tianjia(&people,conn_fd);
        }
        
        if( people.login == 22 )    //请求展示好友列表
        {
            take_friend( people.number );        //从文件读取该用户的好友
            look_fri();
            printf( "%d %s",people.login,people.buf );
            send( conn_fd,(void *)&people,sizeof(people),0 );
        }
    }
    pthread_exit(0);
}


void take_out()				//从文件读取用户信息到链表 
{
    int t = 0,count = 0;
	FILE *fp;
	fp=fopen("denglu","r");
	if(fp == NULL)
	{
		printf("takeout error");
		exit(0);
	}
	peo *p1,*p2,*p3;
	p2=p1=(peo *)malloc( sizeof(peo) );
	head->next = p1;
    p3 = head;
    rewind( fp );   //确保文件指针在开头
	while(fscanf(fp,"%d %d %s %s",&p1->fd,&p1->flag,p1->number,p1->passwd)!=EOF)
	{
        t = 1;
		p1=(peo *)malloc( sizeof(peo) );
		p2->next = p1;
		p2=p1;
        p3 = p3->next;
	}
    if( t == 0 )
    {
        head->next = NULL;
    }
    p3->next = NULL;
    p1 = NULL;
    p2 = NULL;
    fclose(fp);
}

void save()           //保存用户信息到文件
{
    FILE *fp;
	fp=fopen("denglu","w");
    if(fp == NULL)
    {
        printf("save error");
        exit(0);
    }
    peo *p=head->next;
	while(p)
    {
        fprintf(fp,"%d %d %s %s\n",p->fd,p->flag,p->number,p->passwd);
        p=p->next;
    }
    fclose(fp);
}




int check_setin( user *people)   //注册账号密码写入链表
{

    peo *p = head->next;
    peo *p2 = head;
    peo *p1=(peo *)malloc( sizeof(peo) );
    
    while( p )
    {
        if( strcmp(p->number,people->number) == 0 )
        {
            printf( "账号已被使用\n" );
            return 0; 
        }
        p2 = p2->next;
        p = p->next;
    }
    
    strcpy( p1->number,people->number );
    strcpy( p1->passwd,people->passwd );
    p1->fd = 0;
    p1->flag = 0;
    p2-> next = p1;
    p1->next =NULL;

    return 1;
 }

int check_login( user *people,int conn_fd )       //登录
{
    int flag = 0;
    peo *p = head->next;

    while( p)
    {
        if( (strcmp(p->number,people->number)) == 0 )       //账号存在
        {
            flag = 1;
            break;
        }
        p = p->next;
    }
    if( flag == 0 )
    {
        printf ("账号不存在\n");
        return 0;
    }
    if( (strcmp(p->passwd,people->passwd)) != 0 )
    {
        printf( "密码不正确\n" );
        return 0;
    }

    if( p->flag == 1 )
    {
        return 0;
    }
    printf( "成功登录\n" );
    
    wenjian1( p->number );   
    wenjian2( p->number );
   // take_friend( p->number );        //从文件读取该用户的好友
    
    take_offline( p->number );       //检查是否有离线消息
    if( ohead->next != NULL )        //存在离线消息
    {
        send_offline( conn_fd ); 
    }
    p->flag = 1;   //登陆成功即在线
   
    p->fd = conn_fd;  //保存套接字
   
    return 1;
}

void  xiaxian( int conn_fd )         //若有用户下线　链表里的fd置为-1
{
    peo *p = head->next;
    while( p )
    {
        if( p->fd == conn_fd )
        {
            break;
        }
        p = p->next;
    }
    p->fd = -1;
    p->flag = 0;
}

int check_line( char *number )     //检查对方是否离线
{
    peo *p = head->next;
    while( p )
    {
        if( strcmp( p->number,number ) == 0 && p->flag == 0)     //离线
        {
            return 0;
        }
        else if( strcmp( p->number,number ) == 0 && p->flag == 1 )   //在线
        {
            return 1;
        }
        p = p->next;
    }
    return -1;    //没有这个账号
}


void  reply( user *people )     //对于添加好友的回复
{
    peo *p = head->next;
    
    while( p )
    {
        if( p->fd == people->fd )
        {
            break;
        }
        p = p->next;
    }

    if( strcmp(people->buf,"y") == 0 )
    {
        save_friend( people->number,p->number );    //保存他到你的好友
        save_friend( p->number,people->number );

        memset( people->buf,0,sizeof(people->buf) );
        strcpy(people->buf,"你已经添加");
        strcat(people->buf,people->number);
        strcat(people->buf,"为好友");
        send(people->fd,people,sizeof(user),0);
    }
    else if( strcmp(people->buf,"n") == 0 )
    {
        memset( people->buf,0,sizeof(people->buf) );
        strcpy(people->buf,"你被");
        strcat(people->buf,people->number);
        strcat(people->buf,"丑拒了");
        send( people->fd,people,sizeof(user),0 );
    }
        
}


void tianjia( user *people,int conn_fd )      //添加好友
{

    if( people->login == 11 )
    {
        reply( people );
        return ;
    }
    int t = 0;
    peo *p = head->next;
    while( p )        //找该账号
    {
        if( strcmp( p->number,people->buf ) == 0 )          
        {
            t = 1;
            break;
        }
        p = p->next;
    }
    if( t == 0 )
    {
        memset( people->buf,0,sizeof(people->buf) );   
        strcpy( people->buf,"number error" ); 
        send( conn_fd,(void *)people,sizeof(user),0 );
        return ;
    }
    else 
    {
        int ret;
        ret = check_friend( p->number );  //检查是否已经添加对方为好友
        if( ret == 1 )
        {
            memset( people->buf,0,sizeof(people->buf) );
            strcpy( people->buf,"对方已经是你的好友" );
            send( conn_fd,(void *)people,sizeof(user),0 );
            return ;
        }

        memset( people->buf,0,sizeof(people->buf) );
        strcat( people->buf,people->number );
        strcat( people->buf," wants to be friend with u~" );
        people->fd = conn_fd;

        ret = check_line( p->number );  //检查对方是否在线
        if( ret == -1 )      //无该账号
        {
            return ;
        }
        if( ret == 0 )    //离线，把消息存起来
        {
            off_line( people );
            return ;
        }
    
        if( send( p->fd,people,sizeof(user),0 ) < 0) //给想添加的账号发送请求
        {
            printf( "niang类 原来是这里错了\n" );
        }
    }
}

void save_friend( char *number,char *friend )      //保存每个账号的好友到文件
{
    FILE *fp;
    fp = fopen( number,"a+" );
    if( fp == NULL )
    {
        printf( "save_friend fopen error\n" );
        return ;
    }
    fprintf( fp,"%s\n",friend );
    fclose( fp );
}

void  take_friend( char *p )         //从文件读取每个人的好友
{
    int t = 0;
    FILE *fp;
	fp=fopen( p,"r" );
	if(fp == NULL)
	{
		printf("take_friend error\n");
		return ;
	}
	fri *p1,*p2,*p3;
	p2=p1=(fri *)malloc( sizeof(fri) );
	phead->next = p1;
    p3 = phead;
    rewind( fp );    //确保文件指针在开头
	while( fscanf(fp,"%s",p1->number) != EOF )
	{
        t = 1;
		p1=(fri *)malloc( sizeof(fri) );
		p2->next = p1;
		p2=p1;
        p3 = p3->next;
	}
    if( t == 0 )
    {
        phead->next = NULL;
    }
    p3->next = NULL;
    p1 = NULL;
    p2 = NULL;
    fclose(fp);
    
}

int check_friend( char *number )          //检查是否已经添加对方为好友
{
    fri *p = phead->next;
    while( p )
    {
        if( strcmp( p->number,number ) == 0 )
        {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

void off_line( user *people )     //保存该用户离线消息到文件
{
    char p[50]={0};
    strcpy( p,people->number );
    strcpy( p,"off-line" );
    FILE *fp;
    fp = fopen( p,"w" );
    if( fp == NULL )
    {
        printf( "off_line fopen error\n" );
    }
    fprintf( fp,"%s\n",people->buf );
    fclose(fp);
}

void take_offline( char *number )           //从文件读取离线信息到链表
{
    char p[50]={0};
    strcpy( p,number );
    strcat( p,"off-line" );

    off *p1,*p2;
    p2 = p1 = (off *)malloc( sizeof(off) );
    ohead->next = p1;
    
    int t = 0;
    FILE *fp;
    fp = fopen( p,"r" );
    if( fp == NULL )
    {
        printf( "take_offline fopen error\n" );
    }

    rewind(fp);
    while( fscanf( fp,"%s",p1->buf ) != EOF )
    {
        t = 1;
        p1 = (off *)malloc( sizeof(off) );
        p2->next = p1;
        p2 = p1;
    }
    p1 = NULL;
    p2 = NULL;

    if( t == 0 )
    {
        ohead->next = NULL;
    }

    fclose( fp );
}

void send_offline( int conn_fd )        //发送离线消息到该用户
{
    off *p = ohead->next;
    while( p )
    {
        memset( people.buf,0,sizeof(people.buf) );
        strcpy(people.buf,p->buf);
        send( conn_fd,(void *)&people,sizeof(user),0);
        p = p->next;
    }
    memset( people.buf,0,sizeof(people.buf) );
}

void look_fri()         //把好友信息放到buf里
{
    fri *p = phead->next;
    memset( people.buf,0,sizeof(people.buf) );
    while( p )
    {
        strcat( people.buf,p->number );
        strcat( people.buf,"\n" );
        p = p->next;
    }
}

void wenjian1( char *number )  //检查有没有存离线消息和好友的文件没有就创建
{
    char p[50]={0};
    strcpy( p,number );
    FILE *fp;
    if( (fp = fopen(p,"r")) == NULL )
    {
        fp = fopen( p,"wa+" );
        fclose(fp);
   }
    else
        return ;
}
void wenjian2( char *number )
{
    char p[50]={0};
    strcpy( p,number );
    strcat( p,"off-line" );
    FILE *fp;
    if(( fp = fopen( p,"r" )) == NULL)
    {
        fp = fopen( p,"w+" );
        fclose( fp );
    }
    else 
    return ;
}
