cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_library(kernel rtosCore/list.c
        rtosCore/tasks.c rtosCore/queue.c
        rtosCore/portable/MemMang/heap_4.c
        configuration/Assert_call/rtosAssert.cpp)

if(${PORT_SELECT} STREQUAL "WIN_SIM")
    target_sources(kernel PRIVATE rtosCore/portable/MSVC-MingW/port.c)
    target_include_directories(kernel PUBLIC
            configuration/win_sim
            rtosCore/include
            rtosCore/portable/MSVC-MingW/)
    target_link_libraries(kernel winmm)

elseif(${PORT_SELECT} STREQUAL "IAR_M3")
    target_sources(kernel PRIVATE rtosCore/portable/IAR/ARM_CM3/port.c
            rtosCore/portable/IAR/ARM_CM3/portasm.s)
    target_include_directories(kernel PUBLIC
            configuration/IAR_M3
            rtosCore/include/
            rtosCore/portable/IAR/ARM_CM3/)
endif()