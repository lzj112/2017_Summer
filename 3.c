/*************************************************************************
	> File Name: 3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 10时46分20秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int n,m,sum,a[100],avg,flag;
    while(scanf("%d %d",&n,&m)!=EOF)
    { 
        int i,j;
        for(i=0,j=1;i<n;i++,j++)
        {
            a[i]=2*j;
        }
        int t=n%m;
        for(i=0;i<n-t;i=i+m)
        {
            sum = 0;
            flag = 0;
            for(j=i;flag<m;flag++,j++)
            {
                sum+=a[j];
            }
            avg=sum/m;
            if(i==0)
            printf("%d",avg);
            else
            printf(" %d",avg);
        }
        sum=0;
        if(t!=0)
        {
            int tmp=n-i;
        for(;i<n;i++)
        sum+=a[i];
        avg=sum/tmp;
        printf(" %d",avg);
        }
        printf("\n");
    }
        return 0;
}
