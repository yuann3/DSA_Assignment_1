CC=g++
CFLAGS=-Wall -g -std=c++11
LDFLAGS=
SOURCES=browser.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Browser

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
