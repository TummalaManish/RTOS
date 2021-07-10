cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

#------------------------------------------------------------------------------#
#  The settings here are the default setting that will work with systemview 
#  is enabled. In Future these will change maybe eloped by a configuration
#  manager.
#------------------------------------------------------------------------------#

if (NOT DEFINED RTT_ENABLED)
set (RTT_ENABLED 0 CACHE INTERNAL "Flag that specifies RTT is enabled.")
endif()

if (NOT DEFINED RTT_UP_BUFF_CNT)
set (RTT_UP_BUFF_CNT 3 CACHE INTERNAL "Number of up buffers in RTT.")
endif()

if (NOT DEFINED RTT_UP_BUFF_SIZE)
set (RTT_UP_BUFF_SIZE 1024 CACHE INTERNAL "Size of each up buffer.")
endif()

if (NOT DEFINED RTT_DOWN_BUFF_CNT)
set (RTT_DOWN_BUFF_CNT 3 CACHE INTERNAL "Number of down buffers in RTT.")
endif()

if (NOT DEFINED RTT_DOWN_BUFF_SIZE)
set (RTT_DOWN_BUFF_SIZE 16 CACHE INTERNAL "Size of each down buffer.")
endif()

# End of cmake-file.