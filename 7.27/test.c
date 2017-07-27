/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月26日 星期三 16时07分12秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static char *line_read = (char *) NULL;

char *rl_gets() {
    if (line_read) {
          free(line_read);
          line_read = (char *) NULL;
         
    }
     line_read = readline("Please Enter:");

     if (line_read && *line_read)
      add_history(line_read);
     return (line_read);

}

int main() {
     char *mline;
    scanf("%s",mline);
     mline = rl_gets();
     printf("%s/n", mline);

}
