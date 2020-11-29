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
#include <Thread.hpp>

// APP Section:
class ThreadM : public RTOS::Thread {

  IThread &m_slaveThread_thr;
  ISignal &m_slaveThread_sig;

  /*Inherited functions*/
  [[noreturn]] void run() override {
    m_slaveThread_thr.join();
    for (;;) {
      // Signal the thread directly with no block on bit-12.
      m_slaveThread_sig.signal_on_bits(SIG_BIT(12));
      // Give time for the slave to run its course.
      RTOS::Thread::delay_ms(100);
      // Signal the slave on the wrong signal bit.
      m_slaveThread_sig.signal_on_bits(SIG_BIT(13));
      // Wait for the slave signal to record a miss in the signal.
      RTOS::Thread::delay_ms(1000);
      std::cout << "Ending the test.";
      // End the scheduler.
      end_scheduler();
    }
  }

  RTOS::return_status_e thread_delete() override {
    return RTOS::return_status_e::eRTOSSuccess;
  }

public:
  explicit ThreadM(Thread &slaveThread)
      : m_slaveThread_thr(slaveThread), m_slaveThread_sig(slaveThread),
        Thread("Master Thread", 5, 400) {}
};

class ThreadS : public RTOS::Thread {

  [[noreturn]] void run() override {
    for (;;) {
      RTOS::Thread::SIG_RET_VAL signal_stat =
          Thread::wait_for_signal_on_bits(SIG_BIT(12), 700);
      switch (signal_stat) {
      case RTOS::Thread::signal_return_values::eTimeOut:
        std::cout << "Signal wait timed out." << std::endl;
        break;
      case RTOS::Thread::signal_return_values::eUnexpectedSignalReceived:
        std::cout << "Unexpected signal received." << std::endl;
        break;
      case RTOS::Thread::signal_return_values::eExpectedSignalReceived:
        std::cout << "Correct signal received before time-out." << std::endl;
        break;
      default:
        break;
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