cmake_minimum_required(VERSION 3.16)

# Any new test has to be appended here to be a target.
set(TestList
        Task_Creation_And_Running_Active
)

# Iteratively adds the test to the target list.
foreach(Test ${TestList})
    add_subdirectory(${Test})
endforeach()

# End of cmake-file.