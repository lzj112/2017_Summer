/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 15时06分42秒
 ************************************************************************/

#include<stdio.h>
int min(int *a,int n)
{
    int max(int x,int y);
    int x,y,num=a[0],i,m;  
    for(i=0;(i+1)<n;i++)
    {  
     x=num;    
     y=a[i+1];     
     m=max(x,y);      
     num = x/m * y/m * m;  
     }  
    return num;    
    }

int max(int a,int b)
{
    int temp;  
    if(a < b)
    {  
        temp = a;  
        a = b;  
        b = temp;  
    }    
    if(a%b == 0)
    {  
        return b;    
    }else
    {    
        return max(b,a%b);    
    }    
}



int main()
{
    int a[1000],n;
    while(scanf("%d",&n)!=EOF)
    {
        int i,num;
        for(i=0;i<n;i++)
        scanf("%d",&a[i]);
        num=min(a,n);
        printf("%d\n",num);
    }
    return 0;
}
