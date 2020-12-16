cmake_minimum_required(VERSION 3.16)

project(RTOS_CPP_WRAPPER VERSION 0.0.0)
# Selecting windows simulator for un-specified configurations.
if (NOT DEFINED PORT_SELECT)
  set(PORT_SELECT "WIN_SIM")
  # TODO: Have to remove this and placed as target compile def.
  add_compile_definitions("SIM")
endif()
# This the FreeRTOS kernel.
add_subdirectory(rtos_c)
# This is the root directory that builds the core library.
add_subdirectory(rtosCppWrappers)

# Check if there is a parent directory to the current directory.
get_directory_property(USR_IS_CHILD PARENT_DIRECTORY)

if (USR_IS_CHILD) 
  # Directory has a parent.
  # UnitTest configuration.
  if (CMAKE_BUILD_TYPE STREQUAL "UnitTest")
    if (NOT(${PORT_SELECT} STREQUAL "WIN_SIM"))
      message(FATAL_ERROR "${PORT_SELECT} is not a appropriate option for kernel port.")
    endif()
    add_subdirectory(unitTests)
    add_subdirectory(funcTests)
  # Analysis configuration.
  elseif(CMAKE_BUILD_TYPE STREQUAL "Analysis")
    # TODO: Add analysis configuration.
  # Alternative configuration.
  elseif(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL
          "Release")
    message(STATUS "Building under ${CMAKE_BUILD_TYPE}.")
  else()
    message(FATAL_ERROR "${CMAKE_BUILD_TYPE} is not supported.")
  endif()

else()
  # This is the parent directory.
  include(buildSupport/unitTestsInfra.cmake)
  # UnitTest configuration.
  if (CMAKE_BUILD_TYPE STREQUAL "UnitTest")
  set(USR_INC_TST_DIRS unitTests funcTests)
  createUnitTestExe(USR_INC_TST_DIRS)
  # Analysis configuration.
  elseif(CMAKE_BUILD_TYPE STREQUAL "Analysis")
    # TODO: Have to add Analysis cmake-infra.
  # Alternative configuration.
  else()
  message(FATAL_ERROR "${CMAKE_BUILD_TYPE} is not supported.")
  endif()
endif()