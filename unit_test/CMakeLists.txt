cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include_directories(test_mocks/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

add_executable(test_runner tests/MemoryManagerUnit.cpp tests/ThreadUnit.cpp)
target_link_libraries(  test_runner
                        gtest gmock
                        gmock_main
                        gtest_main
                        mem_manger_win
                        obj_thread_win)
