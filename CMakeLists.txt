cmake_minimum_required(VERSION 3.9)
project(movegencpp VERSION 0.0.1 DESCRIPTION "Chess Move Generator written in C++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/builds")

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -fPIC")

# In case neither release nor debug is set as build type, default to release.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Wno-unused-variable -O3 -flto -DNDEBUG")

# Header files
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Third party libraries in lib
# These are ignored if this is used as a dep / sub module
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    # External project file headers
    include_directories(dep/Catch2)

    # also run the tests
    add_subdirectory(test)

    # and benchmarks
    add_subdirectory(benchmark)
endif()
