/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月17日 星期一 14时24分01秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    char name[100];
    int len,i,t,flag,count;
    while(scanf("%s",name)!=EOF)
    {

        t=100,flag=1,count=0;
        len=strlen(name);
        if(name[0]=='@' || name[0]=='.' || name[len-1]=='@' || name[len-1]=='.')
        {
            printf("NO\n");
            continue;
        }
        for(i=0;i<len;i++)
        {
            if(name[i]=='@')
            {
                count++;
                flag=0;
                t=i;
            }
            if(name[t-1]=='.'||name[t+1]=='.')
            {
                flag=2;
                printf("NO\n");
                break;
            }
            if(i>t+1&&name[i]=='.')
            {
                flag=1;
            }
        }
        if(flag==2)
        continue;
        if(count==1&&flag==1)
        printf("YES\n");
        else 
        printf("NO\n");
    }
    return 0;

}
