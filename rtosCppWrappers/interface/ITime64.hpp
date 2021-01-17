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
