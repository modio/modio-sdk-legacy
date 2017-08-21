CC=g++
CFLAGS=-c -Wall -std=c++11 `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS=-lcurl -pthread -lz `pkg-config --cflags --libs gtk+-3.0`
SOURCES=Example.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Example
LIBRARIES=../src/libmodworks.a

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I ../include

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(EXECUTABLE)

run:
	$ ./$(EXECUTABLE)
