#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <readline/readline.h>
#include <readline/history.h>
int main()
{
    char *buf=NULL;
    int len;
    //buf=(char *)malloc(sizeof(char)*256);
    while(1)
    {

    buf=(char *)malloc(sizeof(char)*256);
    buf=memset(buf,0,256);   
    buf=readline("");
    len=strlen(buf);
    printf("len = %d   buf = >%s<\n",len,buf);
    add_history(buf);
    }
    return 0;
}

 

