OBJECTS = main.o functions.o
TARGET = connectFour
CC = g++
CFLAGS = -Wall -lm -g

all: main.o functions.o
	$(CC) -o $(TARGET) main.o functions.o $(CFLAGS)

main.o: main.cpp functions.h
	$(CC) -c main.cpp $(CFLAGS)

functions.o: functions.cpp functions.h
	$(CC) -c functions.cpp $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)

