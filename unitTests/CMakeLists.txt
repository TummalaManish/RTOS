cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

file(GLOB_RECURSE SRC_FILES "*.cpp" "*.hpp")
set(USR_LCL_INC_FLS "${CMAKE_CURRENT_SOURCE_DIR}/mocks")
set(USR_LCL_LIB_FLS mem_manger obj_thread)

addSrcToTestRunner(SRC_FILES USR_LCL_LIB_FLS USR_LCL_INC_FLS)
# End of cmake-file.