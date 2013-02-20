CC=/usr/bin/gcc
INCLUDE_PATH=/home/richj/pthreads/src
SHARED_LIB_PATH=/home/richj/pthreads/src

PTHREAD_LIB=-lpthread
CFLAGS= -g -std=gnu99

OBJS=create

all: $(OBJS)

create: create.c
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -L$(SHARED_LIB_PATH) $(PTHREAD_LIB) -o create create.c

clean: 
	rm $(OBJS)
