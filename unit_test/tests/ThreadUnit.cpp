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
    constexpr rtos_thread_priority_t TaskPriority = 1;
    constexpr rtos_stack_size_t TaskStackSize = 100;
    constexpr rtos_thread_type_e TaskThreadType = RTOS_THR_TYP_E::eKillable;
    ThreadMock thread(TaskName, TaskPriority, TaskStackSize, TaskThreadType);

    EXPECT_STREQ(thread.get_thread_name(), TaskName);
    EXPECT_EQ(thread.get_thread_priority(), TaskPriority);
    EXPECT_TRUE(thread.is_thread_killable());
//    ASSERT_FALSE(!thread.is_scheduler_running());
    //This cannot be tested any further.
}
