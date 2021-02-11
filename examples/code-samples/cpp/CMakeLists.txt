cmake_minimum_required(VERSION 3.5)
project(examples)
include_directories(../../../include)
include_directories(../../../additional_dependencies)
set (CMAKE_CXX_STANDARD 11)
link_directories(../../../build)

file( GLOB EXAMPLE_SOURCES *.cpp )

set(STEAMWORKS_SDK_PATH "" CACHE PATH "Path the the Steamworks SDK for the Steamworks example")
set(STEAMWORKS_APP_ID "" CACHE STRING "A appid that will be used during the execution of your game")

if(EXISTS ${STEAMWORKS_SDK_PATH})
    add_custom_target(copy-steam-dll ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/steam_api64.dll")
endif()

foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
  file(RELATIVE_PATH SOURCE_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR} ${EXAMPLE_SOURCE} )
  string( REPLACE ".cpp" "" EXECUTABLE_NAME "cpp_${SOURCE_FILE_NAME}" )
  add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE_NAME})

  IF (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(STEAM_SUBFOLDER "win64")
    set(STEAM_LIB_NAME "steam_api64")
  ENDIF ()
  IF (APPLE)
    set(STEAM_SUBFOLDER "osx")
    set(STEAM_LIB_NAME "libsteam_api")
  ENDIF ()
  IF (UNIX AND NOT APPLE)
    set(STEAM_SUBFOLDER "linux64")
    set(STEAM_LIB_NAME "libsteam_api")
  ENDIF ()
  target_link_libraries( ${EXECUTABLE_NAME} PRIVATE modio )

  string(TOLOWER ${EXECUTABLE_NAME} EXECUTABLE_NAME_LOWER_CASE)
  string(FIND ${EXECUTABLE_NAME_LOWER_CASE} steam IS_STEAM_EXAMPLE)
  if(EXISTS ${STEAMWORKS_SDK_PATH} AND NOT IS_STEAM_EXAMPLE EQUAL -1)
    target_include_directories(${EXECUTABLE_NAME} PRIVATE "${STEAMWORKS_SDK_PATH}/public/steam")
    target_link_directories(${EXECUTABLE_NAME} PRIVATE "${STEAMWORKS_SDK_PATH}/redistributable_bin/${STEAM_SUBFOLDER}")
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE "${STEAM_LIB_NAME}")
    target_compile_definitions(${EXECUTABLE_NAME} PRIVATE "-DSTEAM_APP_ID=${STEAMWORKS_APP_ID}")

    add_custom_command ( TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${STEAMWORKS_SDK_PATH}/redistributable_bin/${STEAM_SUBFOLDER}/steam_api64.dll" $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
)
   endif()

endforeach(EXAMPLE_SOURCE)
