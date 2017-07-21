/*************************************************************************
	> File Name: 3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月21日 星期五 10时27分19秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int a(int m);
    int n,sum,m;
    scanf("%d",&n);
    while(n--)
    {
        sum=3;
        scanf("%d",&m);
        while(m--)
        sum=a(sum);
        printf("%d\n",sum);
    }
    return 0;
}
int a(int m)
{
    int b;
    b=(m-1)*2;
    return b;
}
