/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 14时21分50秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    unsigned long long a,b,sum;
    int i=0;
    while(scanf( "%llu %llu",&a,&b )!= EOF)
    {
        i++;
        printf( "Case %d:\n",i );
        sum=a+b;
        printf( "%llu + %llu = %llu\n",a,b,sum );
    }
    return 0;
}
