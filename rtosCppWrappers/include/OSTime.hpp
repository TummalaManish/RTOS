/**
 * @file      DataTime.hpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Implements date time to retrieve the system time.
 * @version   0.1
 * @date      02-01-2021
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef RTOS_CPP_WRAPPER_OSTIME_HPP
#define RTOS_CPP_WRAPPER_OSTIME_HPP

#include "rtos_types.hpp"

namespace RTOS{

/**
 * @brief Date time class to retrive date and time of the system.
 */
class OSTime {
public:

  static os_time_t get_ostime() override;
  static void get_ostime(os_time_t &rToHoldTime);
  static void set_ostime(os_time_t &timeToSet);

private:
  static void ker_get_ostime(os_time_t & refToDateTime);
  static void ker_set_ostime(os_time_t const& refToDateTime);
};
}
#endif // RTOS_CPP_WRAPPER_OSTIME_HPP
