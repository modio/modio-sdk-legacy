cmake_minimum_required(VERSION 3.5)
project(modio)
set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 11)

IF (MINGW)
  add_definitions(-DBUILDING_MODIO_DLL -DMINGW)
ENDIF()

IF (MSVC)
  add_definitions(-DBUILDING_MODIO_DLL)
ENDIF()

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(modio SHARED ${SOURCES})

IF (MINGW)
  target_link_libraries(modio ${CMAKE_SOURCE_DIR}/lib/libcurl.a ${CMAKE_SOURCE_DIR}/lib/libcurldll.a   ${CMAKE_SOURCE_DIR}/lib/libz.a )
ENDIF()

IF (MSVC)
  target_link_libraries(modio ${CMAKE_SOURCE_DIR}/lib/libcurl.a ${CMAKE_SOURCE_DIR}/lib/libcurldll.a  ${CMAKE_SOURCE_DIR}/lib/zlib.lib )
ENDIF()
