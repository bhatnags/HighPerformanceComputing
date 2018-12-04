CC=gcc
CFLAGS = -Wall -g

TARGET1 = main
TARGET2 = read_write

all: prog

prog: $(TARGET1).o $(TARGET2).o
	$(CC) $(CFLAGS) $(TARGET1).o $(TARGET2).o -o prog

$(TARGET1).o: $(TARGET1).c
	$(CC) $(CFLAGS) -c $(TARGET1).c

$(TARGET2).o: $(TARGET2).c
	$(CC) $(CFLAGS) -c $(TARGET2).c


clean:
	rm -f prog $(TARGET1).o $(TARGET2).o
