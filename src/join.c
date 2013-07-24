#include "pthread.h"
#include "thread_db.h"
#include <stdio.h>

int join(pthread_t ptid, void **value_ptr)
{
    wait_for_thread_exit(ptid);

    recycle_thread_db_entry(ptid); 
    return 0;
}
