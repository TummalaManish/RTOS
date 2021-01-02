cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# The c-kernel is not distinguishable from the port to a simulator.

file(GLOB_RECURSE SRC_FILES "*.cpp" "*.hpp")

add_library(obj_kernel ${SRC_FILES})
target_include_directories(obj_kernel PUBLIC include interface)
target_link_libraries(obj_kernel kernel)

# End of cmake-file.