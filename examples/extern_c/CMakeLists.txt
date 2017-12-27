cmake_minimum_required(VERSION 3.1)
include_directories(../../include)
link_directories(../../build)

file( GLOB EXAMPLE_SOURCES *.c )

foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
  file(RELATIVE_PATH SOURCE_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR} ${EXAMPLE_SOURCE} )
  string( REPLACE ".c" "" EXECUTABLE_NAME ${SOURCE_FILE_NAME} )
  add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE_NAME})
  target_link_libraries( ${EXECUTABLE_NAME} modio curl z )
  set_property(TARGET ${EXECUTABLE_NAME} PROPERTY C_STANDARD 99)
endforeach(EXAMPLE_SOURCE)
