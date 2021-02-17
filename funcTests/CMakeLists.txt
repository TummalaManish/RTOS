cmake_minimum_required(VERSION 3.16)

# Test that'll be configured to have "Active" in the test dir.
file(GLOB SUB_DIRS "*Active*")

# Iteratively adds the test to the target list.
if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
foreach(Test ${SUB_DIRS})
    add_subdirectory(${Test})
endforeach()
endif()

# End of cmake-file.