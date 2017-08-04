/*************************************************************************
	> File Name: test_address.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月03日 星期四 14时24分22秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
 int main()
 {
     char buffer[32];
     int ret = 0;
     int host = 0;
     int network = 0;
     unsigned int address = 0;
     struct in_addr in;

     in.s_addr = 0;

     //输入一个以"."分隔的字符串形式的IP地址
     printf( "please input your ip address:" );
     fgets( buffer,31,stdin );
     buffer[31] = '\0';

     //示例使用inet_aton函数 
     if( !inet_aton( buffer,&in ))
         printf( "inet_aton:\tinvaild address\n" );
     else
        printf( "inet_aton(将参数所指的字符串形式的IP地址转换为二进制的网络字节顺寻的IP地址):\t0x%x\n\n",in.s_addr );
     
     //示例使用inet_addr函数
     if( (address = inet_addr(buffer)) == INADDR_NONE )
        printf( "inet_addr:\t invaild address\n" );
     else
        printf( "inet_addr(将参数所指的字符串形式的字符串形式的网络地址转换成网络字节顺序形式的二进制IP地址):\t0x%u\n\n",address );

     //示例使用inet_network函数
     if( (address = inet_network( buffer )) == -1 )
        printf( "inet_network:\tinvalid address\n" );
     else 
        printf( "inet_network(将参数所指的字符串形式的网络地址转换成主机字节顺序形式的二进制IP地址):\t0x%u\n\n",address );

     //示例使用inet_ntoa函数
     if( inet_ntoa(in) == NULL )
        printf( "inet_ntoa:\t invalid address\n" );
     else
        printf( "inet_ntoa(将网络字节顺序形式的二进制IP地址转换成以\".\"分隔的字符串形式的):\t%s\n\n",inet_ntoa(in) );

     //示例使用inet_lnaof函数与inet_netof函数
     host = inet_lnaof(in);
     network = inet_netof(in);
     printf( "inet_lnaof(从参数中提取主机地址):\t0x%x\n\n",host );
     printf( "inet_netof(从参数中提取网络地址):\t0x%x\n\n",network );

     //inet_makeaddr函数
     in = inet_makeaddr( network,host );
     printf( "inet_makeaddr(将两个地址组合成一个网络地址):\t0x%x\n",in.s_addr );

     return 0;
 }
