MODIO_WRAPPERS=wrappers/CurlWrapper.cpp wrappers/MinizipWrapper.cpp
MODIO_DEPENDENCIES=dependencies/minizip/zip.cpp dependencies/minizip/unzip.cpp dependencies/minizip/ioapi.cpp dependencies/minizip/minizip.cpp dependencies/minizip/crypt.cpp
MODIO_DATA_CONTAINERS=data_containers/Image.cpp data_containers/User.cpp data_containers/Media.cpp data_containers/Mod.cpp data_containers/Modfile.cpp data_containers/Ratings.cpp data_containers/Tag.cpp data_containers/Error.cpp data_containers/Response.cpp
MODIO_METHODS=exported_methods/ModMethods.cpp exported_methods/ModfileMethods.cpp exported_methods/AuthenticationMethods.cpp exported_methods/TagMethods.cpp exported_methods/ImageMethods.cpp
MODIO_INSTANCE_METHODS=instance_methods/FilterInstanceMethods.cpp instance_methods/AuthenticationInstanceMethods.cpp instance_methods/ImageInstanceMethods.cpp instance_methods/ModInstanceMethods.cpp instance_methods/ModfileInstanceMethods.cpp instance_methods/TagsInstanceMethods.cpp
MODIO_HANDLER_INSTANCE=handlers_instance/ModfileHandlerInstance.cpp handlers_instance/ModHandlerInstance.cpp
MODIO_SOURCES=ModIOSDK.cpp ModIOInstance.cpp Globals.cpp Filter.cpp handlers/ModHandler.cpp handlers/ModfileHandler.cpp Utility.cpp $(MODIO_WRAPPERS) $(MODIO_DEPENDENCIES) $(MODIO_DATA_CONTAINERS) $(MODIO_METHODS) $(MODIO_INSTANCE_METHODS) $(MODIO_HANDLER_INSTANCE)
