cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include_directories(test_mocks/)

add_executable(test_runner tests/MemoryManagerUnit.cpp)
target_link_libraries(test_runner gtest gmock
        gmock_main gtest_main
        mem_manger_win)
