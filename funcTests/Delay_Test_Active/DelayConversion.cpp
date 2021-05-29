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

void print_for_the_tick_rate(RTOS::delay_t const incomingDelay) {
  std::cout << "A delay of " << incomingDelay << "ms is tranlated to ticks of "
            << pdMS_TO_TICKS(incomingDelay) << std::endl;
}

int main() {
  /* Lets see how the delays is passed on. */
  std::cout << " The tick rate is at: "
            << static_cast<unsigned int>(configTICK_RATE_HZ)
            << " i.e once clock cycle is: "
            << (1 / static_cast<unsigned int>(configTICK_RATE_HZ)) << std::endl;

  RTOS::delay_t delays[] = {100, 10, 12, 15, 255, 36.7, 89, 102};

  for (size_t index = 0; index < (sizeof(delays) / sizeof(RTOS::delay_t));
       index++) {
    print_for_the_tick_rate(delays[index]);
  }
}

void vAssertCalled(unsigned long ulLine, const char *const pcFileName) {
  printf("ASSERT: %s : %d\n", pcFileName, (int)ulLine);
  while (1)
    ;
}