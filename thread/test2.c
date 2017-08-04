/*  POSIX 下线程控制的实验程序残缺版 */ 
#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <ctype.h>
#include <pthread.h> 

#define MAX_THREAD 3 /* 线程的个数 */
unsigned long long main_counter, counter[MAX_THREAD]; 
/* unsigned long  long是比long还长的整数 */
void* thread_worker(void*); 
pthread_t pthread_id[MAX_THREAD] = {0}; /* 存放线程id*/ 

int main(int argc,char* argv[])
{     
    int i, rtn, ch;     
//    pthread_t pthread_id[MAX_THREAD] = {0}; /* 存放线程id*/ 
    for (i=0; i<MAX_THREAD; i++)
    {   pthread_t tid;   
        pthread_create( &tid,NULL,(void *)thread_worker,(void *)&i );
        sleep(1);
    }  
    sleep(1);
    do
    {
        /* 用户按一次回车执行下面的循环体一次。按q退出 */          
        unsigned long long sum = 0;    
        /* 求所有线程的counter的和 */
        for (i=0; i<MAX_THREAD; i++) 
        {
            /* 求所有counter的和 */         
            sum += counter[i];             
            printf("%llu ", counter[i]);        
        }
        printf("%llu/%llu\n", main_counter, sum);   
    }while ((ch = getchar()) != 'q'); 
    return 0;
} 
void* thread_worker(void* p)
{   
    int thread_num;  
    /* 在这里填写代码，把main中的i的值传递给thread_num */ 
    thread_num = *(int *)p;
    pthread_id[thread_num] = pthread_self();
    for(;;) 
    { /* 无限循环 */      
     counter[thread_num]++; /* 本线程的counter加一 */ 
     main_counter++; /* 主counter 加一 */   
    } 
}

