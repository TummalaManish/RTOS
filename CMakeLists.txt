cmake_minimum_required(VERSION 3.16)

project(RTOS_CPP_WRAPPER)

# Variables that'll be used with the project.
include(useroptions.cmake)

if (SIM)
    # Adds SIM macro to the target.
    add_compile_definitions("SIM")
endif()

if (NOT DEFINED PORT_SELECT)
    # Selects the appropriate port base.
    set(PORT_SELECT "WIN_SIM")
endif()

# This is the root directory that builds the core library.
add_subdirectory(rtos_cpp_wrappers)

# This the FreeRTOS kernel.
add_subdirectory(rtos_c)

if(TEST)
    # This is the library for the gtest.
    add_subdirectory(googletest)

    # Test directory for the functional tests.
    add_subdirectory(func_test)

    # Test directory for the unit tests.
    add_subdirectory(unit_test)
endif()
