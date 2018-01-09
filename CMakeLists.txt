cmake_minimum_required(VERSION 3.5)
project(modio)
set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 11)

add_definitions(-DBUILDING_MODIO_DLL -DCURL_STATICLIB)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(modio SHARED ${SOURCES})

IF (APPLE)
  find_package(ZLIB REQUIRED)
  find_package(CURL REQUIRED)
  target_link_libraries(modio ${CURL_LIBRARIES} ZLIB::ZLIB)
ENDIF()

IF (MINGW)
  target_link_libraries(modio ${CMAKE_SOURCE_DIR}/lib/MinGW/libcurl.a ${CMAKE_SOURCE_DIR}/lib/MinGW/libz.a wldap32 ws2_32 ssl eay32 crypto)
ENDIF()

IF (MSVC)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_link_libraries(modio ${CMAKE_SOURCE_DIR}/lib/MSVC/x64/libcurl_a.lib  ${CMAKE_SOURCE_DIR}/lib/MSVC/x64/zlib.lib )
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    target_link_libraries(modio ${CMAKE_SOURCE_DIR}/lib/MSVC/x86/libcurl_a.lib  ${CMAKE_SOURCE_DIR}/lib/MSVC/x86/zlib.lib )
  endif()
ENDIF()
