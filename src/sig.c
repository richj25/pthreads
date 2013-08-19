#include "sig.h"
#include <stdio.h>

void mysigchild_handler()
{

  printf("Caught mysigchild");
}

bool install_mysigchild_signal_handler()
{
    struct sigaction new_action;
    sigset_t blockMask;

    sigemptyset(&blockMask);

    new_action.sa_handler = mysigchild_handler;
    new_action.sa_mask = blockMask;
    new_action.sa_flags = 0;
    if (sigaction(MYSIGCHILD, &new_action, NULL) != 0)
        return false;
    return true;
}
