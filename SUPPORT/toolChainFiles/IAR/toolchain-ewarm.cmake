### BEGIN CMAKE_TOOLCHAIN_FILE
# "Generic" is used when cross compiling
set(CMAKE_SYSTEM_NAME Generic)

# Set the EW installation root directory 
#(Avoid spaces in the path or you need to escape them)
set(EW_ROOT_DIR "C:/Program\ Files/IAR\ Systems/Embedded\ Workbench\ 9.0/arm")

# Compiler flags needed to compile for this CPU
set(CPU_FLAGS "")

# Setting compiler name.
set(USR_CXX_COMPILER IAR)
# Will be used by the driver code selecting the appropiate driver files.
add_compile_definitions(__ICCARM__)

# Set up the CMake variables for compiler and assembler
# (The reason for both C and CXX variables is that CMake 
# treats C and C++ tools individually)

# No dlib configuration has been selected by default.
set(CMAKE_C_COMPILER "${EW_ROOT_DIR}/bin/iccarm.exe" CACHE INTERNAL "IAR Compiler")
set(CMAKE_CXX_COMPILER "${EW_ROOT_DIR}/bin/iccarm.exe" CACHE INTERNAL "IAR Compiler")
set(CMAKE_ASM_COMPILER "${EW_ROOT_DIR}/bin/iasmarm.exe" CACHE INTERNAL "IAR Linker")

# Set up the CMake variables for the linker
set(LINKER_SCRIPT "${EW_ROOT_DIR}/config/linker/ST/stm32f103x8.icf")
set(APPEND CMAKE_C_LINK_FLAGS "--map ${CMAKE_BINARY_DIR}/STMF103.map --semihosting")
set(APPEND CMAKE_CXX_LINK_FLAGS "--map ${CMAKE_BINARY_DIR}/STMF103.map --semihosting")

### END CMAKE_TOOLCHAIN_FILE
