/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 08时10分57秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int m,n,i;
    while(scanf("%d %d",&m,&n)!=EOF)
    {
        int a,b,c,count=0;
        for(i=m;i<n;i++)
        {
            a=i/100;
            b=i/10%10;
            c=i%10;
            if(i==a*a*a+b*b*b+c*c*c)
            {
                count++;
               /* if(count==1)
                {
                    printf("%d",i);
                }
                else
                printf(" %d",i);*/
                printf("%d ",i);
            }
        }
        if(count==0)
        printf("no");
        printf("\n");
    }
    return 0;
}
