cmake_minimum_required(VERSION 3.5)
project(modio)
set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 11)

# set the link flag as static to compile statically, for example:
# cmake -D link=static .

include_directories(include additional_dependencies)

file(GLOB_RECURSE SOURCES "src/*.cpp")

if( link AND link STREQUAL "static" )
  message("Building mod.io SDK statically")
  add_definitions(-DMODIO_STATICLIB -DCURL_STATICLIB)
  add_library(modio STATIC ${SOURCES})
else()
  message("Building mod.io SDK dynamically")
  add_definitions(-DMODIO_DYNAMICLIB -DCURL_STATICLIB)
  add_library(modio SHARED ${SOURCES})
endif()

IF (APPLE)
  find_package(ZLIB REQUIRED)
  find_package(CURL REQUIRED)
  target_link_libraries(modio ${CURL_LIBRARIES} ZLIB::ZLIB)
ENDIF()

IF (UNIX AND NOT APPLE)
  target_link_libraries (modio curl z)
ENDIF ()

IF (MINGW)
  target_link_libraries(modio
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libcurl.a
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libz.a
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libcrypto.dll.a
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libeay32.dll
    ${CMAKE_SOURCE_DIR}/lib/MinGW/libssl.dll.a
    wldap32 ws2_32)
ENDIF()

IF (MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_link_libraries(modio ws2_32.lib wldap32.lib advapi32.lib kernel32.lib comdlg32.lib crypt32.lib normaliz.lib ${CMAKE_SOURCE_DIR}/lib/MSVC/x64/libcurl_a.lib  ${CMAKE_SOURCE_DIR}/lib/MSVC/x64/zlib.lib )
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    target_link_libraries(modio ws2_32.lib wldap32.lib advapi32.lib kernel32.lib comdlg32.lib crypt32.lib normaliz.lib ${CMAKE_SOURCE_DIR}/lib/MSVC/x86/libcurl_a.lib  ${CMAKE_SOURCE_DIR}/lib/MSVC/x86/zlib.lib )
  endif()
ENDIF()
