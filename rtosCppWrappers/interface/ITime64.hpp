/**
 * @file      ITime64.hpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Interface for the 64 bit-time.
 * @version   0.1
 * @date      17-01-2021
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef RTOS_CPP_WRAPPER_ITIME64_HPP
#define RTOS_CPP_WRAPPER_ITIME64_HPP

#include "rtos_types.hpp"

namespace RTOS {

class ITime64 {
public:

  /*------------------------ 64-bit time constant ----------------------------*/
  static uint32_t const MS_IN_SEC  = 1000;
  static uint32_t const SEC_IN_MIN = 60;
  static uint32_t const MS_IN_MIN  = SEC_IN_MIN * MS_IN_SEC;
  static uint32_t const MIN_IN_HR  = 60;
  static uint32_t const MS_IN_HR   = MIN_IN_HR * MS_IN_MIN;
  static uint32_t const HRS_IN_DAY = 24;
  static uint32_t const MS_IN_DAY  = 24 * MS_IN_HR;

  virtual ~ITime64() = default;

  /**
   * @brief returns the milliseconds since epoch.
   * @return 64-bit system time.
   */
  virtual RTOS::os_time_t get_time64() const = 0;

  /**
   * @brief returns the milliseconds since epoch.
   * @param msSinceEpoch[in] 64-bit system time.
   */
  virtual void get_time64(RTOS::os_time_t &msSinceEpoch) const = 0;

  /**
   * @brief Sets 64-bit system time.
   * @param msSinceEpoch[in] new timeti be set as s system time.
   */
  virtual void set_time64(RTOS::os_time_t &msSinceEpoch) const = 0;

  /* NOTE: Should we have some api that'll check the validity go the time? */
};

} // namespace RTOS

#endif // RTOS_CPP_WRAPPER_ITIME64_HPP
