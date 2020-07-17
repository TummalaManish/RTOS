cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include_directories(../rtos_c/rtos_core/include)

add_library(obj_kernel source/Thread.cpp)
target_include_directories(obj_kernel PUBLIC include interface)
target_link_libraries(obj_kernel kernel port)

add_library(mem_manger source/MemoryManager.cpp)
target_include_directories(mem_manger PUBLIC include interface)
target_link_libraries(mem_manger c_mem_mang port)
