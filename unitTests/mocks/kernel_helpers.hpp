//
// Created by TUMMALA-MANISH on 18-07-2020.
//

#ifndef RTOS_CPP_WRAPPER_KERNEL_HELPERS_HPP
#define RTOS_CPP_WRAPPER_KERNEL_HELPERS_HPP

void vAssertCalled(unsigned long ulLine, const char *const pcFileName) {
  printf("ASSERT: %s : %d\n", pcFileName, (int)ulLine);
  while (1)
    ;
}

#endif // RTOS_CPP_WRAPPER_KERNEL_HELPERS_HPP
