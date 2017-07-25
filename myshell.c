/*************************************************************************
	> File Name: myshell.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 17时32分59秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>

#define normal              0   //一般的命令
#define out_redirect        1   //输出重定向
#define in_redirect         2   //输入重定向
#define have_pipe           3   //命令中有管道

void get_input(char *);         //得到输入的命令
void explain_input( char *buf,int argcount,char **arglist );      //对输入的命令进行解析
void do_cmd( int argcount,char **arglist ); //执行命令
int find_command( char * );     //查找命令中的可执行程序

int main( int argc,char **argv )
{
    
}

void get_input( char *buf )      //获取用户输入
{
    int len=0;
    int ch;

    ch = getchar();
    while( len<256 && ch!= '\n' )
    {
        buf[len++]=ch;
        ch=getchar();
    }
    if( len == 256 )           //输出的命令过长就退出程序
    {
        printf( "Command is too long!\n" );
        exit(1);
    }
    buf[len]= '\n';
    buf[++len]= '\0';
}

void explain_input( char *buf, int argcount, char **arglist )  //解析buf中的命令 遇到\n结束
{
    char *p = buf;
    char *q = buf;
    int number = 0;
    while(1)
    {
        if( p[0] == '\n' )
            break;
        if( p[0] == ' ' )
            p++;
        else
        {
            q=p;
            number=0;
            while( (q[number] != ' ') && (q[number] != '\n') )
            {
                number++;
                q++;
            }
            strncpy( arglist[argcount],p,number+1 );
            arglist[argcount][number] = '\0';
            argcount += 1;
            p=q;
            
        }
    }
}

void do_cmd( int argcount,char **arglist )
{
    int flag=0;
    int how=normal;                         //用于指示命令中是否含有 >  <  |
    int background = 0;                     //标识命令中是否有后台运行标识符 &
    int status, i, fd;
    char *arg[argcount+1], *argnext[argcount+1], *file;
    pid_t pid; 

    //将命令取出
    for( i=0;i<argcount;i++ )
    {
        arg[i] = ( char * )arglist[i];
    }
    arg[argcount] = NULL;
    
    //查看命令行是否有后台运行符
    for( i=0;i<argcount;i++ )
    {
        if( strcmp( arg[i],"&",1 ) == 0 )
        {
            if( i == argcount )             //&位置在命令最后
            {
                background=1;
                arg[argcount-1]=NULL;
                break;
            }
            else
            {
                printf( "Command error!\n" );
                return ;
            }
        }
    }

    for( i=0; arg[i] != NULL; i++ )
    {
        if( strcmp( arg[i],">" ) == 0 )
        {
            flag++;
            how = out_redirect;
            if( arg[i+1] == NULL ) //如果 > 是最后一个
            flag++;
        }
        if( strcmp( arg[i],"<" ) == 0 )
        {
            flag++;
            how = in_redirect;
            if( i == 0 )
            {
                flag++;
            }
        }
        if( strcmp( arg[i],"|" ) == 0 )
        {
            flag++;
            how=have_pipe;
            if( arg[i+1] == NULL )
            {
                flag++;
            }
            if( i == 0 )
            {
                flag++;
            }
        }
    }

    //flag>1 说明命令中含有多个>, <, | 符号，或者命令格式不对，对此我的shell表示力不从心
    if( flag>1 )
    {
        printf("Command error!\n");
        return ;
    }
    if( how == out_redirect )           //命令只含有一个输出重定向符号
    {
        for( i=0; arg[i] != NULL; i++ )
        {
            if( strcmp( arg[i],">" )==0 )
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }
    if( how == in_redirect )            //命令只含有一个输入重定向符号
    {
        for( i=0; arg[i] != NULL; i++ )
        {
            file = arg[i+1];
            arg[i] = NULL;
        }
    }
    if( how == have_pipe )              //命令中只有一个管道符号
    {
        //把管道后面的部分存入argnext，管道后面那部分是一个可执行的shell命令
        for( i=0; arg[i] != NULL; i++ )
        {
            if( strcmp( arg[i],"|" )== 0 )
            {
                arg[i] = NULL;
                int j;
                for( j=i+1; arg[i] != NULL; j++ )
                {
                    argnext[j-i-1] = arg[j];
                }
                argnext[j-i-1] = arg[j];   //存一个NULL
                break;
            }
        }
    }
    if( (pid = fork()) <0 )
    {
        printf( "process creation failed!\n" );
        return ;
    }
    switch( how )
    {
        case 0:
        {
            //pid=0说明是子进程，在子进程执行输入的命令，命令中不含>, <, |
            if( pid == 0 )
            {
                if( ! )
            }
        }
    }

}
