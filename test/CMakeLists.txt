project (movegencpp_test)

#file(GLOB cmg_testfiles "*.cpp" "**/*.cpp" "../src/*.cpp" "../src/**/*.cpp")
set(movegencpp_testfiles test-main.cpp test-MoveGen.cpp test-Move.cpp)
add_executable(movegencpp_test ${movegencpp_testfiles})
target_compile_definitions(movegencpp_test PUBLIC MOVEGENCPP_UNITTEST)

target_link_libraries(movegencpp_test)