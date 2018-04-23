CC=clang++
CFLAGS=-Wall -std=c++11

MODIO_INCLUDE_DIR = ../../include
MODIO_LIB_DIR = ../../build

all: main.cpp
	$(CC) $(CFLAGS) main.cpp -o MyProject -I $(MODIO_INCLUDE_DIR) $(MODIO_LIB_DIR)/libmodio.dylib -Wl,-rpath $(MODIO_LIB_DIR)
