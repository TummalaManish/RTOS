cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_library(kernel rtos_core/list.c
        rtos_core/tasks.c rtos_core/queue.c
        rtos_core/portable/MemMang/heap_4.c)

if(${PORT_SELECT} STREQUAL "WIN_SIM")
    target_sources(kernel PRIVATE rtos_core/portable/MSVC-MingW/port.c)
    target_include_directories(kernel PUBLIC
            configuration/win_sim
            rtos_core/include
            rtos_core/portable/MSVC-MingW/)
    target_link_libraries(kernel winmm)

elseif(${PORT_SELECT} STREQUAL "IAR_M3")
    target_sources(kernel PRIVATE rtos_core/portable/IAR/ARM_CM3/port.c
            rtos_core/portable/IAR/ARM_CM3/portasm.s)
    target_include_directories(kernel PUBLIC
            configuration/IAR_M3
            rtos_core/include/
            rtos_core/portable/IAR/ARM_CM3/)
endif()