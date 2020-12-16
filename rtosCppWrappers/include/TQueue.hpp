/**
 * @file        TQueue.hpp
 * @author      Manish Tummala (manish.tummala@gmail.com)
 * @brief       Implements the templated queue.
 * @version     0.1
 * @date        2020-09-26
 *
 * @copyright   Copyright (c) 2020
 *
 */

#ifndef TQUEUE_RTOS_HPP
#define TQUEUE_RTOS_HPP

#include "IQueueReceiver.hpp"
#include "IQueueSender.hpp"

#include "MemoryManager.hpp"

namespace RTOS {

/**
 * @brief       Implements the queue wrapper.
 *
 * @tparam T    Type of the queue item.
 * @tparam N    Number of queue items to hold.
 */
template <typename T, size_t N>
class TQueue : public IQueueSender, public IQueueReceiver {

  /*---------------------- Non-static data members -------------------------*/
  que_handle_t m_pHandle; /**< Holds the pointer to the queue handle */
  queue_cb_t
      m_pQueueCB; /**< Holds pointer buffer for the queue control block     */
  T *m_pBuffer;   /**< Holds pointer buffer for the entire queue            */

public:
  /**
   * @brief Construct a new Queue object.
   */
  TQueue() : m_pHandle(nullptr), m_pQueueCB(nullptr), m_pBuffer(nullptr) {
    if (MemoryManager::get_Instance().get_CB(&m_pQueueCB) ==
            eMemAllocationSuccess &&
        MemoryManager::get_Instance().get_block(
            (void **)(&m_pBuffer), N * sizeof(T)) == eMemAllocationSuccess)
      m_pHandle = xQueueCreateStatic(
          N, sizeof(T), reinterpret_cast<uint8_t *>(m_pBuffer), m_pQueueCB);
    else
      debug_break;
  }

  /* destructor */
  ~TQueue() override {
    vQueueDelete(m_pHandle);
    MemoryManager::release_CB(m_pQueueCB);
    MemoryManager::release_block(m_pBuffer);
  }

  /*-------------------------- Inherited methods ---------------------------*/
  RET_STA_E enqueue_to_front(const void *const pv_item_to_queue,
                             delay_t wait_time) override {
    auto ret_val = xQueueSendToFront(m_pHandle, pv_item_to_queue,
                                     pdMS_TO_TICKS(wait_time));
    return ret_val == pdTRUE ? RET_STA_E::eRTOSSuccess
                             : RET_STA_E::eRTOSFailure;
  }

  void enqueue_to_front(const void *const pv_item_to_queue) override {
    (void)enqueue_to_front(pv_item_to_queue, wait_forever);
  }

  RET_STA_E enqueue(const void *const pv_item_to_queue,
                    delay_t wait_time) override {
    auto ret_val =
        xQueueSendToBack(m_pHandle, pv_item_to_queue, pdMS_TO_TICKS(wait_time));
    return ret_val == pdTRUE ? RET_STA_E::eRTOSSuccess
                             : RET_STA_E::eRTOSFailure;
  }

  void enqueue(const void *const pv_item_to_queue) override {
    (void)enqueue(pv_item_to_queue, wait_forever);
  }

  RET_STA_E dequeue(void *const pv_buffer, delay_t wait_time) override {
    auto ret_val =
        xQueueReceive(m_pHandle, pv_buffer, pdMS_TO_TICKS(wait_time));
    return ret_val == pdTRUE ? RET_STA_E::eRTOSSuccess
                             : RET_STA_E::eRTOSFailure;
  }

  void dequeue(void *const pv_buffer) override {
    (void)dequeue(pv_buffer, pdMS_TO_TICKS(wait_forever));
  }

  RET_STA_E peek(void *const pv_buffer, delay_t wait_time) override {
    auto ret_val = xQueuePeek(m_pHandle, pv_buffer, pdMS_TO_TICKS(wait_time));
    return ret_val == pdTRUE ? RET_STA_E::eRTOSSuccess
                             : RET_STA_E::eRTOSFailure;
  }

  void peek(void *const buffer) override {
    (void)peek(buffer, pdMS_TO_TICKS(wait_forever));
  }
};
} // namespace RTOS
#endif // TQUEUE_RTOS_HPP.
