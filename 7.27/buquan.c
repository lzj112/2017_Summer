#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH              100
#define KEY_BACKSPACE2          ((char)127) 
#define KEY_TAB              ((char)9)
#define KEY_ENTRY               ((char)10)

char path[MAX_LENGTH + 1];
int current_i = 0;
struct termios i,n;

int find_index(char *base,char c){
    
    int i = 0;
    char *t = base;        
    while(*t) if (*t++ == c) i = t - base;
    return i - 1;
}

void auto_completion(void){
    
    DIR * dir;
    struct dirent *ent,*t_ent;
    char *t;
    char t2[MAX_LENGTH];
    char *base = path; 
    int l = 0;
    int i = 0;
    int name_length;
    int o;

start:
    i = find_index(base,'/');
    t = &base[i];
    while(*t) t++; // 
    if (path[0] != '/') i = -1; 

    switch(i){

        case -1:

            getcwd(t2,MAX_LENGTH);
            o = strlen(t2);

            if (o + current_i > MAX_LENGTH) return;
            
            for (l = 0; l < o ; l++){
            
                path[o + l + 1] = path[l];
                path[l] = t2[l];
            }
            path[l] = '/';

            for (l = 0; l < current_i; l++)
                putchar('\b');
            
            current_i += o + 1;
            printf("%s",path);
            l = o = 0;
            goto start;

        break;
        case 0:
            if ((dir = opendir("/")) == NULL) return;
            base++;        
        break;
        default:
            base[i] = '\0';        
            if ((dir = opendir(base)) == NULL) return;
            base[i] = '/';
            base = &base[i+1];
        break;
    }

    name_length = t - base;

    while((ent = readdir(dir)) && (l < 2)){

        if ((ent->d_type == 4) &&
            (*ent->d_name != '.') &&
            (strncmp(base,ent->d_name,name_length) == 0)){
            
            t_ent = ent;
            l++;
        }
    }

    if (l == 1){        

        t = t_ent->d_name;
        for (i = 0; i < name_length ; i++){

            current_i--;
            if (path[current_i] == '/') {
                current_i++;
                break;
            };
            putchar('\b');
        }

        for (i = 0; current_i < MAX_LENGTH && *t;i++){
            
            base[i] = *t++;
            current_i++;    
            putchar(base[i]);
        }
        base[i] = '/';
        current_i++;    
        putchar(base[i]);
    }

    closedir(dir);
}

void get_line(void){
    
    int i = 0;
    char c;

    memset(path,0,MAX_LENGTH);
    current_i = 0;

    while (1){

        c = getchar();

        if (c == KEY_ENTRY) return ; //回车键 
        if (current_i >= MAX_LENGTH) continue; //超出最大限制数 
        if (c == KEY_TAB) {    //TAB键，那么自动补全 

            if (!path[0]) continue;
            auto_completion(); 
            continue;
        }
        if (c == KEY_BACKSPACE2){

            if (current_i == 0) continue;
            path[current_i--] = '\0';
            printf("\b \b");
            continue;        
        }    
        path[current_i++] = c;
        putchar(c);
    }
}

int main(void){

    char c;
    DIR *dir;

    tcgetattr(fileno(stdin),&i);
    n = i;
    n.c_lflag &= ~ECHO;
    n.c_lflag &= ~ICANON;

    if (tcsetattr(fileno(stdin),TCSAFLUSH,&n) != 0){

        printf("tcsetattr");
    }else {

        printf(": ");
        get_line();
        printf("\nYou: %s\n",path);
    }

    tcsetattr(fileno(stdin),TCSANOW,&i);
    return 0;
}
