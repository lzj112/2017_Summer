/*************************************************************************
	> File Name: test5.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 10时28分25秒
 **********************************************************************/
 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<time.h>
 #include<unistd.h>
 //#include<linux.h>
 #include<sys/stat.h>
 #include<dirent.h>
 #include<grp.h>
 #include<pwd.h>
 #include<errno.h>
 int main()
 {
     char *path="~/git";
     int len1=0;
     DIR *dir;
     struct stat *ptr;
     int count=0;
     char filename[256][260];
     
     //获取该目录下最长文件名
     dir=opendir("path");
     if(dir==NULL)
     {
         exit(1);
     }
     while((ptr=reddir(dir))!=NULL)
     {
         if(len1<strlen(ptr->d_name))
         {
             len1=ptr->d_name;
         }
         count++;
     }
     closedir(dir);

     if(count>256)
     {
         perror(count);
         exit(1);
     }

     int i,j,len=strlen(path);
     //获取该目录下所有文件名
     dir=opendir(path);
     for(i=0;i<count;i++)
     {
         ptr=readdir(dir);
         if(ptr=NULL)
         {
             perror("for");
             exit(1);
         }
         strncpy(filename[i],path,len);
         filename[i][len]='\0';
         strcat(filename[i],ptr->d_name);:w

     }
 }

