cmake_minimum_required(VERSION 3.16)

# Test that'll be configured have tohave "Actuve" in the test dir.
file(GLOB SUB_DIRS "*Active*")

# Iteratively adds the test to the target list.
foreach(Test ${SUB_DIRS})
    add_subdirectory(${Test})
endforeach()

# End of cmake-file.