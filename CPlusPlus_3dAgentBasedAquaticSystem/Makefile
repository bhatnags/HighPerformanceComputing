OBJECTS = main.o functions.o mapCoordinates.o myrand.o
TARGET = aquatic
CXFLAGS = -Wall -lm -g -Wextra -std=c++11



all: main.o $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(CXFLAGS)

main.o: main.cpp functions.h
	$(CXX) -c main.cpp $(CXFLAGS)

functions.o: functions.cpp functions.h myrand.h mapCoordinates.h
	$(CXX) -c functions.cpp $(CXFLAGS)

mapCoordinates.o: mapCoordinates.cpp mapCoordinates.h
	$(CXX) -c mapCoordinates.cpp $(CXFLAGS)

myrand.o: myrand.cpp myrand.h
	$(CXX) -c myrand.cpp $(CXFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET)

