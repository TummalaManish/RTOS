cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_library(kernel_win rtos_core/list.c
        rtos_core/tasks.c rtos_core/queue.c
        rtos_core/portable/MemMang/heap_4.c
        rtos_core/portable/MSVC-MingW/port.c)
target_include_directories(kernel_win PUBLIC configuration/
        rtos_core/include
        rtos_core/portable/MSVC-MingW/)
target_link_libraries(kernel_win winmm)
