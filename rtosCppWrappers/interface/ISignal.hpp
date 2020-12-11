/**
 * @file        ISignal.hpp
 * @author      Tummala Manish (manish.tummala@gmail.com)
 * @brief       Implements the interafce class for the signals.
 * @version     0.1
 * @date        2020-09-15
 *
 * @copyright   Copyright (c) 2020
 *
 */

#ifndef RTOS_ISIGNAL_HPP
#define RTOS_ISIGNAL_HPP

#include "rtos_types.hpp"

/**
 * @brief Interface to the rtos signals. This uses the Notifications in the case
 * of FreeRTOS.
 */
namespace RTOS {
class ISignal {
public:
  /**
   * @brief   Different notification action types.
   */
  enum class notify_type_e {
    eNoAction =
        eNoAction, /* Notify the task without updating its notify value. */
    eSetBits = eSetBits,     /* Set bits in the task's notification value.*/
    eIncrement = eIncrement, /* Increment the task's notification value. */
    eSetValueWithOverwrite =
        eSetValueWithOverwrite, /* Set the task's notification value to a
                                 * specific value even if the* previous value
                                 * has not yet been read by the task. */
    eSetValueWithoutOverwrite =
        eSetValueWithoutOverwrite /* Set the task's notification value if the
                                   * previous value has been read by the task.
                                   */
  };
  using NTF_TYP_E = notify_type_e;

  virtual ~ISignal() = default;
  /**
   * @brief   Sets the signal bits specified in the argument.
   *          You can use the RTOS::Thread::SIG_BIT() helper function.
   *
   * @param   BITS_TO_SET 32 bit value that has the required bits set.
   */
  virtual void signal_on_bits(uint32_t bitsToSet) = 0;

  /**
   * @brief   Post the value to the thread with an over write.
   *
   * @param   valueToSend 32-bit value that contains the message.
   */
  virtual void send_value_with_over_write(uint32_t valueToSend) = 0;

  /**
   * @brief   Posts the value to the thread with out an over write.
   *
   * @param   valueToSend 32-bit value that contains the message.
   * @return  eRTOSFailure if the send was not possible because of a pending
   * notification else eRTOSSuccess.
   */
  virtual RET_STA_E send_value_with_no_over_write(uint32_t valueToSend) = 0;

  /**
   * @brief   Used to notify the thread that is being operated on.
   *
   * @param   notifyValue - Value used as a notification to the thread.
   * @param   actionType - Type of notification(changes the notification
   * register).
   * @return  eRTOSSuccess is returned if the notification has been sent to the
   * thread.
   */
  virtual RET_STA_E notify(notify_value_t notifyValue,
                           NTF_TYP_E actionType) = 0;
};
} // namespace RTOS

#endif // closes RTOS_ISIGNAL_HPP