#include "pthread_lib.h"
#include "thread_db.h"

int equal(pthread_t ptid1, pthread_t ptid2)
{
    if ((int)ptid1 == (int)ptid2) return true;
    else return false;
}

pthread_t self(void)
{
    pid_t tid;

    tid =  (pid_t)syscall( __NR_gettid );

    return get_pthread_id_from_tid(tid);
}


