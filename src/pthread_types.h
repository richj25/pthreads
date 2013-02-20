#ifndef _BITS_PTHREADTYPES_H     
#define _BITS_PTHREADTYPES_H    1
#include <stddef.h>

#define pthread_t int

typedef struct pthread_attr {
    size_t stacksize;
    int detachstate;
} pthread_attr_t;

#endif
