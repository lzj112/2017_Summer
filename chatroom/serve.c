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
    int flag;           //标记是否在线
    char number[10];
    char passwd[20];
    struct c *next;
}peo;

void take_out( peo *head );
int check_login( user *people,peo *head );
int check_setin( user *people,peo *head );
void save( peo *head );

int main()
{
    pid_t pid;
    pthread_t tid;
    user people;
    struct sockaddr_in cin,sin;
    socklen_t sin_len;
    int conn_fd,sock_fd;
    
    memset( &cin,0,sizeof(cin) );       //置0
    memset( &people,0,sizeof(people) );

    cin.sin_family = AF_INET;
    cin.sin_port = htons(PORT);
    cin.sin_addr.s_addr = htonl(INADDR_ANY);

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
            exit(0);
        }
        
        printf( "有客户端连接\n" );

        //开辟子进程处理
        if( (pid = fork()) == 0 )
        {
            printf( "这里是一个子进程\n" ); //
            int ret;
            int flag;

            //接收数据
            if( (ret = recv(conn_fd,&people,sizeof(user),0)) < 0 )
            {

                printf( "recv error\n" );
                exit(0);
            }
            peo *head = (peo *)malloc( sizeof(peo) );
            head->next = NULL;

            take_out(head);
            if( people.flag == 1 )          //登录
            {
                flag = check_login( &people,head );
                send( conn_fd,(void *)&flag,sizeof(flag),0 );
                
            }
            else if( people.flag == 2 )     //注册
            {
                flag = check_setin( &people,head );
                printf( "%d",flag ); //
                if( flag == 1 )
                    save(head);
                send( conn_fd,(void *)&flag,sizeof(flag),0 );
            }

            exit(0);
        }
    }
}

void take_out( peo *head )           //从文件读取信息到链表 
{
    FILE *fp;
    fp=fopen("denglu","r");
    if(fp==NULL)
    {
        printf("read error");
        exit(0);
    }
    peo *p1,*p2;
    p1=(peo *)malloc(sizeof(peo));
    p2=p1;
    head->next = p1;
    rewind(fp);     //使文件指针指向开头
    while(fscanf(fp,"%s %s",p1->number ,p1->passwd)!=EOF)
    {
        p1 = (peo *)malloc( sizeof(peo) );
        p2->next = p1;
        p2 = p1;
    }
    p1 = NULL;
    p2 = NULL;
    fclose(fp);

}


void save(peo *head)           //保存信息到文件
{
        FILE *fp;
        fp=fopen("denglu","w");
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
            //people->login = 1;
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

int check_login( user *people,peo *head )
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
    printf( "成功登录\n" );
    //people->login = 2;
    return 1;
}
