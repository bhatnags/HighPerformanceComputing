CC = gcc
CFLAGS = -W -Wall -lm -fopenmp -Wextra

SOURCES = main.c serial.c openmp.c
OBJECTS = main.o serial.o openmp.o
TARGET = backwardGauss
DEL_FILE= rm -f

INCPATH		= /usr/include/

all: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CFLAGS)

main.o: main.c serial.h openmp.h
	$(CC) -c main.c $(CFLAGS) -I$(INCPATH)

serial.o: serial.c serial.h
	$(CC) -c serial.c $(CFLAGS) -I$(INCPATH)

openmp.o: openmp.c openmp.h 
	$(CC) -c openmp.c $(CFLAGS) -I$(INCPATH)

test: backwardGauss
	./backwardGauss -n 10 -t 4 -p>output_10_1.txt

graphs: backwardGauss
	./backwardGauss -n 5 -t 1 >output.dat
	./backwardGauss -n 5 -t 3 >>output.dat
	./backwardGauss -n 10 -t 3 >>output.dat
	./backwardGauss -n 50 -t 3 >>output.dat
	./backwardGauss -n 100 -t 3 >>output.dat
	./backwardGauss -n 10 -t 6 >>output.dat
	./backwardGauss -n 50 -t 6 >>output.dat
	./backwardGauss -n 100 -t 6 >>output.dat
	./backwardGauss -n 10 -t 9 >>output.dat
	./backwardGauss -n 50 -t 9 >>output.dat
	./backwardGauss -n 100 -t 9 >>output.dat
	./backwardGauss -n 200 -t 6 >>output.dat
	./backwardGauss -n 200 -t 9 >>output.dat
	./backwardGauss -n 200 -t 12 >>output.dat
	./backwardGauss -n 500 -t 6 >>output.dat
	./backwardGauss -n 500 -t 9 >>output.dat
	./backwardGauss -n 500 -t 12 >>output.dat
	./backwardGauss -n 500 -t 15 >>output.dat
	./backwardGauss -n 700 -t 6 >>output.dat
	./backwardGauss -n 700 -t 9 >>output.dat
	./backwardGauss -n 700 -t 12 >>output.dat
	./backwardGauss -n 700 -t 15 >>output.dat
	./backwardGauss -n 1000 -t 9 >>output.dat
	./backwardGauss -n 1000 -t 12 >>output.dat
	./backwardGauss -n 1000 -t 15 >>output.dat
	./backwardGauss -n 2000 -t 12 >>output.dat
	./backwardGauss -n 2000 -t 15 >>output.dat

clean:
	$(DEL_FILE) $(OBJECTS) $(TARGET)
