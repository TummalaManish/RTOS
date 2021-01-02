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

#include "DateTime.hpp"

namespace RTOS{

os_time_t RTOS::DateTime::get_datetime() {
  os_time_t retTime;
  ker_get_datetime(retTime);
  return retTime;
}
void RTOS::DateTime::get_datetime(os_time_t &rToHoldTime) {
  ker_get_datetime(rToHoldTime);
}
void RTOS::DateTime::set_datetime(os_time_t &timeToSet) {
  ker_set_datetime(timeToSet);
}

void DateTime::ker_get_datetime (os_time_t &refToDateTime) {
  vGetSystemTime(&refToDateTime);
}
void DateTime::ker_set_datetime(const os_time_t &refToDateTime) {
  vSetSystemTime(&refToDateTime);
}
}