cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_library(SYSVIEW_FreeRTOS_Specifics STATIC SEGGER_SYSVIEW_Config_FreeRTOS.c
                                      SEGGER_SYSVIEW_FreeRTOS.c)

target_include_directories(SYSVIEW_FreeRTOS_Specifics PUBLIC ./)

target_link_libraries(SYSVIEW_FreeRTOS_Specifics PUBLIC SEGGER_SYS_VIEW)
target_link_libraries(SYSVIEW_FreeRTOS_Specifics PUBLIC rtos_interface)

# End of cmake-file.