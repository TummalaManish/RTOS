/**
 * @file        Queue.cpp
 * @author      Manish Tummala (manish.tummala@gmail.com)
 * @brief       Implements definitions for the queue object.
 * @version     0.1
 * @date        2020-09-08
 *
 * @copyright   Copyright (c) 2020
 *
 */

#ifndef RTOS_QUEUE_HPP
#define RTOS_QUEUE_HPP

#include "IQueue.hpp"

namespace RTOS {

class Queue : public IQueue {

  /*---------------------- Non-static data members -------------------------*/
  que_handle_t m_pHandle; /**< Holds the pointer to the queue handle */
  queue_cb_t
      m_pQueueCB; /**< Holds pointer buffer for the queue control block     */
  uint8_t *m_pBuffer; /**< Holds pointer buffer for the entire queue */

public:
  /**
   * @brief   Construct a new Queue object.
   *
   * @param   queue_length The length requirement for the queue object.
   * @param   item_length The number of bytes each unit of queue takes.
   */
  Queue(base_t queue_length, base_t item_length);

  /* destructor */
  virtual ~Queue() override;
  /*-------------------------- Inherited methods ---------------------------*/
  RET_STA_E place_item_at_front(const void *pv_item_to_queue,
                                delay_t wait_time) override;
  void place_item_at_front_blocked(const void *pv_item_to_queue) override;
  RET_STA_E place_item_at_back(const void *pv_item_to_queue,
                               delay_t wait_time) override;
  void place_item_at_back_blocked(const void *pv_item_to_queue) override;
  RET_STA_E get_item(void *pv_buffer, delay_t wait_time) override;
  void get_item_blocked(void *pv_buffer) override;
  RET_STA_E look_at_item(void *pv_buffer, delay_t wait_time) override;
  void look_at_item_blocked(void *buffer) override;
};
} // namespace RTOS
#endif // RTOS_THREAD_HPP
