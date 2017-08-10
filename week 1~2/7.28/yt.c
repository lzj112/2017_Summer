/*************************************************************************
	> File Name: yt.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月28日 星期五 14时46分30秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
char str[100][200];
char dir[8][2] = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
int m,n;
int main()
{
    void dfs( int i,int j ); 
    int i,j,count;
    while( scanf( "%d %d",&m,&n ) != EOF )
    {
        if( m == 0 )
            break;
        for( i=0; i<m; i++ )
        {
            scanf( "%s",str[i] );
        }

        count = 0;
        for(i=0; i<m; i++)
        {
            for(j=0; j<n; j++)
            {
                if(str[i][j] == '@')
                {
                    count++;
                    dfs( i,j );
                }
            }
        }
        printf( "%d\n",count );
    }
    return 0;
}

void dfs( int i,int j )
{
    str[i][j] = '*';
    int xx=0 ,yy=0;
    for( int a=0; a<8; a++ )
    {
        xx = i+dir[a][0];
        yy = j+dir[a][1];

        if( str[xx][yy] == '@' &&xx>=0&&xx<m&&yy<n&&yy>=0)
        {
            dfs( xx,yy );
        }
    }
}
