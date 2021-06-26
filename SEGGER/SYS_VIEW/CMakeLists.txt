cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_library(SEGGER_SYS_VIEW STATIC  SEGGER_SYSVIEW.c)

target_include_directories(SEGGER_SYS_VIEW PUBLIC config include)
target_link_libraries(SEGGER_SYS_VIEW PUBLIC SEGGER_RTT)
# End of cmake-file.