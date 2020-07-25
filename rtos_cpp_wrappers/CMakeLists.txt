cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include_directories(../rtos_c/rtos_core/include)

#Thread not yet implemented.
add_library(obj_thread_win source/Thread.cpp)
target_include_directories(obj_thread_win PUBLIC include interface)
target_link_libraries(obj_thread_win kernel_win)

add_library(mem_manger_win source/MemoryManager.cpp)
target_include_directories(mem_manger_win PUBLIC include interface)
target_link_libraries(mem_manger_win kernel_win)
