/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 11时17分23秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int t,a,b,sum;
    scanf("%d",&t);
    getchar();
    while(t--)
    {
        sum=0;
        scanf("%d %d",&a,&b);
        if(a>=100)
        a=a%100;
        if(b>=100)
        b=b%100;
        sum=a+b;
        if(sum>=100)
        sum=sum%100;
        printf("%d\n",sum);
    }
    return 0;
}

