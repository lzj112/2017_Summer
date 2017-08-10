/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月26日 星期三 17时43分36秒
 ************************************************************************/

#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h>  
#include <sys/wait.h>  
#include <sys/types.h>  
  
  #define true 1  
    
    void * One(void * no)   
    {  
        while (true)  
        {  
            printf("NUAACS1\n");  
            sleep(1);  
            }  
    }  
      
      void * Two(void * no)   
        
        {  
            while (true)  
            {  
                printf("NUAACS2\n");  
                sleep(1);  
                }  
        }  
          
          void stop(int signo)   
          {  
              printf("oops! stop!!!\n");  
              _exit(0);  
          }  
            
            int main()  
            {  
                int res;  
                pthread_t A, B;  
              
                signal(SIGINT, stop);   
                res = pthread_create(&A, NULL, One, NULL);  
                res = pthread_create(&B, NULL, Two, NULL);  
                res = pthread_join(A, NULL);  
                res = pthread_join(B, NULL);  
              
                return 0;  
            }  
