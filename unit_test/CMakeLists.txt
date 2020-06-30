cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_executable(test_runner t_Test.cpp)
target_link_libraries(test_runner gtest gtest_main)
