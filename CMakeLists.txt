cmake_minimum_required(VERSION 3.16)

project(RTOS_CPP_WRAPPER)

# Variables that'll be used with the project.
include(useroptions.cmake)

add_compile_definitions("SIM")
# Selects the appropriate port base.
set(PORT_SELECT "WIN_SIM")

# This is the root directory that builds the core library.
add_subdirectory(rtos_cpp_wrappers)

# This the FreeRTOS kernel.
add_subdirectory(rtos_c)

if(RTOS_TEST)
    # This is the library for the gtest.
    add_subdirectory(googletest)

    # Test directory for the unit tests.
    add_subdirectory(unit_test)
endif()