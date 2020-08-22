cmake_minimum_required(VERSION 3.16)

file(GLOB CUR_SRC "*.c" "*.cpp" "*.h" "*.hpp")
add_executable(TaskCreationAndRun ${CUR_SRC})
target_link_libraries(TaskCreationAndRun obj_thread mem_manger)
# End of cmake-file.