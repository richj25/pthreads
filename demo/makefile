CC=/usr/bin/gcc
INCLUDE_PATH=$(CURDIR)/../src
SHARED_LIB_PATH=$(CURDIR)/../src

PTHREAD_LIB=-lpthread
CFLAGS= -g -std=gnu99

OBJS=create

all: $(OBJS)

create: create.c
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -L$(SHARED_LIB_PATH) $(PTHREAD_LIB) -o create create.c

clean: 
	rm $(OBJS)
