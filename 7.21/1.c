/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月21日 星期五 09时37分28秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    double money[13],avg,sum=0.00;
    money[0]=0.00;
    for(int i = 1;i < 13;i++)
        scanf("%lf",&money[i]);
    for(int i=1;i<=12;i++)
    {
        sum+=money[i];
    }
    avg=sum/12;
    printf("$%.2lf\n",avg);
}
