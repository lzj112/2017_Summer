/*************************************************************************
	> File Name: my_recv.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月04日 星期五 11时00分12秒
 ************************************************************************/

//#define MY_RECV_C

#include<stdio.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<errno.h>
#include"my_recv.h"


//自定义的错误处理函数
void my_err( const char *err_string,int line )
{
    fprintf( stderr,"line:%d",line );
    perror(err_string);
    exit(1);
}

/*函数名  my_recv
 * 描述：从套接字上读取一次数据(以'\n'为结束标志)
 * 参数;conn_fd——从该连接套接字上接收数据
 *      data_buf——读取到的数据保存在此缓冲中
 *      len——data_buf所指的空间长度
 *返回值：出错返回-1，服务器端已关闭连接则返回0，成功返回读取的字节数
 */
 int my_recv( int conn_fd,char *data_buf,int len )
 {
     static char recv_buf[BUFSIZE];  //自定义缓冲区，BUFSIZE定义在my_recv.h中
     static char *pread;             //指向下一次读取数据的位置
     static int len_remain = 0;      //自定义缓冲区剩余字节数
     int i;

     //如果自定义缓冲区中没有数据，则从套接字读取数据
     if( len_remain <= 0 )
     {
         if( len_remain = recv( conn_fd,recv_buf,sizeof(recv_buf),0 ) < 0 )
         {
             me_err( "recv",__LINE__ );
         }
         else if( len_remain == 0 )         //目的计算机端的socket连接关闭
         {
             return 0;
         }
         pread = recv_buf;  //重新初始化pread指针
     }

     //冲自定义缓冲区中读取一次数据
     for( i=0;*pread != '\n';i++ )'
     {
        if( i>len )
         {
             return -1;
         }
         data_buf[i] = *pread++;
         len_remain--;
     }

     //去除结束标志
     len_remain--;
     pread++;

     return i;      //读取成功
 }

