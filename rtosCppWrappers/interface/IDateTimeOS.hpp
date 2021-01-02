/**
 * @file      IDateTime.hpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Interface for the date time service.
 * @version   0.1
 * @date      02-01-2021
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef RTOS_CPP_WRAPPER_IDATETIME_H
#define RTOS_CPP_WRAPPER_IDATETIME_H

#include "rtos_types.hpp"

namespace RTOS {

class IDateTimeOS {
public:
  virtual ~IDateTimeOS() = default;

  /**
   * @brief returns os time in ms.
   * @return os_time_t returns time in ms since scheduler has started.
   */
  virtual os_time_t get_datetime() = 0;

  /**
   * @brief passes out the os time in ms.
   * @param rToHoldTime reference to variable to hold time.
   */
  virtual void get_datetime(os_time_t &rToHoldTime) = 0;

  /**
   * @brief sets the os time to the specified value.
   * @param timeToSet new time to be set to system clock.
   * @return true if the adjustment is successfully else false.
   */
  virtual void set_datetime(os_time_t &timeToSet) = 0;
};
} // namespace RTOS

#endif // RTOS_CPP_WRAPPER_IDATETIME_H
