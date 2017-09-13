MODWORKS_WRAPPERS=CurlWrapper.cpp MinizipWrapper.cpp
MODWORKS_DEPENDENCIES=minizip/zip.cpp minizip/unzip.cpp minizip/ioapi.cpp minizip/minizip.cpp minizip/crypt.cpp
MODWORKS_SOURCES=Globals.cpp ModworksSDK.cpp Authentication.cpp Utility.cpp Mod.cpp $(MODWORKS_WRAPPERS) $(MODWORKS_DEPENDENCIES)
