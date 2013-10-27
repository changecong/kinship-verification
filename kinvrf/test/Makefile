CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

test:
	./$(EXECUTABLE)

clean:
	rm -rf *.o $(EXECUTABLE)
