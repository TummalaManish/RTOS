/**
 * @file      IQueueSender.hpp
 * @author    Tummala Manish (tummalamanish@gmail.com)
 * @brief     Interface for the receiver to receive over a queue.
 * @version   0.1
 * @date      2020-12-08
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef IQUEUE_SENDER_HPP
#define IQUEUE_SENDER_HPP

#include "rtos_types.hpp"

namespace RTOS {

/**
 * @brief Interface class for sending over a queue.
 */
class IQueueSender {
public:
  virtual ~IQueueSender() = default;

  /**
   * @brief   Places the item at the front of the queue.
   *
   *          Call to this method block's the calling thread until space is
   * available indefinitely.
   *
   * @param   pv_item_to_queue pointer to the object that has to be queued.
   */
  virtual void enqueue_to_front(const void *pv_item_to_queue) = 0;

  /**
   * @brief   Places the item at the front of the queue.
   *
   *          Call to this method block's the calling thread until space is
   * available over the queue or the time-out expires. Whichever is the earlier.
   *
   * @param   pv_item_to_queue pointer to the object that has to be queued.
   * @param   wait_time Time for which the calling thread has to be blocked for
   * queue space to be available.
   * @return  RET_STA_E Returns eRTOSSuccess if an item is received before the
   * time-out else eRTOSFailure.
   */
  virtual RET_STA_E enqueue_to_front(const void *pv_item_to_queue,
                                     delay_t wait_time) = 0;

  /**
   * @brief   Places the item at the back of the queue.
   *
   *          Call to this method block's the calling thread until space is
   * available over the queue or the time-out expires. Whichever is the earlier.
   *
   * @param   pv_item_to_queue pointer to the object that has to be queued.
   * @param   wait_time Time for which the calling thread has to be blocked for
   * queue space to be available.
   * @return  RET_STA_E Returns eRTOSSuccess if an item is received before the
   * time-out else eRTOSFailure.
   */
  virtual RET_STA_E enqueue(const void *pv_item_to_queue,
                            delay_t wait_time) = 0;

  /**
   * @brief   Places the item at the back of the queue.
   *
   *          Call to this method block's the calling thread until space is
   * available indefinitely.
   *
   * @param   pv_item_to_queue pointer to the object that has to be queued.
   */
  virtual void enqueue(const void *pv_item_to_queue) = 0;
};
} // namespace RTOS

#endif // IQUEUE_SENDER_HPP
