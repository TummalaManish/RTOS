cmake_minimum_required(VERSION 3.16)

file(GLOB CUR_SRC "*.c" "*.cpp" "*.h" "*.hpp")
add_executable(ThreadCreationAndRun ${CUR_SRC})
target_link_libraries(ThreadCreationAndRun obj_thread mem_manger)
# End of cmake-file.