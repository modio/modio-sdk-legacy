cmake_minimum_required(VERSION 2.8.9)
project(modio)
set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 11)

IF (WIN32)
  add_definitions(-DBUILDING_MODIO_DLL -DMINGW -DWINDOWS)
ENDIF()

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(modio SHARED ${SOURCES})

#IF (WIN32)
#  target_link_libraries(modio ${CMAKE_SOURCE_DIR}/lib/libcurl.a ${CMAKE_SOURCE_DIR}/lib/libcurldll.a  ${CMAKE_SOURCE_DIR}/lib/zlib.lib  ${CMAKE_SOURCE_DIR}/lib/zdll.lib )
#ENDIF()

IF (WIN32)
  target_link_libraries(modio ${CMAKE_SOURCE_DIR}/lib/libcurl.a ${CMAKE_SOURCE_DIR}/lib/libcurldll.a   ${CMAKE_SOURCE_DIR}/lib/libz.a )
ENDIF()
