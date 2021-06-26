cmake_minimum_required(VERSION 3.16)

# tool-chain file for the the project.
set(CMAKE_TOOLCHAIN_FILE "../../SUPPORT/toolChainFiles/IAR/toolchain-ewarm.cmake")

project(RTOS_INTEGRATION_TESTS VERSION 0.0.0 LANGUAGES CXX C ASM)

# Adding variables that'll be used further down for the platform modules.
# Processor specific compile time arguments.
list(APPEND CMAKE_CXX_FLAGS "--cpu Cortex-M4F --fpu=VFPv4_sp --thumb --dlib_config normal")
list(APPEND CMAKE_C_FLAGS "--cpu Cortex-M4F --fpu=VFPv4_sp --thumb --dlib_config normal")
list(APPEND CMAKE_ASM_FLAGS "--cpu Cortex-M4F --fpu VFPv4_sp --thumb")

set(PORT_SELECT "IAR_M4F")

# Adding the RTOS Library.
# This the FreeRTOS kernel.
add_subdirectory(../../rtosC rtosC)
# This is the root directory that builds the core library.
add_subdirectory(../../rtosCppWrappers rtosCPP)

# Each test is added as a sperate executable in a sub directory.
add_subdirectory(initilizationTest)

# End of cmake-file.