CC=g++
CFLAGS=-O3 -DNDEBUG -fPIC -std=gnu++11

#g++ -O3 -DNDEBUG -fPIC   -std=gnu++11 libtest.cpp -I ../studentlib_shared/include -L/home/turupawn/Projects/ModioDevel/build -rdynamic -lmodio -lcurl -lz -Wl,-rpath,/home/turupawn/Projects/ModioDevel/build -o olas

OBJECTS=$(SOURCES:.cpp=.o)
LDFLAGS=-L ../../build -lmodio -lcurl -lz -Wl,-rpath,../../build
INCLUDE=-I ../../include

EXAMPLES=01_Authentication 02_BrowseMods 03_ErrorResponse 04_DownloadImages 05_EditImage 06_DownloadModfile 07_AddModfile 08_EditModfile 09_AddMod 10_EditMod 11_DeleteMod 12_GetTags 13_AddTags 14_DeleteTags

all: $(EXAMPLES)

01_Authentication: 01_Authentication.cpp
	$(CC) $(CFLAGS) 01_Authentication.cpp $(INCLUDE) $(LDFLAGS) -o 01_Authentication

02_BrowseMods: 02_BrowseMods.cpp
	$(CC) $(CFLAGS) 02_BrowseMods.cpp $(INCLUDE) $(LDFLAGS) -o 02_BrowseMods

03_ErrorResponse: 03_ErrorResponse.cpp
	$(CC) $(CFLAGS) 03_ErrorResponse.cpp $(INCLUDE) $(LDFLAGS) -o 03_ErrorResponse

04_DownloadImages: 04_DownloadImages.cpp
	$(CC) $(CFLAGS) 04_DownloadImages.cpp $(INCLUDE) $(LDFLAGS) -o 04_DownloadImages

05_EditImage: 05_EditImage.cpp
	$(CC) $(CFLAGS) 05_EditImage.cpp $(INCLUDE) $(LDFLAGS) -o 05_EditImage

06_DownloadModfile: 06_DownloadModfile.cpp
	$(CC) $(CFLAGS) 06_DownloadModfile.cpp $(INCLUDE) $(LDFLAGS) -o 06_DownloadModfile

07_AddModfile: 07_AddModfile.cpp
	$(CC) $(CFLAGS) 07_AddModfile.cpp $(INCLUDE) $(LDFLAGS) -o 07_AddModfile

08_EditModfile: 08_EditModfile.cpp
	$(CC) $(CFLAGS) 08_EditModfile.cpp $(INCLUDE) $(LDFLAGS) -o 08_EditModfile

09_AddMod: 09_AddMod.cpp
	$(CC) $(CFLAGS) 09_AddMod.cpp $(INCLUDE) $(LDFLAGS) -o 09_AddMod

10_EditMod: 10_EditMod.cpp
	$(CC) $(CFLAGS) 10_EditMod.cpp $(INCLUDE) $(LDFLAGS) -o 10_EditMod

11_DeleteMod: 11_DeleteMod.cpp
	$(CC) $(CFLAGS) 11_DeleteMod.cpp $(INCLUDE) $(LDFLAGS) -o 11_DeleteMod

12_GetTags: 12_GetTags.cpp
	$(CC) $(CFLAGS) 12_GetTags.cpp $(INCLUDE) $(LDFLAGS) -o 12_GetTags

13_AddTags: 13_AddTags.cpp
	$(CC) $(CFLAGS) 13_AddTags.cpp $(INCLUDE) $(LDFLAGS) -o 13_AddTags

14_DeleteTags: 14_DeleteTags.cpp
	$(CC) $(CFLAGS) 14_DeleteTags.cpp $(INCLUDE) $(LDFLAGS) -o 14_DeleteTags

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(EXAMPLES)

run:
	$ ./$(EXECUTABLE)
