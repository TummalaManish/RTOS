/**
 * @file      Mutex.cpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Implements mutex for FreeRTOS port.
 * @version   0.1
 * @date      29-05-2021
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Mutex.hpp"

namespace RTOS {

Mutex::Mutex() : m_mutexHandle(nullptr), m_isMutexCreated(false), m_mutexCB() {
  /* create the mutex */
  m_mutexHandle = xSemaphoreCreateMutexStatic(&m_mutexCB);
  if (m_mutexHandle != nullptr) {
    m_isMutexCreated = true;
  }
}

bool Mutex::create() {
  /* If mutex is not yet created, then create one. */
  if (is_mutex_created()) {
    m_mutexHandle = xSemaphoreCreateMutexStatic(&m_mutexCB);
    m_isMutexCreated = (m_mutexHandle != nullptr);
  }
  return m_isMutexCreated;
}

bool Mutex::lock(RTOS::delay_t timeOut) {
  bool retValue = false;
  /* Check if the mutex is created, if created then try to take it. */
  if (is_mutex_created() &&
      xSemaphoreTake(m_mutexHandle,
                     static_cast<TickType_t>(pdMS_TO_TICKS(timeOut)))) {
    retValue = true;
  }
  return retValue;
}

bool Mutex::lock() { return lock(0); }

bool Mutex::unlock() {
  bool retValue = false;
  /* Check if the mutex is created, if created then try to give the mutex back*/
  if (is_mutex_created() && xSemaphoreGive(m_mutexHandle)) {
    retValue = true;
  }
  return retValue;
}

bool Mutex::remove() {
  void *holder = nullptr;
  // Check if the mutex is taken.
  holder = static_cast<void *>(xSemaphoreGetMutexHolder(m_mutexHandle));
  // If take fail the remove action else pass the action.
  if (holder != nullptr) {
    vSemaphoreDelete(m_mutexHandle);
  }
  return (holder != nullptr);
}

bool Mutex::is_mutex_created() { return m_isMutexCreated; }

} // namespace RTOS
