#ifndef PTHREADLIB_H
#define PTHREADLIB_H 1

#include "pthread.h"
#include <stdlib.h>
#include <errno.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <unistd.h>

#define DEFAULT_STACK_SIZE 8388608
#define PTHREAD_STACK_MIN 4096
#define false 0
#define true 1

typedef int bool;

typedef struct thread_func {
    void *thread_data;
    void *(*thread_func)(void *);
    int  detachstate;
    pthread_t ptid;
} thread_func_t;

int thread_wrapper(void * );

int attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
int attr_setdetachstate(pthread_attr_t *attr, int detachstate);
int attr_getstacksize(const pthread_attr_t *restrict attr, size_t *restrict stacksize);
int attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
int attr_destroy(pthread_attr_t *attr);
int attr_init(pthread_attr_t *attr);

int join(pthread_t ptid, void **value_ptr);
int equal(pthread_t ptid1, pthread_t ptid2);
pthread_t self(void);

int create(pthread_t *ptid, const pthread_attr_t *attr, 
           void * (*start_routine) (void *), void *arg);

#endif
