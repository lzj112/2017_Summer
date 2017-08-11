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

#define MAXLINE 20          //listen最大等待队列
#define PORT 4507           //端口号

pthread_mutex_t mutex;

typedef struct b{
    int flag;
    int login;
    int power;
    char name[50];
    char number[10];
    char passwd[20];
    char buf[4096];
}user;


typedef struct c{
    int fd;
    int flag;           //标记是否在线
    char number[10];
    char passwd[20];
    struct c *next;
}peo;

peo *head;
pthread_mutex_t mutex;

void *menu();
void take_out( peo *head );
int check_login( user *people,peo *head,int conn_fd );
int check_setin( user *people,peo *head );
void save( peo *head );
void tianjia( user *people,peo *head,int conn_fd );

int main()
{
    pthread_t tid;
    struct sockaddr_in cin,sin;
    socklen_t sin_len;
    int conn_fd,sock_fd;
    
    memset( &cin,0,sizeof(cin) );       //置0

    cin.sin_family = AF_INET;
    cin.sin_port = htons(PORT);
    cin.sin_addr.s_addr = htonl(INADDR_ANY);

    head = (peo *)malloc( sizeof(peo) ); //初始化
    head->next = NULL;
    take_out( head );  //保存登录信息到文件


    //创建套接字
    if( (sock_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 )
    {
        printf( "socket error\n" );
        exit(0);
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
    user people;
    memset( &people,0,sizeof(people) );
    int conn_fd = *(int *)arg;
    
    
    //接收数据
    while(1)
    {
        if( (ret = recv( conn_fd,(void *)&people,sizeof(user),0 )) <= 0 )
    	{
        	printf( "recv error\n" );
            exit(0);
            //判断不在线的函数
        }
        if( people.login == 2 )
        {

            
          /*  peo *p =head->next; 
            while( p->next )
            {
                printf( "number = %s passwd = %s\n",p->number,p->passwd );
                p = p->next;
            }*/

            if( people.flag == 1 ) //登录
            {
                flag = check_login( &people,head,conn_fd );
                if( flag == 0 )
                {
                    memset( &people,0,sizeof(people) );
                }
                send( conn_fd,(void *)&flag,sizeof(flag),0 );
            }
            else if( people.flag == 2 ) //注册
            {
                flag = check_setin( &people,head );
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

        peo *p = head->next;    //
        while( p->next )
        {
            printf( "\n*************\n\tp->fd = %d\n",p->fd );
            p=p->next;
        } 
        
        if( people.login == 1 )         //请求添加好友
        {
           // printf( "%s",people.buf );
            pthread_mutex_init(&mutex,NULL);
            tianjia(&people,head,conn_fd);
        }
    }
    pthread_exit(0);
}


void take_out(peo *head)				//从文件读取学生信息到链表 
{
	FILE *fp;
	fp=fopen("denglu","r");
	if(fp==NULL)
	{
		printf("takeout error");
		exit(0);
	}
	peo *p1,*p2,*p3;
	p2=p1=(peo *)malloc( sizeof(peo) );
	head->next = p1;
	while(fscanf(fp,"%s %s",p1->number,p1->passwd)!=EOF)
	{
		p1=(peo *)malloc( sizeof(peo) );
		p2->next = p1;
		p2=p1;
	}
    p1 = NULL;
    p2 = NULL;
    fclose(fp);
}

void save(peo *head)           //保存学生信息到文件
{
    FILE *fp;
	fp=fopen("denglu","w+");
    if(fp==NULL)
    {
        printf("save error");
        exit(0);
    }
    peo *p=head->next;
	while(p)
    {
        fprintf(fp,"%s %s\n",p->number,p->passwd);
        p=p->next;
    }
    fclose(fp);
}




int check_setin( user *people,peo *head )   //打开文件，注册账号密码写入链表
{
    peo *p = head->next;
    peo *p1=(peo *)malloc( sizeof(peo) );
    
    while( p->next )
    {
        if( (strcmp(p->number,people->number)) == 0 )
        {
            printf( "账号已被使用\n" );
            return 0; 
        }
        p = p->next;
    }
    
    strcpy( p1->number,people->number );
    strcpy( p1->passwd,people->passwd );

    p->next = p1;
    p1->next =NULL;
    return 1;
 }

int check_login( user *people,peo *head,int conn_fd )       //登录
{
    int flag = 0;
    peo *p = head->next;
    while( p->next )
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
    p->flag = 1;   //登陆成功即在线
    p->fd = conn_fd;  //保存套接字
    return 1;
}

void tianjia( user *people,peo *head,int conn_fd )      //添加好友
{

    pthread_mutex_lock(&mutex);
    int t = 0;
    peo *p = head->next;
    while( p->next )        //找到该账号
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
        memset( people->buf,0,sizeof(people->buf) );
        strcat( people->buf,people->number );
        strcat( people->buf," wants to be friend with u~" );
        printf( "----->%s\n",people->buf );//
       
        printf( "p->fd %d  conn_fd %d\n",p->fd,conn_fd );//

        if( send( p->fd,people,sizeof(user),0 ) < 0) //给想添加的账号发送请求
        {
            printf( "niang类 原来是这里错了\n" );
        }
        if( recv( p->fd,people,sizeof(user),0 ) < 0 )
        {
            printf( "没收到啊\n" );
        }
        
        if( strcmp(people->buf,"y") == 0 )
        {
            memset( people->buf,0,sizeof(people->buf) );
            strcpy(people->buf,"yes");
            send(conn_fd,people,sizeof(user),0);
        }
        else if( strcmp(people->buf,"n") == 0 )
        {
            memset( people->buf,0,sizeof(people->buf) );
            strcpy(people->buf,"no");
            send( conn_fd,people,sizeof(user),0 );
        }
        
    }
    pthread_mutex_unlock( &mutex );
    pthread_mutex_destroy( &mutex );
}
