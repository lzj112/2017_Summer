/*************************************************************************
	> File Name: select.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月03日 星期四 16时38分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>

void display_time( const char *string )
{
    int seconds;

    seconds = time( (time_t *)NULL ); //获得当前时间
    printf( "%s %d\n",string,seconds );
}

int main( void )
{
    fd_set readfds;
    struct timeval timeout;
    int ret;

    //监听文件描述符0是否有数据输入，文件描述符0表示标准输入，即键盘输入
    FD_ZERO( &readfds );            //清空描述符集合
    FD_SET( 0,&readfds );           //将0加入集合
    
  /*  //设置阻塞时间为10s
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;*/

    while(1)
    {
        //设置阻塞时间为10s
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        
        
        display_time( "before select!" );
        ret = select( 1,&readfds,NULL,NULL,&timeout );
        display_time( "after select!" );

        switch( ret )
        {
            case 0:
            {
                printf( "No data in ten seconds.\n" );
                exit(0);
                break;
            }
            case -1:
            {
                perror("select error");
                exit(1);
                break;
            }
            default:
            {
                getchar();      //将数据读入，否则标准输入上就一直为读就绪
                printf( "Data is available now.\n" );
            }
        }
    }
    return 0;
}
