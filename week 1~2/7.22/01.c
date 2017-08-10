/*************************************************************************
	> File Name: 01.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 10时52分06秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int n;
    char a[20];
    scanf("%d",&n);
    while(n--)
    {
        int i=0,len;
        scanf("%s",a);
        len=strlen(a);
        printf("%c",'6');
        for(i=6;i<len;i++)
        printf("%c",a[i]);
        printf("\n");
    }
    return 0;
}
