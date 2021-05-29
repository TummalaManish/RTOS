/**
 * @file      IMutex.hpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Implementation for the mutex.
 * @version   0.1
 * @date      29-05-2021
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef RTOS_CPP_WRAPPER_IMUTEX_HPP
#define RTOS_CPP_WRAPPER_IMUTEX_HPP

#include "rtos_types.hpp"

namespace RTOS {

/**
 * @brief Interface class for the mutex.
 */
class IMutex {
public:
  virtual ~IMutex() = default;

  /**
   * @brief This method will create a mutex
   * @return
   */
  virtual bool create() = 0;

  /**
   * @brief Locks the mutex.
   * @param timeOut Time to wait to get the mutex.
   * @return true if the lock is acquired by timeOutTime else false.
   */
  virtual bool lock(RTOS::delay_t timeOut) = 0;

  /**
   * @breif Locks the mutex with no wait.
   * @return true if the lock is acquired else false.
   */
  virtual bool lock() = 0;

  /**
   * @brief Returns the mutex.
   */
  virtual bool unlock() = 0;

  /**
   * @brief Deletes the mutex.
   * @return true if no task is waiting else false.
   */
  virtual bool remove() = 0;

  /**
   * @brief Checks if the mutex is created if not it has to be created.
   * @return true if the mutex if created else false.
   */
  virtual bool is_mutex_created() = 0;
  /*TODO: This interface will be extended further in the future.*/
};
}

#endif // RTOS_CPP_WRAPPER_IMUTEX_HPP
