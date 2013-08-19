#include "thread_db.h"
#include "mem.h"


bool init_thread_db()
{
    thread_db = (db_entry_t *) calloc(PTHREAD_THREAD_MAX,sizeof(db_entry_t));

    if (thread_db == NULL) return false;

    thread_db[0].inuse = true;

    return true;
}

void destroy_thread_db()
{
    free(thread_db);
}

pthread_t initialize_thread_db_entry(int detachstate, size_t stacksize, void * stackaddr, thread_func_t * user_thread)
{
    int index;

    for (index=0;index<PTHREAD_THREAD_MAX;index++)
        if (thread_db[index].inuse == false)
        {
            thread_db[index].inuse = true;
            thread_db[index].detachstate = detachstate;
            thread_db[index].stacksize = stacksize;
            thread_db[index].stackaddr = stackaddr;
            thread_db[index].state = RUNNING;
            thread_db[index].user_thread = user_thread;
            return index;
        }
    return -1;
}

volatile pid_t* get_tid_location_from_db_entry(pthread_t ptid)
{
    int index = (int) ptid;

    return &(thread_db[index].volatile_tid);
}

void recycle_thread_db_entry(pthread_t ptid)
{
    int index = (int)ptid;

    thread_db[index].inuse = false;
    memunmap(thread_db[index].stackaddr,thread_db[index].stacksize);
    free(thread_db[index].user_thread);
}

void wait_for_thread_exit(pthread_t ptid)
{
    
}

void set_nonvolatile_tid(pthread_t ptid, pid_t tid)
{
    int index = (int)ptid;

    thread_db[index].nonvolatile_tid = tid;
}

pthread_t get_pthread_id_from_tid(pid_t tid)
{
    int index;

    for (index=0;index<PTHREAD_THREAD_MAX;index++)
        if (thread_db[index].nonvolatile_tid == tid) return (pthread_t)index;

    return (pthread_t) -1;
}

int return_stack_size(pthread_t ptid)
{
    int index = (pthread_t)ptid;
    return thread_db[index].stacksize;
}

void *return_stack_addr(pthread_t ptid)
{
    int index = (pthread_t)ptid;
    return thread_db[index].stackaddr;
}
