/**
 * @file      MockMutex.hpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Mock for mutex.
 * @version   0.1
 * @date      30-05-2021
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef RTOS_CPP_WRAPPER_MOCKMUTEX_HPP
#define RTOS_CPP_WRAPPER_MOCKMUTEX_HPP

// GoogleTest includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// RTOS includes
#include "IMutex.hpp"

namespace NEST_TESTS {

class MockMutex : public RTOS::IMutex {
public:
  MOCK_METHOD(bool, create, (), (override));
  MOCK_METHOD(bool, lock, (RTOS::delay_t const), (override));
  MOCK_METHOD(bool, lock, (), (override));
  MOCK_METHOD(bool, unlock, (), (override));
  MOCK_METHOD(bool, remove, (), (override));
  MOCK_METHOD(bool, is_mutex_created, (), (const, override));
};
} // namespace NEST_TESTS

#endif // RTOS_CPP_WRAPPER_MOCKMUTEX_HPP
