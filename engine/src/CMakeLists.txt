set(cmg_files MoveGen.cpp)


# add_executable(${PROJECT_NAME} ${cmg_files})
add_library(${PROJECT_NAME} SHARED ${cmg_files})
target_link_libraries(${PROJECT_NAME})