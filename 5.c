/*************************************************************************
	> File Name: 5.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月17日 星期一 16时00分06秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int flag,n,a,sum;
    scanf("%d",&flag);
    while(flag)
    {
        flag--;

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
            if(flag!=0)
            printf("%d\n\n",sum);
            else 
            printf("%d",sum);
        
    }

   return 0;
}
