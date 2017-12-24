cmake_minimum_required(VERSION 2.8.9)
project(modio)
set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 11)

set ( PROJECT_LINK_LIBS libcurl.a libcurldll.a zlib.lib zdll.lib )

link_directories( lib/ )

include_directories(include)
 
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(modio SHARED ${SOURCES})

target_link_libraries(modio ${PROJECT_LINK_LIBS} )
