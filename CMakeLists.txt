cmake_minimum_required(VERSION 3.9)
project(cmg VERSION 0.0.1 DESCRIPTION "Chess Move Generator written in C++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -fPIC")

# In case neither release nor debug is set as build type, default to release.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Wno-unused-variable -O3 -flto -DNDEBUG")

# Third party libraries in lib
# These are ignored if this is used as a external / sub module
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    # External project file headers
    # set(cmg_BENCHMARK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/benchmark/include")
    set(cmg_CATCH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/Catch2/include")

    add_subdirectory(external)
endif()


# Header files
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Our source code
add_subdirectory(engine)

# Library files to compile
#add_library(cmg SHARED
#        src/library.cpp
#        )

#set_target_properties(cmg PROPERTIES VERSION ${PROJECT_VERSION})

#configure_file(cmg.pc.in cmg.pc @ONLY)
#target_include_directories(cmg PRIVATE include)
#target_include_directories(cmg PRIVATE src)

#include(GNUInstallDirs)

#install(TARGETS cmg
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#install(FILES ${CMAKE_BINARY_DIR}/cmg.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)