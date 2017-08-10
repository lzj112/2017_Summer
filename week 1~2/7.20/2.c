/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 08时52分22秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int len,n,i,j,k,bef,aft,count,flag;
    scanf("%d",&n);
    getchar();
    while(n--)
    {
        char word[1000],tmp[1000];
        bef=0,aft=0,j=0,k=0,count=0;
        fgets(word,1000,stdin);
        len=strlen(word);
        for(i=0;i<len;i++)
        {
            if(word[i]==' ')
            {
                count++;
                if(count==1)
                {
                    int l=0;    //
                    aft=i;
                    for(j=0,k=i-1;j<i;j++)
                    tmp[j]=word[k--];
                    tmp[aft]=' ';
                    for(;l<i;l++)
                    printf(" -->%c",tmp[l]);         //
                }
                else
                {
                    int l=aft+1;
                    bef=i;
                   // printf("abci:%d bef:%d aft:%d   ",i,bef,aft);      //
                    for(j=aft+1,k=bef-1;j<(bef-aft);j++)
                    tmp[j]=word[k--];
                    tmp[bef]=' ';
                    for(;l<bef;l++)
                    printf(" -->%c",tmp[l]);         //
                }
            } 
        }
        if(count==1)
        {
            int l=aft+1;        //
           // printf("bcdi:%d  aft:%d  bef:%d  ",i,aft,bef);             //
            for(j=aft+1,k=i-1;j<=i;j++)
            tmp[j]=word[k--];
            for(;l<i;l++)
            printf("-->%c ",tmp[l]);        //

        }
        else
       {
           int l=bef+1;     //
         //  printf("asdi:%d aft:%d bef:%d",i,aft,bef);          //
            for(j=bef+1,k=i-1;flag<(i-bef);j++)
            tmp[j]=word[k--];
           for(;l<i;l++)
           printf("--> %c",tmp[l]);

       }
        tmp[j]='\0';
        printf("%s\n",tmp);
    }
    return 0;
}
