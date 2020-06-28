cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# link_libraries(/usr/src/googletest/lib/libgtest.a)

add_executable(test_runner t_Test.cpp)
target_link_libraries(test_runner gtest_main
                                  gtest
                                  pthread)
target_include_directories(test_runner PRIVATE /usr/src/googletest/googletest/include)
