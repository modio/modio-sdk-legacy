MODWORKS_WRAPPERS=CurlWrapper.cpp MinizipWrapper.cpp
MODWORKS_DEPENDENCIES=minizip/zip.cpp minizip/unzip.cpp minizip/ioapi.cpp minizip/minizip.cpp minizip/crypt.cpp
MODWORKS_DATA_CONTAINERS=DataContainers/Image.cpp DataContainers/Media.cpp DataContainers/Mod.cpp DataContainers/Modfile.cpp DataContainers/Ratings.cpp DataContainers/Tag.cpp
MODWORKS_SOURCES=ModworksSDK.cpp Globals.cpp Filter.cpp ModMethods.cpp AuthenticationMethods.cpp Utility.cpp $(MODWORKS_WRAPPERS) $(MODWORKS_DEPENDENCIES) $(MODWORKS_DATA_CONTAINERS)
