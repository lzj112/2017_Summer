/*************************************************************************
	> File Name: test2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月26日 星期三 22时00分56秒
 ************************************************************************/

#include<stdio.h>
#include<readline/readline.h>
#include<readline/history.h>
int main()
{
    char ch,*buf;
    int len=0;;
    ch=getchar();
    while( 1 )
    {

        if( ch == '\033'|| ch == '['||ch=='A' )

        //add_history();
        ch=getchar();
    }
    return 0;
}
