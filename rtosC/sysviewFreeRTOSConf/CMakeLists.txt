cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# note: in the rtoc core the blow libray will only be linked
#       if the flag SYSTEM_VIEW_ANALYSIS is set to true.
add_library(SYSVIEW_FreeRTOS_Specifics STATIC SEGGER_SYSVIEW_Config_FreeRTOS.c
                                       SEGGER_SYSVIEW_FreeRTOS.c)

target_include_directories(SYSVIEW_FreeRTOS_Specifics PUBLIC ./)

target_link_libraries(SYSVIEW_FreeRTOS_Specifics PUBLIC SEGGER_SYS_VIEW rtos_interface)

if (PORT_SELECT STREQUAL "WIN_SIM" )
  target_compile_options(SYSVIEW_FreeRTOS_Specifics PRIVATE -Wno-int-to-pointer-cast)
endif()
# End of cmake-file.