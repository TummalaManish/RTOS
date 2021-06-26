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
#include <Thread.hpp>

// APP Section:
class test_thr1 : public RTOS::Thread {

  int value_of_thread;
  void run() override {
    for (;;) {
      // std::cout << "running thread number" << value_of_thread << std::endl;
      size_t value = UINT16_MAX;
      while (value) {
        value--;
      }
      Thread::delay_ms(500);
    }
  }

  RTOS::return_status_e thread_delete() override {
    return RTOS::return_status_e::eRTOSSuccess;
  }

public:
  explicit test_thr1(int thread_number)
      : value_of_thread(thread_number), Thread("TestThread", 1, 100) {}
};

class main_thread : public RTOS::Thread {

  void run() override {
    // std::cout << "Adding Main Thread" << std::endl;
    for (uint8_t index = 0; index < thread_count; ++index) {
      thread_array->join();
      thread_array++;
    }
    delay_ms(500);

    for (;;) {
      size_t value = UINT16_MAX;
      while (value) {
        value--;
      }
      Thread::delay_ms(500);
    }
  }

  RTOS::return_status_e thread_delete() override {
    return RTOS::return_status_e::eRTOSSuccess;
  }

public:
  main_thread(test_thr1 *Thread_Array, uint8_t count)
      : thread_array(Thread_Array), thread_count(count),
        Thread("MainThread", 2, 800) {}

private:
  test_thr1 *thread_array;
  uint8_t thread_count;
};

test_thr1 threads[4] = {test_thr1(1), test_thr1(2), test_thr1(3), test_thr1(4)};
main_thread main_th(threads, 4);

int main() {
  traceSTART();
  main_th.join();
  return 0;
}

void vAssertCalled(unsigned long ulLine, const char *const pcFileName) {
  // printf("ASSERT: %s : %d\n", pcFileName, (int)ulLine);
  while (1)
    ;
}