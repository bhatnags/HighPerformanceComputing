CC = gcc
CFLAGS = -Wall -Wextra -lm -pthread -g
OBJECTS = serial.o parallel.o avltree.o
DEL_FILE = rm -f
INCPATH = /usr/include
TARGET_PARALLEL = progParallel
TARGET_SERIAL = progSerial


all: parallel serial

parallel: parallel.o avltree.o
	$(CC) -o $(TARGET_PARALLEL) parallel.o avltree.o $(CFLAGS) -I$(INCPATH)

serial: serial.o avltree.o
	$(CC) -o $(TARGET_SERIAL) serial.o avltree.o $(CFLAGS) -I$(INCPATH)

parallel.o: parallel.c avltree.h	
	$(CC) -c parallel.c $(CFLAGS) -I$(INCPATH)

serial.o: serial.c avltree.h	
	$(CC) -c serial.c $(CFLAGS) -I$(INCPATH)

avltree.o: avltree.c avltree.h
	$(CC) -c avltree.c $(CFLAGS) -I$(INCPATH)

clean:
	$(DEL_FILE) $(OBJECTS) $(TARGET_PARALLEL) $(TARGET_SERIAL)

