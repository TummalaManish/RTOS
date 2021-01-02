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
#ifndef RTOS_CPP_WRAPPER_DATETIME_HPP
#define RTOS_CPP_WRAPPER_DATETIME_HPP

#include "IDateTime.hpp"

namespace RTOS{

class DateTime: public IDateTime{
  bool timeLock; /*<< Lock for the system time */
public:
  /*------------------------ Interface for Date time -------------------------*/
  os_time_t get_datetime() override;
  void get_datetime(os_time_t &rToHoldTime) override;
  void set_datetime(os_time_t &timeToSet) override;

protected:
  static void ker_get_datetime(os_time_t & refToDateTime);
  static void ker_set_datetime(os_time_t const& refToDateTime);
};
}
#endif // RTOS_CPP_WRAPPER_DATETIME_HPP
