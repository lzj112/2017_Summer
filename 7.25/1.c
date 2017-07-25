/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 11时31分17秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int gcd( int a,int b );
    int a,b,c,t;
    int n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %d",&a,&b);
        c=b;
        while(1)
        {
            t=gcd( a,c );
            if( t==b && c!= b )
            break;
            else
            c+=b;
        }
        printf( "%d\n",c );

    }
}
int gcd( int a,int b )
{
    if( b == 0 )
    return a;
    else 
    return gcd( b,a%b );
}
