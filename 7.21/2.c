/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月21日 星期五 10时11分18秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int i,flag,n,len,j;
    char word[100];
    scanf("%d",&n);
    while(n--)
    {
        flag=1;
        scanf("%s",word);
        len=strlen(word);
        for(i=0,j=len-1;i<len/2;i++,j--)
        {
            if(word[i]!=word[j])
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
        printf("yes\n");
        else
        printf("no\n");

    }
}
