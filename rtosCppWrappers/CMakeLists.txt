cmake_minimum_required(VERSION 3.16 FATAL_ERROR)


add_library(rtos_interface INTERFACE)
target_sources(rtos_interface INTERFACE interface/IQueueReceiver.hpp
                                        interface/IQueueSender.hpp
                                        interface/ISignal.hpp
                                        interface/IThread.hpp
                                        interface/ITime64.hpp)
target_include_directories(rtos_interface INTERFACE interface)
target_link_libraries(rtos_interface INTERFACE rtos_core_interface)

# The c-kernel is not distinguishable from the port to a simulator.
# Manually listing the sources.
add_library(obj_kernel STATIC include/MemoryManager.hpp
                              include/Queue.hpp
                              include/rtos_types.hpp
                              include/Thread.hpp
                              include/TQueue.hpp
                              include/Time64.hpp
# Sources that actually matter.
                              source/MemoryManager.cpp
                              source/Queue.cpp
                              source/Thread.cpp
                              source/Time64.cpp)
target_include_directories(obj_kernel PUBLIC include interface)
target_link_libraries(obj_kernel PUBLIC kernel INTERFACE rtos_core_interface)
# End of cmake-file.