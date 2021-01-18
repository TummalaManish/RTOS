/**
 * @file      Time64.cpp.c
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Implementation of 64-bit time interface.
 * @version   0.1
 * @date      17-01-2021
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "Time64.hpp"

namespace RTOS {

os_time_t Time64::get_time64() const {
  os_time_t timeToReturn = UINT64_MAX;
  vGetSystemTime(&timeToReturn);
  return timeToReturn;
}

void Time64::get_time64(os_time_t &msSinceEpoch) const {
  vGetSystemTime(&msSinceEpoch);
}

void Time64::set_time64(os_time_t const &msSinceEpoch) {
  vSetSystemTime(&msSinceEpoch);
}
} // namespace RTOS