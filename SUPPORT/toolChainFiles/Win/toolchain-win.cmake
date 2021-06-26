# CMake Toolchain File for MinGW-w64 (64-bit) Cross Compilation
set(CMAKE_SYSTEM_NAME "Generic")

# which tools to use
set(CMAKE_C_COMPILER   "C:/MinGW/bin/gcc.exe" CACHE INTERNAL "compiler")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe" CACHE INTERNAL "compiler")

# here is where the target environment located
set(CMAKE_FIND_ROOT_PATH  "C:/MinGW")

# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# initialize required linker flags
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static-libgcc -static-libstdc++")

# end of toolchain file