#include "pthread_lib.h"
#include "thread_db.h"
#include "sig.h"

static void con() __attribute__((constructor));
static void dest() __attribute__((destructor));

static void con()
{
    init_thread_db();
    set_signal_handlers();
}

static void dest()
{
    destroy_thread_db();
}
