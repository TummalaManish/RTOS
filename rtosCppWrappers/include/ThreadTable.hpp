// TODO: implement Thread table.
// Note: Feature implemention is on hold.
/**
 * @file        ThreadTable.hpp
 * @author      Manish Tummala (manish.tummala@gmail.com)
 * @brief       This file implements the thread table that is accessble by all
 * the threads. This keeps a track of all the thread objects to control and
 * handel them all.
 * @version     0.1
 * @date        2020-07-19
 *
 * @copyright   Copyright (c) 2020
 *
 */

#ifndef RTOS_CPP_WRAPPER_THREADTABLE_HPP
#define RTOS_CPP_WRAPPER_THREADTABLE_HPP

#include <IThread.hpp>

namespace RTOS {

/**
 * @brief   This is also a singleton object. It holds the thread table that help
 * in accessing diffrent threads. Note: Still this feature is under
 * consideration.
 */
class ThreadTable {

  using thread_table_thread_count_t = rtos_thread_id_t;

  /**
   * @brief   Struct that holds the thread id for access.
   */
  struct ThTaSt {
    rtos_thread_id_t id;
    IThread &r_thread;
  };
  using rtos_thread_table_s = struct ThTaSt;

  static thread_table_thread_count_t threadCount;

  // Have to implemnet the BASE stucters to further the code.
public:
  IThread &get_thread_by_id();

  thread_table_thread_count_t get_thread_count();
}
} // namespace RTOS
#endif // RTOS_CPP_WRAPPER_THREADTABLE_HPP