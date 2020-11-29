/**
 * @file        Queue.cpp
 * @author      Manish Tummala (manish.tummala@gmail.com)
 * @brief       Implements the queue object.
 * @version     0.1
 * @date        2020-09-08
 *
 * @copyright   Copyright (c) 2020
 *
 */

#include "Queue.hpp"
#include "MemoryManager.hpp"

namespace RTOS {

Queue::Queue(const base_t queue_length, const base_t item_length) {
  m_pHandle = nullptr;
  m_pQueueCB = nullptr;
  m_pBuffer = nullptr;
  if (MemoryManager::get_Instance().get_CB(&m_pQueueCB) ==
          eMemAllocationSuccess &&
      MemoryManager::get_Instance().get_block((void **)(&m_pBuffer),
                                              queue_length * item_length) ==
          eMemAllocationSuccess)
    m_pHandle =
        xQueueCreateStatic(queue_length, item_length, m_pBuffer, m_pQueueCB);
  else
    debug_break;
}

Queue::~Queue() {
  vQueueDelete(m_pHandle);
  MemoryManager::release_CB(m_pQueueCB);
  MemoryManager::release_block(m_pBuffer);
}

RET_STA_E Queue::place_item_at_front(const void *const pv_item_to_queue,
                                     delay_t wait_time) {
  auto ret_val =
      xQueueSendToFront(m_pHandle, pv_item_to_queue, pdMS_TO_TICKS(wait_time));
  return ret_val == pdTRUE ? RET_STA_E::eRTOSSuccess : RET_STA_E::eRTOSFailure;
}

void Queue::place_item_at_front_blocked(const void *const pv_item_to_queue) {
  (void)place_item_at_front(pv_item_to_queue, wait_forever);
}

RET_STA_E Queue::place_item_at_back(const void *const pv_item_to_queue,
                                    delay_t wait_time) {
  auto ret_val =
      xQueueSendToBack(m_pHandle, pv_item_to_queue, pdMS_TO_TICKS(wait_time));
  return ret_val == pdTRUE ? RET_STA_E::eRTOSSuccess : RET_STA_E::eRTOSFailure;
}

void Queue::place_item_at_back_blocked(const void *const pv_item_to_queue) {
  (void)place_item_at_back(pv_item_to_queue, wait_forever);
}

RET_STA_E Queue::get_item(void *const pv_buffer, delay_t wait_time) {
  auto ret_val = xQueueReceive(m_pHandle, pv_buffer, pdMS_TO_TICKS(wait_time));
  return ret_val == pdTRUE ? RET_STA_E::eRTOSSuccess : RET_STA_E::eRTOSFailure;
}

void Queue::get_item_blocked(void *const pv_buffer) {
  (void)get_item(pv_buffer, pdMS_TO_TICKS(wait_forever));
}

RET_STA_E Queue::look_at_item(void *const pv_buffer, delay_t wait_time) {
  auto ret_val = xQueuePeek(m_pHandle, pv_buffer, pdMS_TO_TICKS(wait_time));
  return ret_val == pdTRUE ? RET_STA_E::eRTOSSuccess : RET_STA_E::eRTOSFailure;
}

void Queue::look_at_item_blocked(void *const buffer) {
  (void)look_at_item(buffer, pdMS_TO_TICKS(wait_forever));
}

} // namespace RTOS
