CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lcurl -pthread -lz
SOURCES=ModworksSDK.cpp Utility.cpp CurlWrapper.cpp ZipperWrapper.cpp Mod.cpp ../lib/libZipper-static.a
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libmodworks.a

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I ../include

$(LIBRARY): $(OBJECTS)
	ar $(ARFLAGS) $@ $^

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(LIBRARY)
