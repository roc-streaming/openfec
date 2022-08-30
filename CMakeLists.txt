cmake_minimum_required(VERSION 3.0.2)

##project
project(openfec C)
include(GNUInstallDirs)

execute_process(
  OUTPUT_VARIABLE GIT_TAG
  OUTPUT_STRIP_TRAILING_WHITESPACE
  COMMAND git describe --tags --abbrev=0
  )
string(REGEX MATCH "v?([0-9.]+)" RESULT ${GIT_TAG})
set(GIT_TAG "${CMAKE_MATCH_1}")

message(STATUS "Detected version from git: ${GIT_TAG}")

set(PROJECT_VERSION "${GIT_TAG}")
set(PROJECT_DESCRIPTION "Application-Level Forward Erasure Correction implementation library")

ENABLE_TESTING()

if (PROFILING STREQUAL "ON")

else(PROFILING STREQUAL "ON")

endif(PROFILING STREQUAL "ON")

if (DEBUG STREQUAL "ON")
# Debug mode
ADD_DEFINITIONS(-DOF_DEBUG)
set(CMAKE_BUILD_TYPE Debug)
message(STATUS "Debug mode ON" )

else(DEBUG STREQUAL "ON")
# Release mode
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "-O4")
message(STATUS "Debug mode OFF")

endif (DEBUG STREQUAL "ON")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
MARK_AS_ADVANCED(
        LIBRARY_OUTPUT_PATH
        EXECUTABLE_OUTPUT_PATH
)

link_directories(${LIBRARY_OUTPUT_PATH})

add_subdirectory(pc)
add_subdirectory(src)
add_subdirectory(applis/eperftool)
add_subdirectory(applis/howto_examples/simple_client_server)
add_subdirectory(tools/descr_stats_v1.2)
add_subdirectory(tests)
