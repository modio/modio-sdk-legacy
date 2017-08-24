include Sources.mk

CC = g++
CFLAGS = -c -Wall -std=c++11 `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS = -lcurl -pthread -lz
SOURCES = $(MODWORKS_SOURCES)
OBJECTS = $(SOURCES:.cpp=.o)
LIBRARY = libmodworks.a

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I ../include

$(LIBRARY): $(OBJECTS)
	ar $(ARFLAGS) $@ $^ ../lib/libz.a

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(LIBRARY)
