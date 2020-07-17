cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_library(port rtos_core/portable/MSVC-MingW/port.c)
target_include_directories(port PUBLIC configuration/ rtos_core/portable/MSVC-MingW/)

add_library(c_mem_mang rtos_core/portable/MemMang/heap_4.c)

add_library(kernel rtos_core/list.c rtos_core/tasks.c rtos_core/queue.c)
target_include_directories(kernel PUBLIC configuration/ rtos_core/include)
