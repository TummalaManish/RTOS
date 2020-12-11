/**
 * @file        rtos_types.hpp
 * @author      Manish Tummala (Email: tummalamanish@gmail.com)
 * @brief       Implements the abstract task class that has to be inherited by
 * all the tasks.
 * @version     0.1
 * @date        2020-07-03
 *
 * @copyright   Copyright (c) 2020
 *
 */

#ifndef RTOS_TYPES_HPP
#define RTOS_TYPES_HPP

/*------------------- FreeRTOS Types ---------------------*/
#include "FreeRTOS.h"

#include "event_groups.h"
#include "portmacro.h"
#include "queue.h"
#include "stream_buffer.h"
#include "task.h"
#include "timers.h"

/*--------------------------------------------------------*/
#include <cstdint>

/*-------------------- Defines ---------------------------*/
#ifdef SIM
#define debug_break __debugbreak()
// Note: The below have to be adjusted for other compilers as well.
#else
#define debug_break asm("bkpt 0x01")
#endif

namespace RTOS {
/**
 * @brief Type used for rtos thread priories.
 */
#if configMaxPriorities <= 255
using priority_t = uint8_t;
#elif configMaxPriorities <= 65535
using priority_t = uint16_t;
#else
#error("RTOS: The port dose not suppot prorites more than 65535!!")
#endif // Closing rtos priority type.
/**
 * @brief Base type used for all the rtos operations.
 */
using base_t = BaseType_t;

/*--- Task specific definitions ----*/
/**
 * @brief Type used for the thread names.
 */
// TODO: 1 Have to implement inline low over head test for names.
using name_t = const char *;
/**
 * @brief Type used for the RTOS stack size.
 */
using stack_size_t = configSTACK_DEPTH_TYPE;
/**
 * @brief Stack of the thread.
 */
using stack_t = StackType_t *;
/**
 * @brief Static TCB of the thread.
 */
using control_block_t = StaticTask_t *;
/**
 * @brief Handel for the created thread.
 */
using thr_handle_t = TaskHandle_t;
/**
 * @brief RTOS delay time.
 */
using delay_t = float;
constexpr delay_t wait_forever =
    static_cast<float>(0xffffffffUL * 1000 /
                       configTICK_RATE_HZ); // NOLINT(bugprone-integer-division)

/**
 * @brief Type for the notification value.BaseType_t
 */
using notify_value_t = uint32_t;
/**
 * @brief Type of the thread id.
 */
#if configMaxPriorities <= 255
using id_t = uint8_t;
#elif configMaxPriorities <= 65535
using id_t = uint16_t;
#else
#error("RTOS: The port dose not suppot threads more than 65535!!")
#endif // Closing the RTOS thread id type.

/**
 * @brief Enumerates success returns and failure returns in the RTOS.
 */
enum class return_status_e {
  eRTOSFailure = 0,
  eRTOSSuccess = 1,
};
using RET_STA_E = return_status_e;
/*----------------------------------------------------------------------------*/

/*---------------------------- Queue definitions -----------------------------*/
/**
 * @brief   Handel for the queues.
 */
using que_handle_t = QueueHandle_t;

using queue_cb_t = StaticQueue_t *;
} // namespace RTOS
#endif // Closing RTOS_TYPES_HPP.
