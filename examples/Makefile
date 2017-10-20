CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lcurl -pthread -lz
SOURCES=Example.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Example
LIBRARIES=../src/modio.so

all: Example Authentication GetMods

Example: Example.cpp
	$(CC) $(CFLAGS) Example.cpp -o Example.o -I ../include
	$(CC) $(LDFLAGS) Example.o $(LIBRARIES) -o Example

Authentication: Authentication.cpp
	$(CC) $(CFLAGS) Authentication.cpp -o Authentication.o -I ../include
	$(CC) $(LDFLAGS) Authentication.o $(LIBRARIES) -o Authentication

GetMods: GetMods.cpp
	$(CC) $(CFLAGS) GetMods.cpp -o GetMods.o -I ../include
	$(CC) $(LDFLAGS) GetMods.o $(LIBRARIES) -o GetMods

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f Example
	-rm -f Authentication

run:
	$ ./$(EXECUTABLE)
