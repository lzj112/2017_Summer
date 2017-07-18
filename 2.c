/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 10时14分59秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int n,i,j,t,sum;
    float avg,b,c;
    int a[100];
    while(scanf("%d",&n)!=EOF)
    {
        sum=0;
        for(i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
        }
        for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
        {
            if(a[i]<a[j])
            {
                t=a[i];
                a[i]=a[j];
                a[j]=t;
            }
        }
        for(i=1;i<n-1;i++)
        sum+=a[i];
        n=n-2;
        b=sum*1.0,c=n*1.0;
        avg=b/c;
        printf("%.2f\n",avg);
    }
    return 0;
}
