#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int work_routine(void *num);

int work_routine(void *num)
{
    printf("Executing thread \n");
    pthread_join(pthread_self(),NULL);
    sleep(5);
}

int main(int argc,char **argv)
{
    pthread_t tid;
    pthread_attr_t attr;
    int retval;

    pthread_attr_init(&attr);

    retval = pthread_create(&tid,&attr,work_routine,NULL);
    if (retval != 0) printf("Thread creation failed\n");
    else printf("Thread creation succeeded %d\n",tid);

    sleep(10);
}
