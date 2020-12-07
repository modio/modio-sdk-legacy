cmake_minimum_required(VERSION 3.5)
project(modio)
set (CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Set this to ON if you want to enable testing
option(TEST "Enable UNIT TESTING" OFF)

# set BUILD_SHARED_LIBs to OFF to compile statically, for example:
# cmake -D BUILD_SHARED_LIBS=OFF .
option(BUILD_SHARED_LIBS "Build Shared Libraries" ON)

# set INCLUDE_EXAMPLES to ON to include the examples in the project
option(INCLUDE_EXAMPLES "Build examples" OFF)

# This needs to happen early, so that we force the build to be static
IF(TEST)
  message("Testing enabled, disabling shared libraries to be able to access internal functions")
  SET(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Shared Libraries" FORCE)
  # To be able to link with google test suite
  set(crtmode "static" CACHE STRING "" FORCE)
ENDIF()

# MSVC: set the crtmode flag to 'static' to include the Visual C++
# runtime statically. Requires libcurl to be built with /MT as well.
# cmake -D crtmode=static .

include_directories(include additional_dependencies include/dependencies/miniz include/dependencies/filesystem include/dependencies/utf8)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.c"
    "src/*.h"
    "include/*.h")

message(${CMAKE_SOURCE_DIR})

# Make pretty folders in visual studio/xcode
foreach(source IN LISTS SOURCES)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE ${CMAKE_SOURCE_DIR} "" source_path_folder ${source_path} )
    string(REPLACE "/" "\\" source_path_folder "${source_path_folder}")
    string(REPLACE ${CMAKE_SOURCE_DIR} "" source_path_folder ${source_path_folder} )
    source_group("${source_path_folder}" FILES "${source}")
endforeach()

add_library(modio ${SOURCES})

if( BUILD_SHARED_LIBS )
  message("Building mod.io SDK dynamically")
  add_definitions(-DMODIO_DYNAMICLIB -DCURL_STATICLIB)
else()
  message("Building mod.io SDK statically")
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  add_definitions(-DMODIO_STATICLIB -DCURL_STATICLIB)
endif()

IF (APPLE)
  find_package(CURL REQUIRED)
  target_link_libraries(modio ${CURL_LIBRARIES})
ENDIF()

IF (UNIX AND NOT APPLE)
  add_definitions(-D_LARGEFILE64_SOURCE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  target_link_libraries (modio curl)
ENDIF ()

IF (MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE)
  target_link_libraries(modio ws2_32.lib wldap32.lib advapi32.lib kernel32.lib comdlg32.lib crypt32.lib normaliz.lib )

  IF (crtmode AND crtmode STREQUAL "static")
    set(CompilerFlags
      CMAKE_CXX_FLAGS
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_RELEASE
      CMAKE_C_FLAGS
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_RELEASE
    )

    foreach(CompilerFlag ${CompilerFlags})
      string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      target_link_libraries(modio ${CMAKE_CURRENT_SOURCE_DIR}/lib/MSVC/x64/static/libcurl_a.lib)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
      target_link_libraries(modio ${CMAKE_CURRENT_SOURCE_DIR}/lib/MSVC/x86/static/libcurl_a.lib)
    endif()

  ELSE()

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      target_link_libraries(modio ${CMAKE_CURRENT_SOURCE_DIR}/lib/MSVC/x64/libcurl_a.lib)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
      target_link_libraries(modio ${CMAKE_CURRENT_SOURCE_DIR}/lib/MSVC/x86/libcurl_a.lib)
    endif()

  ENDIF()

ENDIF()

IF(TEST)
  file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
  # This is needed to get release compiling
  SET(gtest_force_shared_crt ON)
  add_subdirectory(ext/googletest-master)
  enable_testing()
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
  add_executable(runUnitTests ${TEST_SRC_FILES})
  target_link_libraries(runUnitTests gtest gtest_main modio)
  add_test(UnitTests runUnitTests)
ENDIF()


if( INCLUDE_EXAMPLES )
  set(CPP_EXAMPLE_DIR "examples/code-samples/cpp")
  set(C_EXAMPLE_DIR "examples/code-samples/c")
  add_subdirectory(${CPP_EXAMPLE_DIR})
  add_subdirectory(${C_EXAMPLE_DIR})
  add_custom_command(TARGET modio POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:modio> "${CMAKE_CURRENT_BINARY_DIR}/${CPP_EXAMPLE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:modio> "${CMAKE_CURRENT_BINARY_DIR}/${C_EXAMPLE_DIR}"
    COMMENT "Copying library binaries into examples dir..."
    )

  # Copy pdb's on platforms that support it
  IF (MSVC)
    IF(BUILD_SHARED_LIBS)
        add_custom_command(TARGET modio POST_BUILD 
          COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_PDB_FILE:modio> "${CMAKE_CURRENT_BINARY_DIR}/${CPP_EXAMPLE_DIR}"
          COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_PDB_FILE:modio> "${CMAKE_CURRENT_BINARY_DIR}/${C_EXAMPLE_DIR}"
          COMMENT "Copying library pdbs into examples dir..."
          )
    ENDIF()
  ENDIF()
endif()

if(BUILD_SHARED_LIBS)
    set(PREFIX ${CMAKE_SHARED_MODULE_PREFIX})
    set(POSTFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
else()
    set(PREFIX ${CMAKE_STATIC_LIBRARY_PREFIX})
    set(POSTFIX ${CMAKE_STATIC_LIBRARY_SUFFIX})
endif()

# Set properties let projects that use this project as a subdirectory know how to play along with it
set_target_properties(modio
    PROPERTIES
    PREFIX "${PREFIX}"
    OUTPUT_NAME modio
    SUFFIX "${POSTFIX}")