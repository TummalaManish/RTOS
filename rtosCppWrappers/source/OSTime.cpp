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

#include "OSTime.hpp"

namespace RTOS {

os_time_t RTOS::DateTimeOS::get_ostime() {
  os_time_t retTime;
  ker_get_ostime(retTime);
  return retTime;
}
void RTOS::DateTimeOS::get_ostime(os_time_t &rToHoldTime) {
  ker_get_ostime(rToHoldTime);
}
void RTOS::DateTimeOS::set_ostime(os_time_t &timeToSet) {
  ker_set_ostime(timeToSet);
}

void DateTimeOS::ker_get_ostime(os_time_t &refToDateTime) {
  vGetSystemTime(&refToDateTime);
}
void DateTimeOS::ker_set_ostime(const os_time_t &refToDateTime) {
  vSetSystemTime(&refToDateTime);
}
} // namespace RTOS