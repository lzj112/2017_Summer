/*************************************************************************
	> File Name: 3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 15时41分21秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(void)
{
    int i,n,count;
    char b[1000];
    scanf("%d",&n);
    getchar(  );
    while(n--)
    {
            count=0;
            int len;
            fgets(b,1000,stdin);
            len=strlen(b);
            b[len]='\0';
            for(i=0;b[i] != '\0';i++)
            {
                if(b[i]<0||b[i]>127)
                count++; 
            }
            printf("%d\n",count/2);
    }

    return 0;
}
