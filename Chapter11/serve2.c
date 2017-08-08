#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include<unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include<arpa/inet.h>
void showClientInf(struct sockaddr_in client_addr) {
  printf("/nThe IP of client is:%s",inet_ntoa(client_addr.sin_addr));
  printf("/nThe Port of client is:%d/n",ntohs(client_addr.sin_port));
}
int main() {
 int sockfd,new_fd;
 struct sockaddr_in my_addr;
 struct sockaddr_in their_addr;
 int sin_size;
 char buff[100];
 int numbytes;
 //建立TCP套接口
 if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1) {
  perror("socket");
  exit(1);
 }
 //初始化结构体，并绑定2323端口
 my_addr.sin_family = AF_INET;
 my_addr.sin_port = htons(2323);
 my_addr.sin_addr.s_addr = INADDR_ANY;
 bzero(&(my_addr.sin_zero),8);
 //绑定套接口
 if(bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==-1)
 {
  perror("bind");
  exit(1);
 }
 //创建监听套接口
 if(listen(sockfd,10)==-1) {
  perror("listen");
  exit(1);
 }
 printf("server is run.../n");
 //等待连接
 while(1) {
  sin_size = sizeof(struct sockaddr_in);
  //如果建立连接，将产生一个全新的套接字，their_fd存储发送方的信息
  //一个套接字与客户端保持控制连接，新套接字与客户端传递、接受信息
  if((new_fd = accept(sockfd,(struct sockaddr *)
  &their_addr,&sin_size))==-1)
  {
   perror("accept");
   exit(1);
  }
  //显示客户端信息
  showClientInf(their_addr);
  //生成一个子进程来完成和客户端的会话，父进程继续监听
  if(!fork()) {
  //读取客户端发来的信息
  //只能用sizeof取buff的大小，因为buff还没初始化，用strlen很容易碰到'/0'
   if((numbytes = recv(new_fd,buff,sizeof(buff),0))==-1)
   {
    perror("recv");
    exit(1);
   }
   buff[numbytes]='\0';
   printf("recieved %d bytes./n",numbytes);
   printf("the message is:%s/n",buff);
   //将从客户端接收到的信息再发回客户端
   if(send(new_fd,buff,strlen(buff),0)==-1)
    perror("send");
   close(new_fd);
   exit(0);
  }
  close(new_fd);
 }
 close(sockfd);
}
