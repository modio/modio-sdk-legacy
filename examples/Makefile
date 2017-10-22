CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lcurl -pthread -lz
SOURCES=Example.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Example
LIBRARIES=../src/modio.so

all: 1_Authentication 2_BrowseMods 3_ErrorResponse 4_DownloadImages 5_InstallMod 6_CreateMod

1_Authentication: 1_Authentication.cpp
	$(CC) $(CFLAGS) 1_Authentication.cpp -o 1_Authentication.o -I ../include
	$(CC) $(LDFLAGS) 1_Authentication.o $(LIBRARIES) -o 1_Authentication

2_BrowseMods: 2_BrowseMods.cpp
	$(CC) $(CFLAGS) 2_BrowseMods.cpp -o 2_BrowseMods.o -I ../include
	$(CC) $(LDFLAGS) 2_BrowseMods.o $(LIBRARIES) -o 2_BrowseMods

3_ErrorResponse: 3_ErrorResponse.cpp
	$(CC) $(CFLAGS) 3_ErrorResponse.cpp -o 3_ErrorResponse.o -I ../include
	$(CC) $(LDFLAGS) 3_ErrorResponse.o $(LIBRARIES) -o 3_ErrorResponse

4_DownloadImages: 4_DownloadImages.cpp
	$(CC) $(CFLAGS) 4_DownloadImages.cpp -o 4_DownloadImages.o -I ../include
	$(CC) $(LDFLAGS) 4_DownloadImages.o $(LIBRARIES) -o 4_DownloadImages

5_InstallMod: 5_InstallMod.cpp
	$(CC) $(CFLAGS) 5_InstallMod.cpp -o 5_InstallMod.o -I ../include
	$(CC) $(LDFLAGS) 5_InstallMod.o $(LIBRARIES) -o 5_InstallMod

6_CreateMod: 6_CreateMod.cpp
	$(CC) $(CFLAGS) 6_CreateMod.cpp -o 6_CreateMod.o -I ../include
	$(CC) $(LDFLAGS) 6_CreateMod.o $(LIBRARIES) -o 6_CreateMod

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f Example
	-rm -f Authentication
	-rm -f GetMods
	-rm -f InstallMod
	-rm -f DownloadImages

run:
	$ ./$(EXECUTABLE)
