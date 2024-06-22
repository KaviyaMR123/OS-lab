#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int semaphore=1;
int state=1;
void wait(int *semaphore)
{
    while(*semaphore<=0);
    *semaphore--;
}
void signal(int *semaphore)
{
    *semaphore++;
}
void *thread_f(void * arg)
{
    int no= *((int*)arg);
    int st=no;
    while(1)
    {
        wait(&semaphore);
        if(state==st)
        {
            printf("From thread [%d] -> %d\n",st,no);
            no+=2;
            state=3-st;
        }
        signal(&semaphore);
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t id1,id2;
    int odd=1;
    int even=2;
    pthread_create(&id1,NULL,(void *)thread_f,&odd);
    pthread_create(&id2,NULL,(void *)thread_f,&even);
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    return 0;
}
