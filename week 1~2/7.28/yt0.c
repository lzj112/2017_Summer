/*************************************************************************
	> File Name: yt0.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月28日 星期五 17时34分24秒
 ************************************************************************/

#include<stdio.h>
  
  
  char grid[101][101];    //油田矩阵  
  int n, m;       //行、列  
  int dir[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}  };    //一个网格的8个方向  
    
      
      void dfs(int x, int y)                  //从（x,y）进行深度优先遍历  
      {  
          int xx, yy;  
          grid[x][y] = '*';       //将grid中访问过的方块设置成‘*’，防止重复访问  
          for(int i = 0; i < 8; i++)  
          {  
                  xx = x + dir[i][0];  
                  yy = y + dir[i][1];  
                  if(xx<0 || xx>=n || yy<0 || yy>=m) continue;    //越界终止本次循环  
                  if(grid[xx][yy] == '@') dfs(xx, yy);            //核心算法语句。如果方格还是‘@’，则继续搜索  
              }  
      }  
        
        int main()  
        {  
            int i, j;   //循环变量  
            int cnt;    //油田数量计数  
            while(scanf("%d%d", &n, &m)&&(n||m))  
            {  
                    cnt = 0;  
                    for(i = 0; i < n; i++) scanf("%s", grid[i]);  
                    for(i = 0; i < n; i++)  
                        for(j = 0; j < m; j++)  
                            if(grid[i][j] == '@') { dfs(i, j); cnt++;  } //在（i,j）遍历，并且遍历了一个“油田”，计数器加1  
                    printf("%d\n", cnt);  
                }  
            return 0;  
        }  
