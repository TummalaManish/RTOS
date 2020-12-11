/**
 * @file      IQueueReceiver.hpp
 * @author    TummalaManish (thumalamanish@gmail.com)
 * @brief     Interface for a receiver to receive over a queue.
 * @version   0.1
 * @date      2020-12-08
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef IQUEUE_RECEIVER_HPP
#define IQUEUE_RECEIVER_HPP

#include "rtos_types.hpp"

namespace RTOS {

/**
 * @brief Interface class for receiving over a queue.
 */
class IQueueReceiver {
  public:
    virtual ~IQueueReceiver() = default;

      /**
   * @brief   Receives the value from the queue.
   *
   *          Call to this method blocks the thread till the specified time-out
   * is received or a value is available on the queue. Whichever is the earlier.
   *
   * @param   pv_buffer buffer for the item to be received.
   * @param   wait_time time for the thread to wait for the item over queue.
   * @return  RET_STA_E Returns eRTOSSuccess if an item is received before the
   * time-out else eRTOSFailure.
   */
  virtual RET_STA_E dequeue(void *pv_buffer, delay_t wait_time) = 0;

  /**
   * @brief   Receives the value from the queue.
   *
   *          Call to this method blocks the thread indefinitely until a value
   * is available on the queue to be received.
   *
   * @param   pv_buffer buffer for the item to be received.
   */
  virtual void dequeue(void *pv_buffer) = 0;

  /**
   * @brief   Just gets the item from queue without removing the item from the
   * queue.
   *
   *          The thread will be in blocked state till a value is posted to the
   * queue. Else, the wait time is timed-out. Whichever, is the earlier.
   *
   * @param   pv_buffer Pointer to the memory that'll be used for holding the
   * item from the queue.
   * @param   wait_time Time-out for the thread to be in blocked state to
   * receive the message.
   * @return  RET_STA_E Returns eRTOSSuccess if an item is received before
   * time-out else eRTOSFailure.
   */
  virtual RET_STA_E peek(void *pv_buffer, delay_t wait_time) = 0;

  /**
   * @brief   Just gets the item from queue without removing the item from the
   * queue.
   *
   *          This function is same as the method: peek except that this
   * method blocks the called thread indefinitely.
   *
   * @param   buffer Buffer for the item to be copied from the queue.
   */
  virtual void peek(void *buffer) = 0;
};
} // namespace RTOS
#endif // IQUEUE_RECEIVER_HPP
