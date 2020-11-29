cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Parameters : USR_INC_SUB_DIR - Holds the Varible that holds the list of sub dirs to include.
function(createUnitTestExe USR_INC_SUB_DIR)
  enable_testing()
  include(CTest)
  include(GoogleTest)
  # Adding GoogleTest to the build.
  add_subdirectory(googletest GTest)
  
  # All the test objects will be attached to this variable.
  set(USR_TST_OBJS "" CACHE INTERNAL "Holds the object files of the tests.")
  # All the test libs will be attached to this variable.
  set(USR_TST_LIBS "" CACHE INTERNAL "Holds the library files required by the tests.")
  # All the test inclide files will be add to this variable.
  set(USR_TST_INCS "" CACHE INTERNAL "Holds the include paths required by the tests.")
  # Attaches all the required objects files to create test.
  foreach(USR_DIR ${${USR_INC_SUB_DIR}})
    add_subdirectory(${USR_DIR})
  endforeach()
  # Parent unitest that has to include the rest of the inner test.
  add_executable(TEST_RUNNER ${USR_TST_OBJS})
  # Adding test libraries & GTest libraries to be linked to the TEST_RUNNER.
  target_link_libraries(TEST_RUNNER
                        ${USR_TST_LIBS}
                        gtest gmock
                        gmock_main
                        gtest_main)
  target_include_directories(TEST_RUNNER PRIVATE ${USR_TST_INCS})

  # All the tests are added as a single test into cmake.
  # ----------------------------------------------------------------------------
  # The idea here is that instead of linking test individually we can go for a 
  # single executable. This will speed up the build time for the TEST_RUNNER.
  # ----------------------------------------------------------------------------
  gtest_discover_tests(TEST_RUNNER)
endfunction()

# @breif: Used to add test sources to the TEST RUNNER.
# @param: USR_TST_SRC_FLS Hold the varible that holds the TST source files.
# @param: USR_TST_SRC_FLS Holds the varible that holds the LIB files.
# @param: USR_TST_INC_FLS Holds the varible that holds the INC folder paths.
function(addSrcToTestRunner USR_TST_SRC_FLS USR_TST_LIB_FLS USR_TST_INC_FLS)
set(USR_TST_OBJS ${USR_TST_OBJS} ${${USR_TST_SRC_FLS}} CACHE INTERNAL "")
set(USR_TST_LIBS ${USR_TST_LIBS} ${${USR_TST_LIB_FLS}} CACHE INTERNAL "")
set(USR_TST_INCS ${USR_TST_INCS} ${${USR_TST_INC_FLS}} CACHE INTERNAL "")
endfunction()

# End of cmake-file.