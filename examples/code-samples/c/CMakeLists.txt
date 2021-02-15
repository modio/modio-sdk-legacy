cmake_minimum_required(VERSION 3.5)
project(examples)
include_directories(../../../include)
link_directories(../../../build)
enable_language(C)
enable_language(CXX)

file( GLOB EXAMPLE_SOURCES *.c )

foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
  file(RELATIVE_PATH SOURCE_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR} ${EXAMPLE_SOURCE} )
  # Setting to compile absolute path, so that we ensure that __FILE__ gives a proper full path in macros
  get_filename_component(EXAMPLE_SOURCES_ABSOLUTE_PATH ${EXAMPLE_SOURCE} ABSOLUTE)
  string( REPLACE ".c" "" EXECUTABLE_NAME "c_${SOURCE_FILE_NAME}" )
  add_executable(${EXECUTABLE_NAME} ${EXAMPLE_SOURCES_ABSOLUTE_PATH})

  IF (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  ENDIF()
  target_link_libraries( ${EXECUTABLE_NAME} PRIVATE modio )
  set_property(TARGET ${EXECUTABLE_NAME} PROPERTY C_STANDARD 99)

endforeach(EXAMPLE_SOURCE)
