

#ifndef RTOS_CPP_WRAPPER_MEMORYMANAGERMOCK_HPP
#define RTOS_CPP_WRAPPER_MEMORYMANAGERMOCK_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MemoryManager.hpp>

namespace TEST{
        class MemoryManagerMock:
        public RTOS::MemoryManager{
            MOCK_METHOD2(get_block, RTOS::eMemoryResult(void * *, size_t));
            MOCK_METHOD1(release_block, void(void * ));
            MOCK_METHOD2(get_stack, RTOS::eMemoryResult(RTOS::thread_stack_t & , RTOS::stack_size_t));
            MOCK_METHOD1(release_stack, void(RTOS::thread_stack_t));
            MOCK_METHOD1(get_TCB, RTOS::eMemoryResult(RTOS::thread_cb_t & ));
            MOCK_METHOD1(release_TCB, void(RTOS::thread_cb_t));
        };
}
#endif //RTOS_CPP_WRAPPER_MEMORYMANAGERMOCK_HPP
