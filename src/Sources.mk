MODIO_WRAPPERS=wrappers/CurlWrapper.cpp wrappers/MinizipWrapper.cpp
MODIO_DEPENDENCIES=dependencies/minizip/zip.cpp dependencies/minizip/unzip.cpp dependencies/minizip/ioapi.cpp dependencies/minizip/minizip.cpp dependencies/minizip/crypt.cpp
MODIO_DATA_CONTAINERS=data_containers/Image.cpp data_containers/Member.cpp data_containers/Media.cpp data_containers/Mod.cpp data_containers/Modfile.cpp data_containers/Ratings.cpp data_containers/Tag.cpp
MODIO_SOURCES=ModIOSDK.cpp Globals.cpp Filter.cpp handlers/ModHandler.cpp handlers/ModfileHandler.cpp ModMethods.cpp ModfileMethods.cpp AuthenticationMethods.cpp Utility.cpp $(MODIO_WRAPPERS) $(MODIO_DEPENDENCIES) $(MODIO_DATA_CONTAINERS)
