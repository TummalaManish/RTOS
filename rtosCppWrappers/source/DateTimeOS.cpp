/**
 * @file      DateTime.cpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Implements the date time to retrieve os time.
 * @version   0.1
 * @date      02-01-2021
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "DateTimeOS.hpp"

namespace RTOS {

os_time_t RTOS::DateTimeOS::get_datetime() {
  os_time_t retTime;
  ker_get_datetime(retTime);
  return retTime;
}
void RTOS::DateTimeOS::get_datetime(os_time_t &rToHoldTime) {
  ker_get_datetime(rToHoldTime);
}
void RTOS::DateTimeOS::set_datetime(os_time_t &timeToSet) {
  ker_set_datetime(timeToSet);
}

void DateTimeOS::ker_get_datetime(os_time_t &refToDateTime) {
  vGetSystemTime(&refToDateTime);
}
void DateTimeOS::ker_set_datetime(const os_time_t &refToDateTime) {
  vSetSystemTime(&refToDateTime);
}
} // namespace RTOS