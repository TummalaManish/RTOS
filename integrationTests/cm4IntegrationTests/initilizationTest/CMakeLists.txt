cmake_minimum_required(VERSION 3.16)

# TODO:Source and Configuration file generation.
# Note: for now the linker configuration is static.
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} --config \
${CMAKE_CURRENT_SOURCE_DIR}/linkerConfiguration/app_linker_script.icf")

add_executable(InitilizationTest ThreadCreationTests.cpp)
target_link_libraries(InitilizationTest obj_kernel)

# End of cmake-file.