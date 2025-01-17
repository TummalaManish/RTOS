

#ifndef RTOS_CPP_WRAPPER_MEMORYMANAGERMOCK_HPP
#define RTOS_CPP_WRAPPER_MEMORYMANAGERMOCK_HPP

#include <MemoryManager.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace TEST {
class MemoryManagerMock : public RTOS::MemoryManager {
  MOCK_METHOD2(get_block, RTOS::eMemoryResult(void **, size_t));
  MOCK_METHOD1(release_block, void(void *));
  MOCK_METHOD2(get_stack,
               RTOS::eMemoryResult(RTOS::stack_t &, RTOS::stack_size_t));
  MOCK_METHOD1(release_stack, void(RTOS::stack_t));
  MOCK_METHOD1(get_CB, RTOS::eMemoryResult(RTOS::control_block_t *));
  MOCK_METHOD1(release_CB, void(RTOS::control_block_t));
};
} // namespace TEST
#endif // RTOS_CPP_WRAPPER_MEMORYMANAGERMOCK_HPP
