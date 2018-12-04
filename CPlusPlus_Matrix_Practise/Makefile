OBJECTS = Matrix.o testMatrix.o
TARGET = testMatrix
CC = g++
CFLAGS = -Wall -lm

all: Matrix.o testMatrix.o
	$(CC) -o $(TARGET) Matrix.o testMatrix.o $(CFLAGS)

Matrix.o: Matrix.cc Matrix.h
	$(CC) -c Matrix.cc $(CFLAGS)

testMatrix.o: testMatrix.cc Matrix.h
	$(CC) -c testMatrix.cc $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)

