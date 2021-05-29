/**
 * @file      MutexIntegrationTest.cpp
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Integration test for the mutex.
 * @version   0.1
 * @date      29-05-2021
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>

// RTOS Includes.
#include "Mutex.hpp"
#include "Thread.hpp"

class ThreadOne : public RTOS::Thread {
  RTOS::IMutex &m_rMutex;

public:
  explicit ThreadOne(RTOS::IMutex &rMutex)
      : m_rMutex(rMutex), RTOS::Thread("one", 2, 100) {}

  RTOS::return_status_e thread_delete() override {
    return RTOS::return_status_e::eRTOSSuccess;
  }

protected:
  void run() override {
    bool isLockSuccessful = m_rMutex.lock();
    isLockSuccessful
        ? std::cout << "Mutex locked by threadOne" << std::endl
        : std::cout << "Unable to lock mutex by threadOne" << std::endl;
    while (true)
      ;
  }
};

class ThreadTwo : public RTOS::Thread {
  RTOS::IMutex &m_rMutex;

public:
  explicit ThreadTwo(RTOS::IMutex &rMutex)
      : m_rMutex(rMutex), RTOS::Thread("two", 2, 100) {}

  RTOS::return_status_e thread_delete() override {
    return RTOS::return_status_e::eRTOSSuccess;
  }

protected:
  void run() override {
    bool isLockSuccessful = m_rMutex.lock();
    isLockSuccessful
        ? std::cout << "Mutex locked by threadTwo" << std::endl
        : std::cout << "Unable to lock mutex by threadTwo" << std::endl;
    while (true)
      ;
  }
};

class MainThread : public RTOS::Thread {

  void run() override {
    std::cout << "Adding Main Thread" << std::endl;
    std::cout << "Adding the child threads" << std::endl;

    m_rThreadOne.join();
    m_rThreadTwo.join();
    delay_ms(500);
    std::cout << "Ending the test.";
    end_scheduler();
  }

  RTOS::return_status_e thread_delete() override {
    return RTOS::return_status_e::eRTOSSuccess;
  }

public:
  MainThread(Thread &threadOne, Thread &threadTwo)
      : m_rThreadOne(threadOne), m_rThreadTwo(threadTwo),
        Thread("MainThread", 2, 800) {}

private:
  Thread &m_rThreadOne;
  Thread &m_rThreadTwo;
};

int main() {
  RTOS::Mutex protectionMutex;
  ThreadOne one(protectionMutex);
  ThreadTwo two(protectionMutex);
  MainThread main(one, two);

  main.join();
  return 0;
}

void vAssertCalled(unsigned long ulLine, const char *const pcFileName) {
  printf("ASSERT: %s : %d\n", pcFileName, (int)ulLine);
  while (1)
    ;
}