CC = cl.exe
CFLAGS = /EHsc /MD
MODIO_LIB_DIR = ../../../build
MODIO_INCLUDE_DIR = ../../../include
ADDITIONAL_INCLUDE_DIR = ../../../additional_dependencies

# Static library setup
# In order to compile with the static version of mod.io add the $(STATIC_LIB_CONFIG) flag to your build
SHIPPED_CURL_LIB = ../../../lib/MSVC/x86/libcurl_a.lib
SHIPPED_ZLIB_LIB = ../../../lib/MSVC/x86/zlib.lib
CURL_DEPENDENCIES = ws2_32.lib wldap32.lib advapi32.lib kernel32.lib comdlg32.lib crypt32.lib normaliz.lib
STATIC_LIB_CONFIG = /D MODIO_STATICLIB $(SHIPPED_CURL_LIB) $(SHIPPED_ZLIB_LIB) $(CURL_DEPENDENCIES)

build:
	$(CC) $(CFLAGS) main.cpp $(MODIO_LIB_DIR)/modio.lib /I $(MODIO_INCLUDE_DIR) /I $(ADDITIONAL_INCLUDE_DIR)
