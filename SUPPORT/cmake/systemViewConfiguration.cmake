cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

#------------------------------------------------------------------------------#
#  The settings here are the default setting that will work with systemview 
#  is enabled. In Future these will change maybe eloped by a configuration
#  manager.
#------------------------------------------------------------------------------#

if (NOT DEFINED SYSTEM_VIEW_ANALYSIS)
set (SYSTEM_VIEW_ANALYSIS 0 CACHE INTERNAL "Will SYSTEM VIEW status.")
endif()

if (NOT DEFINED SYSTEM_VIEW_APP_NAME)
set (SYSTEM_VIEW_APP_NAME "NEST Platform" CACHE INTERNAL "Name of the application. ")
endif()

if (NOT DEFINED SYSTEM_VIEW_DEVICE_NAME)
set (SYSTEM_VIEW_DEVICE_NAME "Generic Device" CACHE INTERNAL "Device ID")
endif()

if (NOT DEFINED SYSTEM_VIEW_POSTMORTEM)
set (SYSTEM_VIEW_POSTMORTEM 0 CACHE INTERNAL "SYS_VIEW Postmortem mode flag.")
endif()

# End of cmake-file.