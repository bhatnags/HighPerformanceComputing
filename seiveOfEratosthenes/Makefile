CC = gcc
CFLAGS = -lm -fopenmp 

SOURCES = main.c functions.c
OBJECTS = main.o functions.o
TARGET = seiveOfEratothenes
DEL_FILE= rm -f

INCPATH		= /usr/include/

all: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CFLAGS)

main.o: main.c functions.h 
	$(CC) -c main.c $(CFLAGS) -I$(INCPATH)

functions.o: functions.c functions.h
	$(CC) -c functions.c $(CFLAGS) -I$(INCPATH)

test: seiveOfEratothenes
	./seiveOfEratothenes -n 10 -t 4 -p >output_10_4.txt

graphs: seiveOfEratothenes
	./seiveOfEratothenes -n 10 -t 1 >output.dat
	./seiveOfEratothenes -n 10 -t 3 >>output.dat
	./seiveOfEratothenes -n 10 -t 6 >>output.dat
	./seiveOfEratothenes -n 10 -t 9 >>output.dat
	./seiveOfEratothenes -n 10 -t 12 >>output.dat
	./seiveOfEratothenes -n 50 -t 3 >>output.dat
	./seiveOfEratothenes -n 50 -t 6 >>output.dat
	./seiveOfEratothenes -n 50 -t 9 >>output.dat
	./seiveOfEratothenes -n 50 -t 12 >>output.dat
	./seiveOfEratothenes -n 50 -t 15 >>output.dat
	./seiveOfEratothenes -n 100 -t 3 >>output.dat
	./seiveOfEratothenes -n 100 -t 6 >>output.dat
	./seiveOfEratothenes -n 100 -t 9 >>output.dat
	./seiveOfEratothenes -n 100 -t 12 >>output.dat
	./seiveOfEratothenes -n 100 -t 15 >>output.dat
	./seiveOfEratothenes -n 200 -t 3 >>output.dat
	./seiveOfEratothenes -n 200 -t 6 >>output.dat
	./seiveOfEratothenes -n 200 -t 9 >>output.dat
	./seiveOfEratothenes -n 200 -t 12 >>output.dat
	./seiveOfEratothenes -n 200 -t 15 >>output.dat
	./seiveOfEratothenes -n 500 -t 3 >>output.dat
	./seiveOfEratothenes -n 500 -t 6 >>output.dat
	./seiveOfEratothenes -n 500 -t 9 >>output.dat
	./seiveOfEratothenes -n 500 -t 12 >>output.dat
	./seiveOfEratothenes -n 500 -t 15 >>output.dat
	./seiveOfEratothenes -n 1000 -t 3 >>output.dat
	./seiveOfEratothenes -n 1000 -t 6 >>output.dat
	./seiveOfEratothenes -n 1000 -t 9 >>output.dat
	./seiveOfEratothenes -n 1000 -t 12 >>output.dat
	./seiveOfEratothenes -n 1000 -t 15 >>output.dat
	./seiveOfEratothenes -n 5000 -t 3 >>output.dat
	./seiveOfEratothenes -n 5000 -t 6 >>output.dat
	./seiveOfEratothenes -n 5000 -t 9 >>output.dat
	./seiveOfEratothenes -n 5000 -t 12 >>output.dat
	./seiveOfEratothenes -n 5000 -t 15 >>output.dat
	./seiveOfEratothenes -n 8000 -t 3 >>output.dat
	./seiveOfEratothenes -n 8000 -t 6 >>output.dat
	./seiveOfEratothenes -n 8000 -t 9 >>output.dat
	./seiveOfEratothenes -n 8000 -t 12 >>output.dat
	./seiveOfEratothenes -n 8000 -t 15 >>output.dat
	./seiveOfEratothenes -n 10000 -t 3 >>output.dat
	./seiveOfEratothenes -n 10000 -t 6 >>output.dat
	./seiveOfEratothenes -n 10000 -t 9 >>output.dat
	./seiveOfEratothenes -n 10000 -t 12 >>output.dat
	./seiveOfEratothenes -n 10000 -t 15 >>output.dat

clean:
	$(DEL_FILE) $(OBJECTS) $(TARGET)
