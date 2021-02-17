cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
add_executable(rtosUnitTestExe 
                    ThreadUnit.cpp
                    MemoryManagerUnit.cpp)
target_include_directories(rtosUnitTestExe PUBLIC mocks)
target_link_libraries(rtosUnitTestExe PUBLIC  obj_kernel 
                                              gtest
                                              gmock
                                              gtest_main
                                              gmock_main)
gtest_discover_tests(rtosUnitTestExe)
endif()
# End of cmake-file.s