/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 14时35分10秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int n;
    int cows(int n);
    int sum=0;
    while(scanf("%d",&n)!=EOF&&n!=0)
    {
        sum=cows(n);
        printf("%d\n",sum);
    }
    return 0;
}
int cows(int n)
{
    if(n<5)
    return n;
    else
    return cows(n-1)+cows(n-3);
}
