CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project (ScarryGam)

add_subdirectory(tank)
include_directories(${TANK_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-mismatched-tags")
endif()

add_subdirectory(src)
file(COPY "res" DESTINATION ${CMAKE_BINARY_DIR})
