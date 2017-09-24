include Sources.mk

CC = g++
CFLAGS = -c -Wall -std=c++11 -fPIC
LDFLAGS = -lcurl -pthread -lz
SOURCES = $(MODWORKS_SOURCES)
OBJECTS = $(SOURCES:.cpp=.o)
LIBRARY = modworks.so

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I ../include

$(LIBRARY): $(OBJECTS)
	$(CC) -shared -o $@ $^ ../lib/libz.a

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(LIBRARY)
