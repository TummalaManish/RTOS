/**
 * @file        Task_Creation.cpp
 * @author      Manish Tummala (manish.tummala@gmail.com)
 * @brief       Tests the Thread signaling.
 * @version     0.1
 * @date        2020-08-17
 *
 * @copyright Copyright (c) 2020
 *
 */

// IO
#include <iostream>

// RTOS
#include "Thread.hpp"

// APP Section:
class ThreadM : public RTOS::Thread {

  Thread &m_slaveThread;
  const uint32_t VALUE_FOR_MESSAGE = 0xf0ff0fffUL;

  /*Inherited functions*/
  [[noreturn]] void run() override {
    m_slaveThread.join();
    for (;;) {
      // Sending correct value with over write and no wait time.
      m_slaveThread.send_value_with_over_write(VALUE_FOR_MESSAGE);

      // Sending correct value with no over write when value is pending.
      RTOS::RET_STA_E msg_stat =
          m_slaveThread.send_value_with_no_over_write(VALUE_FOR_MESSAGE);
      if (msg_stat == RTOS::RET_STA_E::eRTOSFailure)
        std::cout << "Expected failure as there is a value waiting to be read"
                  << std::endl;
      else
        std::cout << "Expected a failure but didn't occur." << std::endl;

      // Waiting for the salve to process the Value sent.
      delay_ms(400);

      // Sending correct value with no over write when value is not pending.
      msg_stat = m_slaveThread.send_value_with_no_over_write(VALUE_FOR_MESSAGE);
      if (msg_stat == RTOS::RET_STA_E::eRTOSSuccess)
        std::cout << "Expected success as there is no value waiting to be read"
                  << std::endl;
      else
        std::cout << "Expected no failure but it occurred." << std::endl;
      // Waiting for the salve to process the Value sent.
      delay_ms(400);

      // Sending the incorrect value to the slave.
      m_slaveThread.send_value_with_over_write(VALUE_FOR_MESSAGE + 2);
      // Waiting for the salve to process the Value sent.
      delay_ms(400);

      // Testing the time out.
      delay_ms(704);

      // End the test.
      std::cout << "Ending the test.";
      end_scheduler();
    }
  }

  RTOS::return_status_e thread_delete() override {
    return RTOS::return_status_e::eRTOSSuccess;
  }

public:
  explicit ThreadM(Thread &slaveThread)
      : m_slaveThread(slaveThread), Thread("Master Thread", 5, 400) {}
};

class ThreadS : public RTOS::Thread {

  const uint32_t VALUE_FOR_MESSAGE = 0xf0ff0fffUL;

  /*Inherited functions*/
  [[noreturn]] void run() override {
    for (;;) {
      RTOS::Thread::NTF_VALUE_S signal_stat = Thread::wait_for_value(700);
      if (signal_stat.timed_out)
        std::cout << "Message wait time timed out" << std::endl;
      else {
        if (signal_stat.received_value == VALUE_FOR_MESSAGE) {
          std::cout << "Correct value is received in time: " << std::hex
                    << static_cast<uint32_t>(signal_stat.received_value)
                    << std::endl;
        } else {
          std::cout << "In-correct value is received in time: " << std::hex
                    << static_cast<uint32_t>(signal_stat.received_value)
                    << std::endl;
        }
      }
    }
  }

  RTOS::return_status_e thread_delete() override {
    return RTOS::return_status_e::eRTOSSuccess;
  }

public:
  explicit ThreadS() : Thread("Slave Thread", 4, 400) {}
};

int main() {
  ThreadS salve_thread;
  ThreadM Master_thread(salve_thread);
  Master_thread.join();
}

void vAssertCalled(unsigned long ulLine, const char *const pcFileName) {
  printf("ASSERT: %s : %d\n", pcFileName, (int)ulLine);
  while (1)
    ;
}