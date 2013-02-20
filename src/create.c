#define _GNU_SOURCE
#include <sched.h>
#include "pthread.h"
#include "pthread_lib.h"
#include "thread_db.h"
#include <sys/mman.h>
#include <stdio.h>

int create(pthread_t *ptid, const pthread_attr_t *attr, int (*start_routine) (void *), void *arg)
{
    int flags;
    volatile pid_t* ctid;
    int tid;
    int index;

    void *stack = mmap(NULL,attr->stacksize, \
                  PROT_READ | PROT_WRITE, \
                  MAP_PRIVATE | MAP_ANONYMOUS | MAP_GROWSDOWN, \
                  -1, 0);

    flags = CLONE_VM | CLONE_THREAD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND |\
            CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | SIGCHLD;

    index = initialize_thread_db_entry(attr->detachstate,attr->stacksize,stack);

    if (index == -1) return EAGAIN;

    ctid = get_volatile_tid_location_from_index(*ptid);
    
    tid = clone(start_routine,stack+attr->stacksize, flags, arg, ctid, NULL, ctid);



    if (tid != -1) {
         set_nonvolatile_tid_for_entry(index,tid);
         *ptid = index;
         return 0;
    }
    else {
        recycle_thread_db_entry_by_index(index);
        return errno;
    }
}
