#include "pthread.h"
#include "thread_db.h"
#include <stdio.h>

int join(pthread_t ptid, void **value_ptr)
{
    wait_for_volatile_tid_to_clear(ptid);

    recycle_thread_db_entry_by_pthread_id(ptid); 
    return 0;
}
