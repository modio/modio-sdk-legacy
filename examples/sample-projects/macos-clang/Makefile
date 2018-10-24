CC=clang++
CFLAGS=-Wall -std=c++11

MODIO_INCLUDE_DIR = ../../../include
MODIO_LIB_DIR = ../../../build

all: main.cpp
	$(CC) $(CFLAGS) main.cpp -o MyProject -I $(MODIO_INCLUDE_DIR) -L $(MODIO_LIB_DIR) -lmodio -Wl,-rpath $(MODIO_LIB_DIR)

# In order to link statically, add the following curl and zlib link flags: -lcurl -lz
