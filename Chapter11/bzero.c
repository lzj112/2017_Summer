#include <stdio.h>    
#include <string.h>  

int main( void )    
{     
    struct    
    {     
        int a;    
        char *s;    
        float f;    
    } tt;    
    tt.a = 10;
    tt.s = "abcd";
    tt.f = 1.2;
    char s[20];  
    bzero( &tt, sizeof( tt ) );     
    printf( "%d\n%s\n%f\n",tt.a,tt.s,tt.f );  
    getchar();    
    return 0;    
}
