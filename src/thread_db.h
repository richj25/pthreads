#include "pthread.h"
#include "pthread_lib.h"
#include <sys/types.h>
#include <stdlib.h>

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

bool init_thread_db();
void destroy_thread_db();
pthread_t initialize_thread_db_entry(int detachstate, size_t stacksize, void * stackaddr);
volatile pid_t* get_tid_location_from_db_entry(pthread_t ptid);
void recycle_thread_db_entry(pthread_t ptid);
void wait_for_thread_exit(pthread_t ptid);
void set_nonvolatile_tid(pthread_t ptid, pid_t tid);
pthread_t get_pthread_id_from_tid(pid_t tid);



int return_stack_size(pthread_t ptid);
void *return_stack_addr(pthread_t ptid);
