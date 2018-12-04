CC = gcc
CFLAGS = -W -Wall -lm -Wextra -g

SOURCES = main.c greedy.c brute.c
OBJECTS = main.o greedy.o brute.o 
TARGET = prog
DEL_FILE= rm -f

INCPATH		= /usr/include/

all: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CFLAGS)

main.o: main.c greedy.h
	$(CC) -c main.c $(CFLAGS) -I$(INCPATH)

greedy.o: greedy.c greedy.h
	$(CC) -c greedy.c $(CFLAGS) -I$(INCPATH)

brute.o: brute.c brute.h
	$(CC) -c brute.c $(CFLAGS) -I$(INCPATH)

test: prog
	./prog -n 16

graph: prog
	./prog -n 5 -g > output.dat
	./prog -n 10 -g >> output.dat
	./prog -n 15 -g  >> output.dat
	./prog -n 20 -g  >> output.dat
	./prog -n 25 -g  >> output.dat
	./prog -n 30 -g  >> output.dat
	./prog -n 35 -g  >> output.dat
	./prog -n 40 -g  >> output.dat
	./prog -n 45 -g  >> output.dat
	./prog -n 50 -g  >> output.dat
	./prog -n 55 -g  >> output.dat
	./prog -n 60 -g  >> output.dat
	./prog -n 65 -g  >> output.dat
	./prog -n 70 -g  >> output.dat
	./prog -n 75 -g  >> output.dat
	./prog -n 80 -g   >> output.dat
	./prog -n 85 -g  >> output.dat
	./prog -n 90 -g  >> output.dat
	./prog -n 95 -g  >> output.dat
	./prog -n 100 -g  >> output.dat

clean:
	$(DEL_FILE) $(OBJECTS) $(TARGET)
