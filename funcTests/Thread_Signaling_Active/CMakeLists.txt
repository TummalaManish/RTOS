cmake_minimum_required(VERSION 3.16)

file(GLOB CUR_SRC "*.c" "*.cpp" "*.h" "*.hpp")
add_executable(ThreadSignaling ${CUR_SRC})
target_link_libraries(ThreadSignaling obj_kernel)
# End of cmake-file.