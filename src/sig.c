#include "sig.h"

void mysigchild_handler()
{
}

bool install_mysigchild_signal_handler()
{
    struct sigaction new_action;
    sigset_t block_mask;

    sigemptyset(&block_mask);
    new_action.sa_handler = mysigchild_handler;
    new_action.sa_mask = block_mask;
    new_action.sa_flags = 0;
    if (sigaction(MYSIGCHILD, &new_action, NULL) != 0)
        return false;
    return true;
}
