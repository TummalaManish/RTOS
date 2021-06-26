cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_library(SEGGER_RTT STATIC SEGGER_RTT_ASM_ARMv7M.s
                              SEGGER_RTT_printf.c
                              SEGGER_RTT.c)

target_include_directories(SEGGER_RTT PUBLIC config include)
# End of cmake-file.