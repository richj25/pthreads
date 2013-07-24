#include <stdio.h>
#include "pthread_lib.h"
#include "thread_db.h"
#include "sig.h"

static void con() __attribute__((constructor));
static void dest() __attribute__((destructor));

static void con()
{
    if (init_thread_db() == false) printf("Could not initialize thread_db\n");
    if (install_mysigchild_signal_handler() == false) printf("Could not install signal handler\n");
}

static void dest()
{
    destroy_thread_db();
}
