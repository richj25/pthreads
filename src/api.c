#include "pthread.h"
#include "pthread_lib.h"
#include <stdio.h>

int pthread_attr_destroy(pthread_attr_t *attr)
{
    return attr_destroy(attr);
}


int pthread_attr_init(pthread_attr_t *attr)
{
    return attr_init(attr);
}

int pthread_attr_getstacksize(const pthread_attr_t *restrict attr, size_t *restrict stacksize)
{
    return attr_getstacksize(attr,stacksize);
}

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize)
{
    return attr_setstacksize(attr,stacksize);
}

int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate)
{
    return attr_getdetachstate(attr, detachstate);
}

int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate)
{
    return attr_setdetachstate(attr, detachstate);
}

int pthread_join(pthread_t thread, void **value_ptr)
{
    return join(thread, value_ptr);
}

int pthread_equal(pthread_t t1, pthread_t t2)
{
    return equal(t1,t2);
}

pthread_t pthread_self(void)
{
    return self();
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          int (*start_routine) (void *), void *arg)
{
    return create(thread,attr,start_routine,arg);
}
