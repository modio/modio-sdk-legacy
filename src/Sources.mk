MODWORKS_WRAPPERS=wrappers/CurlWrapper.cpp wrappers/MinizipWrapper.cpp
MODWORKS_DEPENDENCIES=dependencies/minizip/zip.cpp dependencies/minizip/unzip.cpp dependencies/minizip/ioapi.cpp dependencies/minizip/minizip.cpp dependencies/minizip/crypt.cpp
MODWORKS_DATA_CONTAINERS=data_containers/Image.cpp data_containers/Member.cpp data_containers/Media.cpp data_containers/Mod.cpp data_containers/Modfile.cpp data_containers/Ratings.cpp data_containers/Tag.cpp
MODWORKS_SOURCES=ModworksSDK.cpp Globals.cpp Filter.cpp handlers/ModHandler.cpp handlers/ModfileHandler.cpp ModMethods.cpp AuthenticationMethods.cpp Utility.cpp $(MODWORKS_WRAPPERS) $(MODWORKS_DEPENDENCIES) $(MODWORKS_DATA_CONTAINERS)
