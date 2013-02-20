#include "thread_db.h"


void init_thread_db()
{
    thread_db = (db_entry_t *) calloc(PTHREAD_THREAD_MAX,sizeof(db_entry_t));
    thread_db[0].inuse = true;
    thread_db[0].state = RUNNING;
    thread_db[0].nonvolatile_tid = getpid();
}

void destroy_thread_db()
{
    free(thread_db);
}

pthread_t initialize_thread_db_entry(int detachstate, size_t stacksize, void * stackaddr)
{
    int i;

    for (i=0;i<PTHREAD_THREAD_MAX;i++)
        if (thread_db[i].inuse == false)
        {
            thread_db[i].inuse = true;
            thread_db[i].detachstate = detachstate;
            thread_db[i].stacksize = stacksize;
            thread_db[i].stackaddr = stackaddr;
            thread_db[i].state = RUNNING;
            return i;
        }
    return -1;
}

volatile pid_t* get_volatile_tid_location_from_db_entry(int i)
{
    return &(thread_db[i].volatile_tid);
}

volatile pid_t* get_volatile_tidloc_from_pthread_id(pthread_t ptid)
{
    return &(thread_db[(int) ptid].volatile_tid);
}

pthread_t get_pthread_id_from_tid(pid_t tid)
{
    int i;

    for (i=0;i<PTHREAD_THREAD_MAX;i++)
        if (thread_db[i].nonvolatile_tid == tid) return (pthread_t)i;
    return -1;
}

void set_nonvolatile_tid_for_entry(int index,pid_t tid)
{
    thread_db[index].nonvolatile_tid = tid;
}

void recycle_thread_db_entry_by_index(int index)
{
    thread_db[index].inuse = false;
    munmap(thread_db[index].stackaddr,thread_db[index].stacksize);
}

void recycle_thread_db_entry_by_pthread_id(pthread_t ptid)
{
    thread_db[(int)ptid].inuse = false;
    munmap(thread_db[(int)ptid].stackaddr,thread_db[(int)ptid].stacksize);
}

void wait_for_volatile_tid_to_clear(pthread_t ptid)
{
}
