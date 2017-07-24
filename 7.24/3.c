/*************************************************************************
	> File Name: 3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 22时28分25秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    char str[100000];
    char ptr[]="Bulbbasaur";
    int flag,count,len,i,j,a,b,u,l,s,r,B;
    while( scanf("%s",str) !=EOF )
    {
        a=0,b=0,u=0,r=0,l=0,B=0,s=0;
        flag = 1,count=0;
        len = strlen( str );
        if( len<10 ){
            printf("0\n");
            flag=0;
        }
        if( flag )
        {
            for( i=0; i<len; i++ )
            {
                if( str[i] == 'B'){
                    B++;
                }else if( str[i] == 'u'){ 
                    u++;
                }else if( str[i] == 'l' ){
                    l++;
                }else if( str[i] == 'b'){
                    b++;
                }else if( str[i] == 'a' ){
                    a++;
                }else if( str[i] == 'r' ){
                    r++;
                }else if( str[i] == 's' ){
                    s++;
                }
            }
        if( B==0 || u==0 || l==0 || b==0 || a==0 || r==0 )
            printf("0\n");
        while( B != 0 && l != 0 && s != 0 && r != 0 && a!=0 &&b!=0)
            {
                B-=1;
                b-=2;
                u-=2;
                l-=1;
                a-=2;
                s-=1;
                r-=1;
                count++;

            }
            printf("%d\n",count);
        
        }
    }
    return 0;
}
