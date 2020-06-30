cmake_minimum_required(VERSION 3.16)

project(RTOS_CPP_WRAPPER)

#Varibles that'll be used with the project.
include(useroptions.cmake)

# This is the root directory that builds the core library.
add_subdirectory(rtos_cpp_wrappers)

#This is the library for the gtest.
add_subdirectory(googletest)

#Test directory for the unit tests.
add_subdirectory(unit_test)