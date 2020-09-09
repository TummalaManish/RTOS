/**
 * @file        MemoryManagerUnit.cpp
 * @author      your name (you@domain.com)
 * @brief       Implements the unit test for the MemoryManager.
 * @version     0.1
 * @date        2020-07-18
 * 
 * @copyright   Copyright (c) 2020
 */

#include <MemoryManagerMock.hpp>
#include <kernel_helpers.hpp>

/*
==========================:Example test format:===========================
TEST(MemoryManagerTestPositive, AllocatingStack){

    ----------- SETUP: -----------
    RTOS::rtos_thread_stack_t stack;
    RTOS::rtos_stack_size_t size = 100;

    ----------- ACTION: ----------
    RTOS::eMemoryResult res = MemoryManagerMock::get_Instance().get_stack(stack, size);

    --------- ASSERTION: ---------
    ASSERT_EQ(res, RTOS::eMemoryResult::eMemAllocationSuccess);
}
*/

/*-------------- Positive Tests ----------------*/

using namespace TEST;

TEST(MemoryManagerTestPositive, AllocatingStack){

    RTOS::stack_t stack;
    RTOS::stack_size_t size = 100;
    RTOS::eMemoryResult res = MemoryManagerMock::get_Instance().get_stack(stack, size);

    ASSERT_EQ(res, RTOS::eMemoryResult::eMemAllocationSuccess);
    MemoryManagerMock::get_Instance().release_stack(stack);
}

TEST(MemoryManagerTestPositive, AllocatingTask){

    RTOS::control_block_t TCB;
    RTOS::eMemoryResult res = MemoryManagerMock::get_Instance().get_CB(&TCB);

    ASSERT_EQ(res, RTOS::eMemoryResult::eMemAllocationSuccess);
    MemoryManagerMock::get_Instance().release_CB(TCB);
}

TEST(MemoryManagerTestPositive, AllocatingByte){

    uint8_t* p_Block;
    size_t size = 24*1000;
    RTOS::eMemoryResult res = MemoryManagerMock::get_Instance().get_block(reinterpret_cast<void **>(&p_Block), size);

    ASSERT_EQ(res, RTOS::eMemoryResult::eMemAllocationSuccess);
    MemoryManagerMock::get_Instance().release_block(p_Block);
}

/*------------------- Negative Tests ------------------*/
TEST(MemoryManagerTestNegative, UnableToAllocateStack){

    RTOS::stack_t stack;
    RTOS::stack_size_t size = 24 * 1024; //Trying to reserve memory more than available.
    RTOS::eMemoryResult res = MemoryManagerMock::get_Instance().get_stack(stack, size);

    ASSERT_EQ(res, RTOS::eMemoryResult::eMemAllocationFailed);
}

TEST(MemoryManagerTestNegative, UnableToAllocateTask){

    uint8_t* p_Temp;
    //Filling up the stack.
    EXPECT_EQ(MemoryManagerMock::get_Instance().get_block(reinterpret_cast<void **>(&p_Temp),
                                                          configTOTAL_HEAP_SIZE - 32),
              RTOS::eMemoryResult::eMemAllocationSuccess);
    RTOS::control_block_t TCB; //Trying to reserve memory when not available.
    RTOS::eMemoryResult res = MemoryManagerMock::get_Instance().get_CB(&TCB);

    ASSERT_EQ(res, RTOS::eMemoryResult::eMemAllocationFailed);
}

TEST(MemoryManagerTestNegative, UnableToAllocateByte){

    uint8_t* p_Block;
    size_t size = 24*10000;
    RTOS::eMemoryResult res = MemoryManagerMock::get_Instance().get_block(reinterpret_cast<void **>(&p_Block), size);

    ASSERT_EQ(res, RTOS::eMemoryResult::eMemAllocationFailed);
}
