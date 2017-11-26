CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lcurl -lz
SOURCES=Example.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Example
LIBRARIES=../src/modio.so

EXAMPLES=01_Authentication 02_BrowseMods 03_ErrorResponse 04_DownloadImages 05_EditImage 06_InstallModfile 07_AddModfile 08_EditModfile 09_AddMod 10_EditMod 11_DeleteMod 12_GetTags 13_AddTags 14_DeleteTags

all: $(EXAMPLES)

01_Authentication: 01_Authentication.cpp
	$(CC) $(CFLAGS) 01_Authentication.cpp -o 01_Authentication.o -I ../include
	$(CC) 01_Authentication.o $(LIBRARIES) -o 01_Authentication $(LDFLAGS)

02_BrowseMods: 02_BrowseMods.cpp
	$(CC) $(CFLAGS) 02_BrowseMods.cpp -o 02_BrowseMods.o -I ../include
	$(CC) 02_BrowseMods.o $(LIBRARIES) -o 02_BrowseMods $(LDFLAGS)

03_ErrorResponse: 03_ErrorResponse.cpp
	$(CC) $(CFLAGS) 03_ErrorResponse.cpp -o 03_ErrorResponse.o -I ../include
	$(CC) 03_ErrorResponse.o $(LIBRARIES) -o 03_ErrorResponse $(LDFLAGS)

04_DownloadImages: 04_DownloadImages.cpp
	$(CC) $(CFLAGS) 04_DownloadImages.cpp -o 04_DownloadImages.o -I ../include
	$(CC) 04_DownloadImages.o $(LIBRARIES) -o 04_DownloadImages $(LDFLAGS)

05_EditImage: 05_EditImage.cpp
	$(CC) $(CFLAGS) 05_EditImage.cpp -o 05_EditImage.o -I ../include
	$(CC) 05_EditImage.o $(LIBRARIES) -o 05_EditImage $(LDFLAGS)

06_InstallModfile: 06_InstallModfile.cpp
	$(CC) $(CFLAGS) 06_InstallModfile.cpp -o 06_InstallModfile.o -I ../include
	$(CC) 06_InstallModfile.o $(LIBRARIES) -o 06_InstallModfile $(LDFLAGS)

07_AddModfile: 07_AddModfile.cpp
	$(CC) $(CFLAGS) 07_AddModfile.cpp -o 07_AddModfile.o -I ../include
	$(CC) 07_AddModfile.o $(LIBRARIES) -o 07_AddModfile $(LDFLAGS)

08_EditModfile: 08_EditModfile.cpp
	$(CC) $(CFLAGS) 08_EditModfile.cpp -o 08_EditModfile.o -I ../include
	$(CC) 08_EditModfile.o $(LIBRARIES) -o 08_EditModfile $(LDFLAGS)

09_AddMod: 09_AddMod.cpp
	$(CC) $(CFLAGS) 09_AddMod.cpp -o 09_AddMod.o -I ../include
	$(CC) 09_AddMod.o $(LIBRARIES) -o 09_AddMod $(LDFLAGS)

10_EditMod: 10_EditMod.cpp
	$(CC) $(CFLAGS) 10_EditMod.cpp -o 10_EditMod.o -I ../include
	$(CC) 10_EditMod.o $(LIBRARIES) -o 10_EditMod $(LDFLAGS)

11_DeleteMod: 11_DeleteMod.cpp
	$(CC) $(CFLAGS) 11_DeleteMod.cpp -o 11_DeleteMod.o -I ../include
	$(CC) 11_DeleteMod.o $(LIBRARIES) -o 11_DeleteMod $(LDFLAGS)

12_GetTags: 12_GetTags.cpp
	$(CC) $(CFLAGS) 12_GetTags.cpp -o 12_GetTags.o -I ../include
	$(CC) 12_GetTags.o $(LIBRARIES) -o 12_GetTags $(LDFLAGS)

13_AddTags: 13_AddTags.cpp
	$(CC) $(CFLAGS) 13_AddTags.cpp -o 13_AddTags.o -I ../include
	$(CC) 13_AddTags.o $(LIBRARIES) -o 13_AddTags $(LDFLAGS)


14_DeleteTags: 14_DeleteTags.cpp
	$(CC) $(CFLAGS) 14_DeleteTags.cpp -o 14_DeleteTags.o -I ../include
	$(CC) 14_DeleteTags.o $(LIBRARIES) -o 14_DeleteTags $(LDFLAGS)

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(EXAMPLES)

run:
	$ ./$(EXECUTABLE)
