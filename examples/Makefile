CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lcurl -pthread -lz
SOURCES=Example.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Example
LIBRARIES=../src/modio.so
EXAMPLES=1_Authentication 2_BrowseMods 3_ErrorResponse 4_HandleImages 5_HandleModfiles 6_CreateMod 7_EditMod 8_DeleteMod 9_HandleTags 10_SetUserRating 11_ModSubscription

all: $(EXAMPLES)

1_Authentication: 1_Authentication.cpp
	$(CC) $(CFLAGS) 1_Authentication.cpp -o 1_Authentication.o -I ../include
	$(CC) 1_Authentication.o $(LIBRARIES) -o 1_Authentication $(LDFLAGS)

2_BrowseMods: 2_BrowseMods.cpp
	$(CC) $(CFLAGS) 2_BrowseMods.cpp -o 2_BrowseMods.o -I ../include
	$(CC) 2_BrowseMods.o $(LIBRARIES) -o 2_BrowseMods $(LDFLAGS)

3_ErrorResponse: 3_ErrorResponse.cpp
	$(CC) $(CFLAGS) 3_ErrorResponse.cpp -o 3_ErrorResponse.o -I ../include
	$(CC) 3_ErrorResponse.o $(LIBRARIES) -o 3_ErrorResponse $(LDFLAGS)

4_HandleImages: 4_HandleImages.cpp
	$(CC) $(CFLAGS) 4_HandleImages.cpp -o 4_HandleImages.o -I ../include
	$(CC) 4_HandleImages.o $(LIBRARIES) -o 4_HandleImages $(LDFLAGS)

5_HandleModfiles: 5_HandleModfiles.cpp
	$(CC) $(CFLAGS) 5_HandleModfiles.cpp -o 5_HandleModfiles.o -I ../include
	$(CC) 5_HandleModfiles.o $(LIBRARIES) -o 5_HandleModfiles $(LDFLAGS)

6_CreateMod: 6_CreateMod.cpp
	$(CC) $(CFLAGS) 6_CreateMod.cpp -o 6_CreateMod.o -I ../include
	$(CC) 6_CreateMod.o $(LIBRARIES) -o 6_CreateMod $(LDFLAGS)

7_EditMod: 7_EditMod.cpp
	$(CC) $(CFLAGS) 7_EditMod.cpp -o 7_EditMod.o -I ../include
	$(CC) 7_EditMod.o $(LIBRARIES) -o 7_EditMod $(LDFLAGS)

8_DeleteMod: 8_DeleteMod.cpp
	$(CC) $(CFLAGS) 8_DeleteMod.cpp -o 8_DeleteMod.o -I ../include
	$(CC) 8_DeleteMod.o $(LIBRARIES) -o 8_DeleteMod $(LDFLAGS)

9_HandleTags: 9_HandleTags.cpp
	$(CC) $(CFLAGS) 9_HandleTags.cpp -o 9_HandleTags.o -I ../include
	$(CC) 9_HandleTags.o $(LIBRARIES) -o 9_HandleTags $(LDFLAGS)

10_SetUserRating: 10_SetUserRating.cpp
	$(CC) $(CFLAGS) 10_SetUserRating.cpp -o 10_SetUserRating.o -I ../include
	$(CC) 10_SetUserRating.o $(LIBRARIES) -o 10_SetUserRating $(LDFLAGS)

11_ModSubscription: 11_ModSubscription.cpp
	$(CC) $(CFLAGS) 11_ModSubscription.cpp -o 11_ModSubscription.o -I ../include
	$(CC) 11_ModSubscription.o $(LIBRARIES) -o 11_ModSubscription $(LDFLAGS)

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(EXAMPLES)

run:
	$ ./$(EXECUTABLE)
