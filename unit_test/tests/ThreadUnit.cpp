/**
 * @file        ThreadUnit.cpp
 * @author      Manish Tummala (manish.tummala@gmail.com)
 * @brief       Tests for the thread class.
 * @version     0.1
 * @date        2020-07-22
 * 
 * @copyright   Copyright (c) 2020
 * 
 */

#include <ThreadMock.hpp>

using namespace TEST;
TEST(ThreadCreationPostive, ThreadCreationValidParameters){
    const char* TaskName = "UTThread";
    constexpr thread_priority_t TaskPriority = 1;
    constexpr stack_size_t TaskStackSize = 100;
    ThreadMock thread(TaskName, TaskPriority, TaskStackSize);

    ASSERT_FALSE(thread.is_scheduler_running());
    //This cannot be tested any further.
}
