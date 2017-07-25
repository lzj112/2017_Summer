/*************************************************************************
	> File Name: a.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 09时20分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#define MAXFILE 65535
int main()
{
    pid_t pc;
    int i,fd,len;
    char *buf="this is a dameon\n";
    len = strlen( buf );
    pc =fork();//创建一个子进程
    if( pc<0 )
    {
        printf("error!\n");
        exit(1);
    }else if( pc >0 ){
        exit(0); //结束父进程
    }
    setsid();//使子进程独立 1.拜托原会话控制，2.摆脱原进程组控制 3.拜托控制终端的控制
    chdir("/"); //改变当前工作目录，这也是为了摆脱父进程的影响
    umask(0);//重设文件掩码
    for( i=0;i<MAXFILE;i++ ) //关闭文件描述符（常说的输入 输出 报错三个文件),因为守护进程要失去了对所属控制终端的联系，这三个文件都要关闭
    close(i);
    while(1)
    {
        if((fd=open("/tmp/dameon.txt",O_CREAT | O_WRONLY | O_APPEND,0600))<0){
            printf("open file err\n");
            exit(0);
        }
        write( fd,buf,len+1 );
        close(fd);
        sleep(100);
    }
}
