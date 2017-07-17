/*************************************************************************
	> File Name: 4.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月17日 星期一 15时43分56秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int n,a,sum;
    while(1)
    {
        scanf("%d",&n);
        if(n==0)
        break;
        sum=0;
        while(n)
        {
            n--;
            scanf("%d",&a);
            sum+=a;
        }
        printf("%d\n",sum);
    }
    return 0;
}
