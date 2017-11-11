include_directories(src) # source files

# Externals
if ("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}/engine")
    #include_directories(${UCI_BENCHMARK_INCLUDE_DIR})
    include_directories(${cmg_CATCH_INCLUDE_DIR})

    #add_subdirectory(benchmarks)  # Benchmarks
    add_subdirectory(test)         # Unit tests
endif()