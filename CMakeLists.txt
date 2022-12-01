cmake_minimum_required(VERSION 3.0.2)

##project
project(openfec C)
include(GNUInstallDirs)

file(READ ${PROJECT_SOURCE_DIR}/.version VERSION_TAG)
string(REGEX REPLACE "\n$" "" VERSION_TAG "${VERSION_TAG}")
message(STATUS "Project version: ${VERSION_TAG}")

set(PROJECT_VERSION "${VERSION_TAG}")
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
set(OPTIMIZE "3" CACHE STRING "Set optimization level (0-3 or DEFAULT)")
if (NOT OPTIMIZE STREQUAL "DEFAULT")
  string(REGEX REPLACE "(-O[A-Za-z0-9]+)" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE "(-O[A-Za-z0-9]+)" "" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O${OPTIMIZE}")
endif()
message(STATUS "Debug mode OFF")
message(STATUS "Optimization level ${OPTIMIZE}")

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
