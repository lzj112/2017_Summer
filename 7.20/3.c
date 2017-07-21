/*************************************************************************
	> File Name: 3.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 10时15分24秒
 ************************************************************************/

#include<stdio.h> 
#include<string.h>  
int main()  
{  
    int len,i,j,k,m,l,t;  
    char str[1005];  
    scanf("%d",&t);  
    getchar();  
    while(t--)  
    {  
            fgets(str,1005,stdin);  
            l=strlen(str);  
            str[l-1]='\0';
            m=0,k=0;  
            for(i=0;i<l;i++)  
            {  
                if(str[i]==' ')  
                {  
                    m=i;   
                    for(j=m-1;j>=k;j--)  
                    {  
                        printf("%c",str[j]);  
                    }  
                        printf("%c",str[i]);  
                    k=m+1;  
                }  
            }  
            for(j=l-2;j>=k;j--)
            {  
                printf("%c",str[j]);  
            }  
            printf("\n");  
        }  
    return 0;  
}  
