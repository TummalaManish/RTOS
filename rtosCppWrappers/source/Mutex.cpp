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
#include "MemoryManager.hpp"

namespace RTOS {

Mutex::Mutex()
    : m_mutexHandle(nullptr), m_isMutexCreated(false), m_pMutexCB(nullptr) {
  /* Try and get the control block from storage */
  bool const isSuccessful = MemoryManager::get_Instance().get_CB(&m_pMutexCB) ==
                            eMemoryResult::eMemAllocationSuccess;
  if (isSuccessful) {
    /* create the mutex */
    m_mutexHandle = xSemaphoreCreateMutexStatic(m_pMutexCB);
    if (m_mutexHandle != nullptr) {
      m_isMutexCreated = true;
    }
  } else {
    debug_break;
  }
}

bool Mutex::create() {
  /* If mutex is not yet created, then create one. */
  if (is_mutex_created()) {
    m_mutexHandle = xSemaphoreCreateMutexStatic(m_pMutexCB);
    m_isMutexCreated = (m_mutexHandle != nullptr);
  }
  return m_isMutexCreated;
}

bool Mutex::lock(RTOS::delay_t timeOut) {

  base_t ret_val = pdFALSE;
  if (is_mutex_created()) {
    /* If the call is made from a ISR or Application and call relv. api. */
    if (xPortIsInsideInterrupt() == pdTRUE) {

      /* Check if a context switch is required. */
      base_t YieldRequired = 0U;
      ret_val = xSemaphoreTakeFromISR(m_mutexHandle, &YieldRequired);

      /* Perform a switch if required. */
      if (YieldRequired == pdTRUE) {
        portYIELD();
      }
    }

    /* Not in an ISR so using normal flavour if the api. */
    else {
      ret_val = xSemaphoreTake(m_mutexHandle,
                               static_cast<TickType_t>(pdMS_TO_TICKS(timeOut)));
    }
  }
  return ret_val == pdTRUE;
}

bool Mutex::lock() { return lock(0); }

bool Mutex::unlock() {

  base_t ret_val = pdFALSE;
  if (is_mutex_created()) {
    /* If the call is made from a ISR or Application and call relv. api. */
    if (xPortIsInsideInterrupt() == pdTRUE) {

      /* Check if a context switch is required. */
      base_t YieldRequired = 0U;
      ret_val = xSemaphoreGiveFromISR(m_mutexHandle, &YieldRequired);

      /* Perform a switch if required. */
      if (YieldRequired == pdTRUE) {
        portYIELD();
      }
    }

    /* Not in an ISR so using normal flavour if the api. */
    else {
      ret_val = xSemaphoreGive(m_mutexHandle);
    }
  }
  return ret_val == pdTRUE;
}

bool Mutex::remove() {
  void *holder = nullptr;
  // Check if the mutex is taken.
  holder = static_cast<void *>(xSemaphoreGetMutexHolder(m_mutexHandle));
  // If take fail the remove action else pass the action.
  if (holder == nullptr) {
    vSemaphoreDelete(m_mutexHandle);
  }
  return (holder == nullptr);
}

bool Mutex::is_mutex_created() const { return m_isMutexCreated; }

} // namespace RTOS
