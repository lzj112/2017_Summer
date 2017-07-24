/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 08时10分30秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int len,i,j,k,flag,count;
    char str[100000];
    char ptr[] = "Bulbbasaur";
    while(scanf( "%[Bulbbasaur ]", str) != EOF )
    {
      /*  k = 0, flag = 1, count =0;
        len = strlen( str );
        printf("asfasf     %d\n",len);
        if( len < 10 )
        {
            printf( "0\n");
            flag =0 ;
        }
         while( flag )
        {
            for( i=0,j=0;i<len;i++ )
            {
                if( str[i] == ptr[j])
                {
                    j++;
                    str[i] = '0';
                    k++;
                }
            }
            if( k >= 10 )
            {
                count += k /10;
                k=0;
            }
                flag = 0;
                for( i=0; i<len; i++)
                {
                    if( str[i] != '0' )
                    {
                        flag = 1;
                        break;
                    }
                }
            
        }
        printf( "%d\n", count);*/
        printf("%s\n",str);
    }
    return 0;
}
