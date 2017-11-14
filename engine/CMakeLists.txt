add_subdirectory(src) # source files

# Externals
if ("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}/engine")
    #add_subdirectory(benchmarks)  # Benchmarks
    add_subdirectory(test)         # Unit tests
endif()