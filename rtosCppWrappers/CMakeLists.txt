cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# The c-kernel is not distinguishable from the port to a simulator.

file(GLOB_RECURSE SRC_FILES "*.cpp" "*.hpp")

add_library(obj_kernel ${SRC_FILES})
target_include_directories(obj_kernel PUBLIC include interface)
target_link_libraries(obj_kernel kernel)

add_library(rtos_only_interface INTERFACE)
target_include_directories(rtos_only_interface INTERFACE include interface)
target_link_libraries(rtos_only_interface INTERFACE rtos_core_interface)
# End of cmake-file.