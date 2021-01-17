/**
 * @file      Time64.hpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Implementation of the 64-bit time.
 * @version   0.1
 * @date      17-01-2021
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef RTOS_CPP_WRAPPER_TIME64_HPP
#define RTOS_CPP_WRAPPER_TIME64_HPP

#include "ITime64.hpp"

namespace RTOS {

class Time64 : public ITime64 {
  /*Note: I don't think we need any object specific parameters for this class.*/
public:
  Time64() = default;
  ~Time64() override = default;

  /*----------------- Interface Implementation for the ITime64 ---------------*/
  os_time_t get_time64() const override;
  void get_time64(os_time_t &msSinceEpoch) const override;
  void set_time64(os_time_t &msSinceEpoch) const override;
};
} // namespace RTOS

#endif // RTOS_CPP_WRAPPER_TIME64_HPP
