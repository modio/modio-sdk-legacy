CC=g++
CFLAGS=-O3 -DNDEBUG -fPIC -std=gnu++11

#g++ -O3 -DNDEBUG -fPIC   -std=gnu++11 libtest.cpp -I ../studentlib_shared/include -L/home/turupawn/Projects/ModioDevel/build -rdynamic -lmodio -lcurl -lz -Wl,-rpath,/home/turupawn/Projects/ModioDevel/build -o olas

OBJECTS=$(SOURCES:.cpp=.o)
LDFLAGS=-L ../../build -lmodio -lcurl -lz -Wl,-rpath,../../build
INCLUDE=-I ../../include

EXAMPLES=01_Authentication 02_BrowseMods 03_ErrorResponse 04_DownloadImages 05_EditImage 06_DownloadModfile 07_UninstallModfile 08_AddModfile 09_EditModfile 10_AddMod 11_EditMod 12_DeleteMod 13_GetTags 14_AddTags 15_DeleteTags

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

07_UninstallModfile: 07_UninstallModfile.cpp
	$(CC) $(CFLAGS) 07_UninstallModfile.cpp $(INCLUDE) $(LDFLAGS) -o 07_UninstallModfile

08_AddModfile: 08_AddModfile.cpp
	$(CC) $(CFLAGS) 08_AddModfile.cpp $(INCLUDE) $(LDFLAGS) -o 08_AddModfile

09_EditModfile: 09_EditModfile.cpp
	$(CC) $(CFLAGS) 09_EditModfile.cpp $(INCLUDE) $(LDFLAGS) -o 09_EditModfile

10_AddMod: 10_AddMod.cpp
	$(CC) $(CFLAGS) 10_AddMod.cpp $(INCLUDE) $(LDFLAGS) -o 10_AddMod

11_EditMod: 11_EditMod.cpp
	$(CC) $(CFLAGS) 11_EditMod.cpp $(INCLUDE) $(LDFLAGS) -o 11_EditMod

12_DeleteMod: 12_DeleteMod.cpp
	$(CC) $(CFLAGS) 12_DeleteMod.cpp $(INCLUDE) $(LDFLAGS) -o 12_DeleteMod

13_GetTags: 13_GetTags.cpp
	$(CC) $(CFLAGS) 13_GetTags.cpp $(INCLUDE) $(LDFLAGS) -o 13_GetTags

14_AddTags: 14_AddTags.cpp
	$(CC) $(CFLAGS) 14_AddTags.cpp $(INCLUDE) $(LDFLAGS) -o 14_AddTags

15_DeleteTags: 15_DeleteTags.cpp
	$(CC) $(CFLAGS) 15_DeleteTags.cpp $(INCLUDE) $(LDFLAGS) -o 15_DeleteTags

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(EXAMPLES)

run:
	$ ./$(EXECUTABLE)
