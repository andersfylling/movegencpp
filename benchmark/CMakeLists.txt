project (movegencpp_benchmark)

#file(GLOB cmg_testfiles "*.cpp" "**/*.cpp" "../src/*.cpp" "../src/**/*.cpp")
set(movegencpp_benchmarkfiles main.cpp knight.cpp random.cpp)
add_executable(movegencpp_benchmark ${movegencpp_benchmarkfiles})
target_compile_definitions(movegencpp_benchmark PUBLIC MOVEGENCPP_BENCHMARK)

target_link_libraries(movegencpp_benchmark -lbenchmark)