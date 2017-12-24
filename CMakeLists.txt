cmake_minimum_required(VERSION 2.8.9)
project(modio)
set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 11)

#Bring the headers, such as Student.h into the project
include_directories(include)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE SOURCES "src/*.cpp")
 
#Generate the shared library from the sources
add_library(modio SHARED ${SOURCES})
 
#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
#install(TARGETS testStudent DESTINATION /usr/lib)
