CC=g++
CFLAGS=-Wall -std=c++11
INCLUDE_PATH = ../../../include
LIB_PATH = ../../../build

all: main.cpp
	$(CC) $(CFLAGS) main.cpp -o MyProject -I $(INCLUDE_PATH) -L $(LIB_PATH) -lmodio -Wl,-rpath .

# In order to link statically, add the following curl and zlib link flags: -lcurl -lz