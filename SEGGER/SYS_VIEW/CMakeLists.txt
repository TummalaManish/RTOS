cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include(../../SUPPORT/cmake/systemViewConfiguration.cmake)

#------------------------------------------------------------------------------#
#  Here RTT buffer count must be increment once component level configuration
#  is enabled for the entire system. For now the default values of the RTT 
#  buffer count is enough.
#------------------------------------------------------------------------------#

add_library(SEGGER_SYS_VIEW STATIC  SEGGER_SYSVIEW.c)

target_include_directories(SEGGER_SYS_VIEW PUBLIC config include)
target_link_libraries(SEGGER_SYS_VIEW PUBLIC SEGGER_RTT)

if (PORT_SELECT STREQUAL WIN_SIM)
    set (SYSTEM_VIEW_POSTMORTEM 1 CACHE INTERNAL "SYS_VIEW Postmortem mode flag.")
endif()
# Adding the configuration definitions. See readme.md file for more info.
target_compile_definitions(SEGGER_SYS_VIEW PUBLIC
SYSTEM_VIEW_ANALYSIS=${SYSTEM_VIEW_ANALYSIS}
SYSTEM_VIEW_APP_NAME="${SYSTEM_VIEW_APP_NAME}"
SYSTEM_VIEW_DEVICE_NAME="${SYSTEM_VIEW_DEVICE_NAME}"
SYSTEM_VIEW_POSTMORTEM=${SYSTEM_VIEW_POSTMORTEM}
)
# End of cmake-file.