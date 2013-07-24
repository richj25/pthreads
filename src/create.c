#define _GNU_SOURCE
#include <sched.h>
#include "pthread.h"
#include "pthread_lib.h"
#include "thread_db.h"
#include <signal.h>
#include "mem.h"
#include <stdio.h>

int thread_wrapper(void *arg)
{
    thread_func_t *user_thread = (thread_func_t *)arg;

    user_thread->thread_func(user_thread->thread_data);

    return 0;
}

int create(pthread_t *ptid, const pthread_attr_t *attr, void * (*start_routine) (void *), void *arg)
{
    int flags;
    volatile pid_t* ctidloc;
    int tid;
    thread_func_t *user_thread;

    user_thread = (thread_func_t *)malloc(sizeof(thread_func_t));

    user_thread->thread_func = start_routine;
    user_thread->thread_data = arg;
    user_thread->detachstate = attr->detachstate;
    user_thread->ptid = -1;

    void *stack = memmap(NULL,attr->stacksize, \
                  PROT_READ | PROT_WRITE, \
                  MAP_PRIVATE | MAP_ANONYMOUS | MAP_GROWSDOWN, \
                  -1, 0);

    if (stack == MAP_FAILED) return ENOMEM;

    *ptid = initialize_thread_db_entry(attr->detachstate,attr->stacksize,stack);

    if (*ptid == -1) {
        memunmap(stack,attr->stacksize);
        return EAGAIN;
    }

    user_thread->ptid = *ptid;

    flags = CLONE_VM | CLONE_THREAD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND |\
            CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_IO | SIGCHLD;

    ctidloc = get_tid_location_from_db_entry(*ptid);

    tid = clone(thread_wrapper,stack+attr->stacksize, flags, user_thread, ctidloc, NULL, ctidloc);

    if (tid == -1) {
        recycle_thread_db_entry(*ptid);
        return errno;
    }

    set_nonvolatile_tid(*ptid,tid);

    free(user_thread);

    return 0;
}
