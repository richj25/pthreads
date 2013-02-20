CC=/usr/bin/gcc
LD=/usr/bin/gcc

INCLUDES=-I/home/richj/pthreads/src
WARNINGS=-Wall
DEBUG=-g
CFLAGS=-c -fPIC -std=gnu99 -D__USE_MISC
LDOPT=-shared 

TARGET=libpthread.so
SOURCES=$(shell echo *.c)
HEADERS=$(shell echo *.h)
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDOPT) -o $(TARGET) $(OBJECTS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(WARNINGS) $(DEBUG) $(INCLUDES) $(SOURCES)

clean: 
	rm $(OBJECTS) $(TARGET)
