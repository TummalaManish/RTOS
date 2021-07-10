cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include (../../SUPPORT/cmake/seggerRTTConfiguration.cmake)

add_library(SEGGER_RTT STATIC SEGGER_RTT_printf.c
                              SEGGER_RTT.c)

target_include_directories(SEGGER_RTT PUBLIC config include)

if (PORT_SELECT STREQUAL "WIN_SIM")
target_compile_definitions(SEGGER_RTT PUBLIC RTT_USE_ASM=0)

# The ASM version of the write lock.
elseif(PORT_SELECT STREQUAL "IAR_M3" OR PORT_SELECT STREQUAL "IAR_M4F")
target_compile_definitions(SEGGER_RTT PUBLIC RTT_USE_ASM=1)
target_sources(SEGGER_RTT PRIVATE SEGGER_RTT_ASM_ARMv7M.s)
endif()

# Configuration definitions for the RTT. See readme.md for more info.
target_compile_definitions(SEGGER_RTT PUBLIC 
RTT_ENABLED=${RTT_ENABLED}
RTT_UP_BUFF_CNT=${RTT_UP_BUFF_CNT}
RTT_UP_BUFF_SIZE=${RTT_UP_BUFF_SIZE}
RTT_DOWN_BUFF_CNT=${RTT_DOWN_BUFF_CNT}
RTT_DOWN_BUFF_SIZE=${RTT_DOWN_BUFF_SIZE})

# End of cmake-file.