cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_subdirectory(sysviewFreeRTOSConf)

add_library(kernel rtosCore/list.c
        rtosCore/tasks.c rtosCore/queue.c
        rtosCore/portable/MemMang/heap_4.c
        configuration/Assert_call/rtosAssert.c)

# This for the freeRTOSConfig.hpp to include trace api's.
target_compile_definitions(kernel PUBLIC SYS_VIEW=${SYSTEM_VIEW_ANALYSIS})

# Only link the SYSTEM_VIEW if analysis is enabled by the application.
if (SYSTEM_VIEW_ANALYSIS EQUAL 1)
  if (NOT DEFINED RTT_ENABLED)
    set (RTT_ENABLED 1 CACHE INTERNAL "Holds the status of RTT")
  endif()
  target_link_libraries(kernel PUBLIC SYSVIEW_FreeRTOS_Specifics)
endif()

add_library(rtos_core_interface INTERFACE)

if(${PORT_SELECT} STREQUAL "WIN_SIM")
    target_sources(kernel PRIVATE rtosCore/portable/MSVC-MingW/port.c)
    target_include_directories(kernel PUBLIC
            configuration/win_sim
            rtosCore/include
            rtosCore/portable/MSVC-MingW/)
    target_include_directories(rtos_core_interface INTERFACE
            configuration/win_sim
            rtosCore/include
            rtosCore/portable/MSVC-MingW/)
    target_link_libraries(kernel PUBLIC winmm)
    # This warning suppression is for the SYSTEMVIEW api's.
    target_compile_options(kernel PRIVATE -Wno-pointer-to-int-cast)

elseif(${PORT_SELECT} STREQUAL "IAR_M3")
    target_sources(kernel PRIVATE rtosCore/portable/IAR/ARM_CM3/port.c
            rtosCore/portable/IAR/ARM_CM3/portasm.s)
    target_include_directories(kernel PUBLIC
            configuration/IAR_M3
            rtosCore/include/
            rtosCore/portable/IAR/ARM_CM3/)
    target_include_directories(rtos_core_interface INTERFACE
            configuration/IAR_M3
            rtosCore/include/
            rtosCore/portable/IAR/ARM_CM3/)

elseif(${PORT_SELECT} STREQUAL "IAR_M4F")
    target_sources(kernel PRIVATE rtosCore/portable/IAR/ARM_CM4F/port.c
            rtosCore/portable/IAR/ARM_CM4F/portasm.s)
    target_include_directories(kernel PUBLIC
            configuration/IAR_M4F
            rtosCore/include/
            rtosCore/portable/IAR/ARM_CM4F/)
    target_include_directories(rtos_core_interface INTERFACE
            configuration/IAR_M4F
            rtosCore/include/
            rtosCore/portable/IAR/ARM_CM4F/)

endif()