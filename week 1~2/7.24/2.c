/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 09时44分54秒
 ************************************************************************/

#include<stdio.h> 
#include <stdlib.h>  
#include <math.h>  
#include <string.h>  
  
int gcd(int x,int y)  
{  
      if(y == 0)  
      return x;  
      else  
      return gcd(y,x%y);      
}  
    
int lcm(int x,int y)  
{  
    return x/gcd(x,y)*y;      
}  
      
int main()  
{  
    int n;  
    scanf("%d",&n);  
    while(n--)  
    {  
        int a,b,c,d,rx,ry;  
        scanf("%d/%d",&a,&b);  
        scanf("%d/%d",&c,&d);  
        /*int t=gcd(a,b);  
        a/=t,b/=t;  
        t= gcd(c, d);   
        c/=t,d/=t;   
        if(gcd( b,d) == 1)  
        {  
            printf( "%d\n",lcm(a,c));  
        }  
        else  
        {  */
            printf("%d/%d\n",lcm(a,c),gcd(b,d));  
        //}  
    }  
    return 0;  
}  
