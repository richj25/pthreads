#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

struct thread_data {
   int counter;
};

void* work_routine(void *data);

void* work_routine(void *data)
{
   struct thread_data  *user_data = (struct thread_data *)data;
   user_data->counter++;
   
}

int main(int argc,char **argv)
{
    pthread_t tid;
    pthread_attr_t attr;
    sigset_t set;
    int retval;
    struct thread_data *data;

    data = (struct thread_data *)malloc(sizeof(struct thread_data));
    data->counter = 0;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    retval = pthread_create(&tid,&attr,&work_routine,(void *)data);
    if (retval == 0) { 
        printf("Thread creation succeeded\n");
    }
    else {
        printf("Thread creation failed\n"); 
        if (errno = EAGAIN) 
          printf("No resources\n");
    }

    if (data->counter == 1) 
      printf("Data passing works %d\n",data->counter);
    else 
      printf("Data passing doesn't work\n");

    return(0);
}
