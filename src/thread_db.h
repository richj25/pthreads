#include "pthread.h"
#include "pthread_lib.h"
#include <sys/types.h>
#include <stdlib.h>
#include <sys/mman.h>

enum thread_state {RUNNING, UNJOINED, EXITED};

typedef struct db_entry {
    int                         inuse;
    volatile pid_t              volatile_tid;
    pid_t                       nonvolatile_tid;
    int                         detachstate;
    size_t                      stacksize;
    void *                      stackaddr;
    enum thread_state           state;
} db_entry_t;

db_entry_t *thread_db;

void init_thread_db();
void destroy_thread_db();
volatile pid_t* get_volatile_tid_location_from_index(int i);
pthread_t initialize_thread_db_entry(int detachstate, size_t stacksize, void * stackaddr);
volatile pid_t* get_volatile_tid_location_from_pthread_id(pthread_t ptid);
void set_nonvolatile_tid_for_entry(int index,pid_t tid);
void recycle_thread_db_entry_by_index(int index);
void recycle_thread_db_entry_by_pthread_id(pthread_t ptid);
void wait_for_volatile_tid_to_clear(pthread_t ptid);
pthread_t get_pthread_id_from_tid(pid_t tid);
