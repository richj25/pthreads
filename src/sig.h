#include <signal.h>
#include "pthread_lib.h"

#define MYSIGCHILD SIGUSR1

void mysigchild_handler();
bool install_mysigchild_signal_handler();
