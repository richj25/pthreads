#include <sys/mman.h>

void * memmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int memunmap(void *addr, size_t length);

