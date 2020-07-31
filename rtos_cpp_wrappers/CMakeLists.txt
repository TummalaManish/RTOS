cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# The c-kernel is not distinguishable from the port to a simulator.
add_library(obj_thread source/Thread.cpp)
target_include_directories(obj_thread PUBLIC include interface)
target_link_libraries(obj_thread kernel)

add_library(mem_manger source/MemoryManager.cpp)
target_include_directories(mem_manger PUBLIC include interface)
target_link_libraries(mem_manger kernel)