include Sources.mk

CC = g++
CFLAGS = -c -Wall -std=c++11 -fPIC
LDFLAGS = -lcurl -lz
SOURCES = $(MODIO_SOURCES)
OBJECTS = $(SOURCES:.cpp=.o)
LIBRARY = modio.so

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I ../include

$(LIBRARY): $(OBJECTS)
	$(CC) -fPIC -shared -o $@ $^ ../lib/libz.a

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(LIBRARY)
