project (cmg_test)

#file(GLOB cmg_testfiles "*.cpp" "**/*.cpp" "../src/*.cpp" "../src/**/*.cpp")
set(cmg_testfiles test-main.cpp test-MoveGenValidator.cpp test-Move.cpp)
add_executable(cmg_test ${cmg_testfiles})

target_link_libraries(cmg_test)