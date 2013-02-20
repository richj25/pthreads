#include "pthread_lib.h"

int attr_getdetachstate(const pthread_attr_t *attr, int *detachstate)
{
    *detachstate =  attr->detachstate;
    return 0;
}

int attr_setdetachstate(pthread_attr_t *attr, int detachstate)
{
    if ((detachstate != PTHREAD_CREATE_DETACHED) && ( detachstate != PTHREAD_CREATE_JOINABLE))
        return EINVAL;
    attr->detachstate = detachstate;
    return 0;
}

int attr_getstacksize(const pthread_attr_t *restrict attr, size_t *restrict stacksize)
{
    *stacksize = attr->stacksize;
    return 0;
}

int attr_setstacksize(pthread_attr_t *attr, size_t stacksize)
{
    if (stacksize < PTHREAD_STACK_MIN) return EINVAL;
    attr->stacksize = stacksize;
    return 0; 
}

int attr_destroy(pthread_attr_t *attr)
{
    attr->stacksize=0;
    return 0;
}

int attr_init(pthread_attr_t *attr)
{
    attr->stacksize = DEFAULT_STACK_SIZE;
    attr->detachstate = PTHREAD_CREATE_JOINABLE;
    return 0;
}
