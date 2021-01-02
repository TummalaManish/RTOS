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

#include "IOSTime.hpp"

namespace RTOS{

/**
 * @brief Date time class to retrive date and time of the system.
 */
class DateTimeOS : public IOSTime {
public:
  /*------------------------ Interface for Date time -------------------------*/
  os_time_t get_ostime() override;
  void get_ostime(os_time_t &rToHoldTime) override;
  void set_ostime(os_time_t &timeToSet) override;

protected:
  static void ker_get_ostime(os_time_t & refToDateTime);
  static void ker_set_ostime(os_time_t const& refToDateTime);
};
}
#endif // RTOS_CPP_WRAPPER_OSTIME_HPP
