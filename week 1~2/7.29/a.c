/*************************************************************************
	> File Name: a.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月29日 星期六 08时30分01秒
 ************************************************************************/

#include<stdio.h>

int n;

int main()
{
    int i;
    while( scanf( "%d",&n ) != EOF )
    {
        int str[n],ptr[n];
        for( i=0; i<n; i++ )
            scanf( "%d",&str[i] );
        for( i=0;i<n;i++ )
        {
            a(str[i]);
        }

    }
    return 0;
}

void a( char *str )
{
    int i,j;
    ptr;
    str+=1;
    for( i=1; i<n; i++ )
    {
        if( check(str[i-1],str[i]) ) 
        {
            
        }
    }
}

int pn( int m,int n )
{
     int sum=m+n;
    for( i=1; i<=sum; i++ )
    {
        if( n%i )
        return 0;
    }
    return 1;
}
