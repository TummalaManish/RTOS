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

os_time_t RTOS::OSTime::get_ostime() {
  os_time_t retTime;
  ker_get_ostime(retTime);
  return retTime;
}
void RTOS::OSTime::get_ostime(os_time_t &rToHoldTime) {
  ker_get_ostime(rToHoldTime);
}
void RTOS::OSTime::set_ostime(os_time_t &timeToSet) {
  ker_set_ostime(timeToSet);
}

void OSTime::ker_get_ostime(os_time_t &refToDateTime) {
  vGetSystemTime(&refToDateTime);
}
void OSTime::ker_set_ostime(const os_time_t &refToDateTime) {
  vSetSystemTime(&refToDateTime);
}
} // namespace RTOS