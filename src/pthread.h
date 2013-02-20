#ifndef _PTHREAD_H          
#define _PTHREAD_H      1

#include <pthread_types.h>

#define PTHREAD_THREAD_MAX 256
#define PTHREAD_CREATE_DETACHED 0
#define PTHREAD_CREATE_JOINABLE 1

int pthread_attr_getstacksize(const pthread_attr_t *restrict attr, size_t *restrict stacksize);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);

int pthread_join(pthread_t thread, void **value_ptr);
pthread_t pthread_self(void);
int pthread_equal(pthread_t t1, pthread_t t2);

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, int  (*start_routine) (void *), void *arg);

#endif

