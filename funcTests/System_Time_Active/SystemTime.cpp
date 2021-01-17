/**
 * @file        Task_Creation.cpp
 * @author      Manish Tummala (manish.tummala@gmail.com)
 * @brief       Tests the functionality of the task creation and running.
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
#include "Time64.hpp"

// APP Section:
class clock : public RTOS::Thread {

  RTOS::ITime64 const &m_rTime64;

  void run() override {
    RTOS::os_time_t const timeAtStart = m_rTime64.get_time64();
    // Test start.
    std::cout << "Test Start" << std::endl;
    std::cout << "Time at start: " << timeAtStart << std::endl;
    delay_ms(1000); // Waiting for 1000 milliseconds.
    std::cout << "Time after 1000 Ms delay: " << m_rTime64.get_time64()
              << std::endl;
    std::cout << "Time delta after the pass: "
              << static_cast<int64_t>(m_rTime64.get_time64() - timeAtStart)
              << std::endl;
    std::cout << "Ending test." << std::endl;
    // Closing the Tests.
    end_scheduler();
  }

public:
  explicit clock(const RTOS::ITime64 &mRTime64)
      : Thread("SndThr", 1, 100), m_rTime64(mRTime64) {}
};

int main() {
  RTOS::Time64 rtosTime;

  clock clockObject(rtosTime);
  clockObject.join();
  return 0;
}
