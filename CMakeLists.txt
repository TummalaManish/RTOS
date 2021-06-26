cmake_minimum_required(VERSION 3.16)

project(RTOS_CPP_WRAPPER VERSION 0.0.0 LANGUAGES CXX C ASM)

enable_testing()
if(NOT TARGET gtest)
  if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_subdirectory(googletest)
  include(GoogleTest)
  endif()
endif()

# Selecting windows simulator for un-specified configurations.
if (NOT DEFINED PORT_SELECT)
  set(PORT_SELECT "WIN_SIM")
endif()

if (PORT_SELECT STREQUAL "WIN_SIM")
  add_compile_definitions("SIM")
endif()

# Support Libraries
add_subdirectory(SEGGER/RTT)
add_subdirectory(SEGGER/SYS_VIEW)

# This the FreeRTOS kernel.
add_subdirectory(rtosC)
# This is the root directory that builds the core library.
add_subdirectory(rtosCppWrappers)

# Tests
add_subdirectory(unitTests)
add_subdirectory(funcTests)

# End of cmake-file.