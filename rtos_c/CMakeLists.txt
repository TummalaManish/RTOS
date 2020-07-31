cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if(${PORT_SELECT} STREQUAL "WIN_SIM")
add_library(kernel rtos_core/list.c
        rtos_core/tasks.c rtos_core/queue.c
        rtos_core/portable/MemMang/heap_4.c
        rtos_core/portable/MSVC-MingW/port.c)
target_include_directories(kernel PUBLIC
        configuration/
        rtos_core/include
        rtos_core/portable/MSVC-MingW/)
target_link_libraries(kernel winmm)

elseif(${PORT_SELECT} STREQUAL "IAR_M3")
add_library(kernel rtos_core/list.c
        rtos_core/tasks.c rtos_core/queue.c
        rtos_core/portable/MemMang/heap_4.c
        rtos_core/portable/MSVC-MingW/port.c)
target_include_directories(kernel PUBLIC
        configuration/
        rtos_core/include
        rtos_core/portable/IAR/ARM_CM3)
endif()