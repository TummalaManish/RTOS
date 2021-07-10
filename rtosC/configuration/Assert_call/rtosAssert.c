/**
 * @file      rtosAssert.cpp.c
 * @author    Tummala Manish (manishtummala@gmail.com)
 * @brief     Assert call for config assert.
 * @version   0.1
 * @date      09-01-2021
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <stdio.h>

void RTOS_ASSERT(char const* file, unsigned int const line){
  printf("RTOS ASSERT: %s : %d\n", file, (int)line);                        \
  while (1);
}