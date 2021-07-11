/**
 * @file      Mutex.hpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Implements the mutex interface.
 * @version   0.1
 * @date      29-05-2021
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef RTOS_CPP_WRAPPER_MUTEX_HPP
#define RTOS_CPP_WRAPPER_MUTEX_HPP

#include "IMutex.hpp"

namespace RTOS {

using mutex_handle = SemaphoreHandle_t;
using mutex_cb = StaticSemaphore_t;

/**
 * @breif FreeRTOS flavour of the mutex.
 */
class Mutex : public IMutex {
  SemaphoreHandle_t m_mutexHandle; /**< Mutex handler. */
  mutex_cb *m_pMutexCB{};          /**< Control block for the mutex. */
  bool m_isMutexCreated;

public:
  ~Mutex() override = default;

  explicit Mutex();

  /*------------------------------ IMutex interface
   * --------------------------*/
  bool create() override;
  bool lock(RTOS::delay_t timeOut) override;
  bool lock() override;
  bool unlock() override;
  bool remove() override;
  bool is_mutex_created() const override;
};
} // namespace RTOS

#endif // RTOS_CPP_WRAPPER_MUTEX_HPP
