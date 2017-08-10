/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 10时30分27秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    long int a;
    int n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%ld",&a);
        printf("6");
        printf("%ld",a%100000);
        printf("\n");
    }
    return 0;
}
