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

/**
 * *Why_this_exists: This is a intermediate structure that helps us to pass the
 *                   thread-creation related arguments with out any extra
 *                   memory usage.
 * *How_it_works   : The allocated thread TCB is reinterpreted as the below
 *                   structure and the structure is filled. Which then while
 *                   joining to the kernel is reinterpreted and is passed as
 *                   arguments.
 */
/**@brief: Invisible structure to pass the TCB details*/
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
                          const stack_t stack) {
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

  /* Try and get a TCB block from the RTOS memory region successfully. */
  bool result = ((MemoryManager::get_Instance().get_CB(&m_pTaskCb) ==
                  eMemoryResult::eMemAllocationSuccess));
  /* Try and get the stack from thr RTOS memory region successfully. */
  result &=
      ((MemoryManager::get_Instance().get_stack(m_pStack, thread_stack_size) ==
        eMemoryResult::eMemAllocationSuccess));

  /* If both the allocations are successful then fill the thread variables. */
  if (result) {
    m_threadStatus = THR_STA_E::eNotStarted;

    /* Casting TCB to a intermediate type to pass task parameters. */
    (*(reinterpret_cast<TCB_PASS_STR *>(m_pTaskCb)))
        .fill_tcb_from_args(thread_name, thread_priority, thread_stack_size,
                            m_pStack);

    /* TODO: Write the feature for thread ID */
    m_sThreadCount++;
    if (thread_id != 0) {
      m_threadId = thread_id;
    } else {
      m_threadId = m_sThreadCount;
    }

    /* If the creation has failed release the TCB if allocated. */
  } else {

    /* Fill the thread status. */
    m_threadStatus = THR_STA_E::eMemoryAllocationFailed;

    /* Check if TCB is allocated. */
    if (m_pTaskCb != nullptr) {
      /* Release memory for other usages. */
      MemoryManager::release_CB(m_pTaskCb);
    }
    // TODO: Insert a debug-break if such functionality is required.
  }
}

Thread::~Thread() {
  if (is_scheduler_running()) {
    vTaskDelete(m_pHandle);
  }
  /* Release the resources block by the thread. */
  MemoryManager::release_CB(m_pTaskCb);
  MemoryManager::release_stack(m_pStack);
}

void Thread::start(void *super) {
  auto *this_obj = static_cast<Thread *>(super);

  /* Verify if the thread could be run. */
  if (this_obj->get_status() == THR_STA_E::eNotStarted) {

    /* Update the thread status. */
    this_obj->m_threadStatus = THR_STA_E::eStarted;
    this_obj->run();

    /*
     * This thread has completed it's execution. The thread either can be reset
     * or can be deleted freeing all the resources.
     */
    this_obj->m_threadStatus = THR_STA_E::eCompleted;

    /* Suspend the thread and unblock only if the task is reset. */
    delay_ms(wait_forever);
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
  /* Container to store the received notification. */
  auto notification_value = static_cast<uint32_t>(0x00);
  Thread::SIG_RET_VAL ret_value;

  /* Wait until the timeout expires or a notification is received. */
  auto time_out_status = xTaskNotifyWait(
      signalMask, signalMask, &notification_value, pdMS_TO_TICKS(blockTime));

  /* Clear unwanted bits of the received notification. */
  uint32_t received_signal = notification_value & signalMask;

  /* Check if the unblocking is due to timeout or received notification.*/
  if (time_out_status == pdPASS) {

    /* If received signal matches the expected signal then return. */
    if (received_signal == signalMask) {
      ret_value = Thread::SIG_RET_VAL::eExpectedSignalReceived;
    } else {
      ret_value = Thread::SIG_RET_VAL::eUnexpectedSignalReceived;
    }
  } else {
    /* Return time-out. */
    ret_value = Thread::SIG_RET_VAL::eTimeOut;
  }
  return ret_value;
}

Thread::SIG_RET_VAL Thread::wait_for_signal_on_bits(uint32_t signalMask) {
  return wait_for_signal_on_bits(signalMask, wait_forever);
}

Thread::NTF_VALUE_S Thread::wait_for_value(delay_t blockTime) {
  Thread::NTF_VALUE_S ret_value = {true, static_cast<uint32_t>(0x00)};

  /* Wait until the timeout expires or a value over notification is received. */
  auto time_out_status =
      xTaskNotifyWait(static_cast<uint32_t>(0x00), pdMS_TO_TICKS(wait_forever),
                      &(ret_value.received_value), pdMS_TO_TICKS(blockTime));

  /* Check if the unblocking is due to timeout or a value is received. */
  if (time_out_status == pdPASS) {
    ret_value.timed_out = false;
  } else {
    ret_value.timed_out = true;
  }

  /* Return the value with the status. */
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

void Thread::suspend() {

  /* Change the status of the thread before calling the api. */
  m_threadStatus = THR_STA_E::eSuspended;
  vTaskSuspend(m_pHandle);
}

void Thread::resume() {

  /* Check if the thread is suspended because it is completed. */
  if (m_threadStatus != THR_STA_E::eCompleted) {

    /* If the call is made from a ISR or Application and call relv. api. */
    if (xPortIsInsideInterrupt() == pdTRUE) {

      /* Check if a context switch is required. */
      auto YieldRequired = xTaskResumeFromISR(m_pHandle);
      m_threadStatus = THR_STA_E::eStarted;
      /* Perform a switch if required. */
      if (YieldRequired == pdTRUE) {
        yield();
      }
    }

    /* Not in an ISR so using normal flavour if the api. */
    else {
      vTaskResume(m_pHandle);
      m_threadStatus = THR_STA_E::eStarted;
    }
  }
}

void Thread::join() {
  // Temp Variable to pass the parameters.
  TCB_PASS_STR dest(*(reinterpret_cast<TCB_PASS_STR *>(m_pTaskCb)));

  /*Check if the memory required is allocated or not.*/
  if (m_threadStatus == THR_STA_E::eNotStarted) {
    /*If allocated try to create the task.*/
    m_pHandle = xTaskCreateStatic(start, dest.m_threadName, dest.m_stackSize,
                                  (void *const)(this), dest.m_threadPrio,
                                  dest.m_pStack, m_pTaskCb);
    if (m_pHandle != nullptr) {
      /*If thread creation is successful start the scheduler.*/
      start_scheduler();
    } else {
      /*Else if thread creation has filed fill the status and exit.*/
      m_threadStatus = THR_STA_E::eCreationFailed;
    }
  }
}

bool Thread::is_thread_created() const {
  return static_cast<bool>(get_status() == THR_STA_E::eStarted
                               ? RET_STA_E::eRTOSSuccess
                               : RET_STA_E::eRTOSFailure);
}

id_t Thread::get_id() const { return m_threadId; }

RET_STA_E Thread::notify(notify_value_t notifyValue, NTF_TYP_E actionType) {
  base_t ret_val;

  /* Check if the method is called from a ISR. */
  if (xPortIsInsideInterrupt() == pdTRUE) {
    base_t isYieldRequired = 0U;
    ret_val = xTaskNotifyFromISR(m_pHandle, notifyValue,
                                 static_cast<eNotifyAction>(actionType),
                                 &isYieldRequired);
    /* Check if a context switch is required. */
    if (isYieldRequired == pdTRUE) {
      yield();
    }

  }
  /* Call is not from an ISR use non ISR flavour. */
  else {
    ret_val = xTaskNotify(m_pHandle, notifyValue,
                          static_cast<eNotifyAction>(actionType));
  }
  if (ret_val == pdPASS) {
    return RET_STA_E::eRTOSSuccess;
  } else {
    return RET_STA_E::eRTOSFailure;
  }
}

void Thread::signal_on_bits(uint32_t bitsToSet) {

  /* Check if the method is called from a ISR. */
  if (xPortIsInsideInterrupt() == pdTRUE) {
    base_t isYieldRequired = 0U;
    (void)xTaskNotifyFromISR(m_pHandle, bitsToSet,
                             static_cast<eNotifyAction>(NTF_TYP_E::eSetBits),
                             &isYieldRequired);
    /* Check if a context switch is required. */
    if (isYieldRequired == pdTRUE) {
      yield();
    }

  }
  /* Call is not from an ISR use non ISR flavour. */
  else {
    (void)xTaskNotify(m_pHandle, bitsToSet,
                      static_cast<eNotifyAction>(NTF_TYP_E::eSetBits));
  }
}

void Thread::send_value_with_over_write(uint32_t valueToSend) {

  /* Check if the method is called from a ISR. */
  if (xPortIsInsideInterrupt() == pdTRUE) {
    base_t isYieldRequired = 0U;
    (void)xTaskNotifyFromISR(
        m_pHandle, valueToSend,
        static_cast<eNotifyAction>(NTF_TYP_E::eSetValueWithOverwrite),
        &isYieldRequired);
    /* Check if a context switch is required. */
    if (isYieldRequired == pdTRUE) {
      yield();
    }
  }

  /* Call is not from an ISR use non ISR flavour. */
  else {
    (void)xTaskNotify(
        m_pHandle, valueToSend,
        static_cast<eNotifyAction>(NTF_TYP_E::eSetValueWithOverwrite));
  }
}

RET_STA_E Thread::send_value_with_no_over_write(uint32_t valueToSend) {
  base_t ret_value = 0U;

  /* Check if the method is called from a ISR. */
  if (xPortIsInsideInterrupt() == pdTRUE) {
    base_t isYieldRequired = 0U;
    ret_value = xTaskNotifyFromISR(
        m_pHandle, valueToSend,
        static_cast<eNotifyAction>(NTF_TYP_E::eSetValueWithoutOverwrite),
        &isYieldRequired);
    /* Check if a context switch is required. */
    if (isYieldRequired == pdTRUE) {
      yield();
    }
  }

  /* Call is not from an ISR use non ISR flavour. */
  else {
    ret_value = xTaskNotify(
        m_pHandle, valueToSend,
        static_cast<eNotifyAction>(NTF_TYP_E::eSetValueWithoutOverwrite));
  }

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
