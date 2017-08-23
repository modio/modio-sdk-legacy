CC=g++
CFLAGS=-c -Wall -std=c++11 `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS=-lcurl -pthread -lz
SOURCES=ModworksSDK.cpp Utility.cpp CurlWrapper.cpp MinizipWrapper.cpp Mod.cpp minizip/unzip.cpp minizip/ioapi.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libmodworks.a

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I ../include

$(LIBRARY): $(OBJECTS)
	ar $(ARFLAGS) $@ $^ ../lib/libz.a

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(LIBRARY)
