cmake_minimum_required(VERSION 3.16)

file(GLOB CUR_SRC "*.c" "*.cpp" "*.h" "*.hpp")
add_executable(QueueCreateAndRun ${CUR_SRC})
target_link_libraries(QueueCreateAndRun obj_kernel)
# End of cmake-file.