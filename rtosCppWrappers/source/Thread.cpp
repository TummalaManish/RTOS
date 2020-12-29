/**
 * @file        Thread.cpp
 * @author      Manish Tummala(manish.tummala@gmail.com)
 * @brief       Thread implementation.
 * @version     0.1
 * @date        2020-07-23
 *
 * @copyright   Copyright (c) 2020
 *
 */

#include "Thread.hpp"
#include "MemoryManager.hpp"

namespace RTOS {

/*Structure to pass the TCB details*/
struct TCB_pass_s {
  stack_t m_pStack;
  stack_size_t m_stackSize;
  priority_t m_threadPrio;
  char m_threadName[configMAX_TASK_NAME_LEN]{};

  TCB_pass_s() = delete;
  TCB_pass_s(struct TCB_pass_s const &src)
      : m_threadPrio(src.m_threadPrio), m_pStack(src.m_pStack),
        m_stackSize(src.m_stackSize), m_threadName("") {
    for (auto index = static_cast<uint8_t>(0); index < configMAX_TASK_NAME_LEN;
         ++index) {
      if (src.m_threadName[index] != static_cast<char>(0x00)) {
        m_threadName[index] = src.m_threadName[index];
      } else {
        // End of the character reached.
        m_threadName[index] = static_cast<char>(0x00);
        break;
      }
    }
  }

  void fill_tcb_from_args(const name_t thread_name,
                          const priority_t thread_priority,
                          const stack_size_t thread_stack_size,
                          size_t* const stack) {
    m_pStack = stack;
    m_stackSize = thread_stack_size;
    m_threadPrio = thread_priority;

    for (size_t index = static_cast<size_t>(0); index < configMAX_TASK_NAME_LEN;
         ++index) {
      if (thread_name[index] != static_cast<char>(0x00)) {
        m_threadName[index] = thread_name[index];
      } else {
        // End of the thread-name reached.
        m_threadName[index] = static_cast<char>(0x00);
        break;
      }
    }
  }
};

using TCB_PASS_STR = struct TCB_pass_s;

/*--------- static value initialization ---------*/
id_t Thread::m_sThreadCount = 0;
/*----------------------------------------------*/

RTOS::Thread::Thread(const name_t thread_name, const priority_t thread_priority,
                     const stack_size_t thread_stack_size, const id_t thread_id)
    : m_pStack(nullptr), m_pTaskCb(nullptr), m_pHandle(nullptr) {
  bool result = ((MemoryManager::get_Instance().get_CB(&m_pTaskCb) ==
                  eMemoryResult::eMemAllocationSuccess));
  result &=
      ((MemoryManager::get_Instance().get_stack(m_pStack, thread_stack_size) ==
        eMemoryResult::eMemAllocationSuccess));

  if (result) {
    m_threadStatus = THR_STA_E::eThreadNotStarted;

    // Casting TCB to a intermediate type to pass task parameters.
    (*(reinterpret_cast<TCB_PASS_STR *>(m_pTaskCb)))
        .fill_tcb_from_args(thread_name, thread_priority, thread_stack_size,
                            m_pStack);

    // Thread ID related changes.
    m_sThreadCount++;
    if (thread_id != 0) {
      m_threadId = thread_id;
    } else {
      m_threadId = m_sThreadCount;
    }
  } else {

    m_threadStatus = THR_STA_E::eMemoryAllocationFailed;
    // TODO: Insert a debug-break if such functionality is required.
  }
}

Thread::~Thread() {
  if (is_scheduler_running()) {
    vTaskDelete(m_pHandle);
  }
  // Memory for the task has been provided from the heap hence the clean up.
  MemoryManager::release_CB(m_pTaskCb);
  MemoryManager::release_stack(m_pStack);
}

void Thread::start(void *super) {
  auto *this_obj = static_cast<Thread *>(super);
  if (this_obj->get_status() == THR_STA_E::eThreadNotStarted) {
    this_obj->m_threadStatus = THR_STA_E::eThreadStarted;
    this_obj->run();

    /*--------- Execution should never come here -----------*/
    // TODO: Invalid thread exit. The thread will be cleaned up and this has
    //      to be logged. Once the logger is implemented.
    debug_break;
  } else {
    debug_break;
  }
}

bool Thread::is_scheduler_running() {
  return xTaskGetSchedulerState() == taskSCHEDULER_RUNNING;
}

void Thread::yield() {
  // This macro will be populated by the port layer.
  taskYIELD();
}

void Thread::start_scheduler() {
  if (!(is_scheduler_running())) {
    vTaskStartScheduler();
  }
}

RET_STA_E Thread::wait_for_notification(uint32_t entryClearMask,
                                        uint32_t exitClearMask, delay_t msDelay,
                                        uint32_t *pNotificationValue) {
  auto ret_val = xTaskNotifyWait(entryClearMask, exitClearMask,
                                 pNotificationValue, pdMS_TO_TICKS(msDelay));
  return ret_val == pdTRUE ? RET_STA_E::eRTOSSuccess : RET_STA_E::eRTOSFailure;
}

Thread::SIG_RET_VAL Thread::wait_for_signal_on_bits(uint32_t signalMask,
                                                    delay_t blockTime) {
  auto notification_value = static_cast<uint32_t>(0x00);
  Thread::SIG_RET_VAL ret_value;
  auto time_out_status = xTaskNotifyWait(
      signalMask, signalMask, &notification_value, pdMS_TO_TICKS(blockTime));
  uint32_t received_signal = notification_value & signalMask;
  if (time_out_status == pdPASS) {
    if (received_signal == signalMask) {
      ret_value = Thread::SIG_RET_VAL::eExpectedSignalReceived;
    } else {
      ret_value = Thread::SIG_RET_VAL::eUnexpectedSignalReceived;
    }
  } else {
    ret_value = Thread::SIG_RET_VAL::eTimeOut;
  }
  return ret_value;
}

Thread::SIG_RET_VAL
Thread::wait_for_signal_on_bits(uint32_t signalMask) {
  return wait_for_signal_on_bits(signalMask, wait_forever);
}

Thread::NTF_VALUE_S Thread::wait_for_value(delay_t blockTime) {
  Thread::NTF_VALUE_S ret_value = {true, static_cast<uint32_t>(0x00)};
  auto time_out_status = xTaskNotifyWait(
      static_cast<uint32_t>(0x00), static_cast<uint32_t>(0xFFFFFFFFFFFFFFFF),
      &(ret_value.received_value), pdMS_TO_TICKS(blockTime));
  if (time_out_status == pdPASS)
    ret_value.timed_out = false;
  else
    ret_value.timed_out = true;
  return ret_value;
}

Thread::NTF_VALUE_S Thread::wait_for_value() {
  return wait_for_value(wait_forever);
}

uint32_t Thread::SIG_BIT(const unsigned int value) {
  return ((static_cast<uint32_t>(0x01U)) << value);
}

void Thread::delay_ms(delay_t delay) {
  vTaskDelay(static_cast<TickType_t>(pdMS_TO_TICKS(delay)));
}

void Thread::end_scheduler() { vTaskEndScheduler(); }

priority_t Thread::get_priority() const {
  return static_cast<priority_t>(uxTaskPriorityGet(m_pHandle));
}

// note: partially implemented.
return_status_e Thread::set_priority(priority_t new_priority) {
  // TODO: This is a bit complicated function has to be implement yet.
  vTaskPrioritySet(m_pHandle, new_priority);
  return RET_STA_E::eRTOSSuccess;
}

char const *Thread::get_name() const {
  return static_cast<const char *>(pcTaskGetName(m_pHandle));
}

status_e Thread::get_status() const { return m_threadStatus; }

void Thread::suspend() const { vTaskSuspend(m_pHandle); }

void Thread::resume() const { vTaskResume(m_pHandle); }

void Thread::join() {
  // Temp Variable to pass the parameters.
  TCB_PASS_STR dest(*(reinterpret_cast<TCB_PASS_STR *>(m_pTaskCb)));

  m_pHandle = xTaskCreateStatic(start, dest.m_threadName, dest.m_stackSize,
                                (void *const)(this), dest.m_threadPrio,
                                dest.m_pStack, m_pTaskCb);
  if (m_pHandle != nullptr &&
      m_threadStatus != THR_STA_E::eMemoryAllocationFailed) {
    start_scheduler();
  } else {
    m_threadStatus = THR_STA_E::eThreadCreationFailed;
  }
}

bool Thread::is_thread_created() const {
  return static_cast<bool>(get_status() == THR_STA_E::eThreadStarted
                               ? RET_STA_E::eRTOSSuccess
                               : RET_STA_E::eRTOSFailure);
}

id_t Thread::get_id() const { return m_threadId; }

RET_STA_E Thread::notify(notify_value_t notifyValue, NTF_TYP_E actionType) {
  base_t ret_val = xTaskNotify(m_pHandle, notifyValue,
                               static_cast<eNotifyAction>(actionType));
  if (ret_val == pdPASS) {
    return RET_STA_E::eRTOSSuccess;
  } else {
    return RET_STA_E::eRTOSFailure;
  }
}

void Thread::signal_on_bits(uint32_t bitsToSet) {
  (void)xTaskNotify(m_pHandle, bitsToSet,
                    static_cast<eNotifyAction>(NTF_TYP_E::eSetBits));
}

void Thread::send_value_with_over_write(uint32_t valueToSend) {
  (void)xTaskNotify(
      m_pHandle, valueToSend,
      static_cast<eNotifyAction>(NTF_TYP_E::eSetValueWithOverwrite));
}

RET_STA_E Thread::send_value_with_no_over_write(uint32_t valueToSend) {
  base_t ret_value = xTaskNotify(
      m_pHandle, valueToSend,
      static_cast<eNotifyAction>(NTF_TYP_E::eSetValueWithoutOverwrite));

  return ret_value == pdPASS ? RET_STA_E::eRTOSSuccess
                             : RET_STA_E::eRTOSFailure;
}

RET_STA_E Thread::thread_delete() { return RET_STA_E::eRTOSSuccess; }

} // namespace RTOS

extern "C" void
vApplicationGetIdleTaskMemory(StaticTask_t **const ppxIdleTaskTCBBuffer,
                              StackType_t **const ppxIdleTaskStackBuffer,
                              uint32_t *const pulIdleTaskStackSize) {
  constexpr unsigned int stack_size = 50;
  static StaticTask_t l_tcb;
  static StackType_t l_stack[stack_size];
  *pulIdleTaskStackSize = stack_size;
  *ppxIdleTaskStackBuffer = reinterpret_cast<StackType_t *>(&l_stack);
  *ppxIdleTaskTCBBuffer = &l_tcb;
}
