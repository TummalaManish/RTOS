/**
 * @file        rtos_types.hpp
 * @author      Manish Tummala (Email: tummalamanish@gmail.com)
 * @brief       Implements the abstract task class that has to be inherited by all the tasks.
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

#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"
#include "stream_buffer.h"
#include "portmacro.h"
/*--------------------------------------------------------*/
#include <cstdint>

/*-------------------- Defines ---------------------------*/
#ifndef debug_break
#define debug_break __debugbreak()
#endif

namespace RTOS{
/**
 * @brief Type used for rtos thread priories.
 */
#if configMaxPriorities <= 255
    using priority_t = uint8_t;
#elif configMaxPriorities <= 65535
    using priority_t = uint16_t;
#else
    #error("RTOS: The port dose not suppot prorites more than 65535!!")
#endif //Closing rtos priority type.
/**
 * @brief Base type used for all the rtos operations.
 */
    using base_t = BaseType_t;

    /*------------------------------ Task specific definitions ------------------------------*/
/**
 * @brief Type used for the thread names.
 */
    //TODO: 1 Have to implement inline low over head test for names.
    using name_t = const char *;
/**
 * @brief Type used for the RTOS stack size.
 */
    using stack_size_t = configSTACK_DEPTH_TYPE;
/**
 * @brief Stack of the thread.
 */
    using stack_t = StackType_t*;
/**
 * @brief Static TCB of the thread.
 */
    using control_block_t = StaticTask_t*;
/**
 * @brief Handel for the created thread.
 */
    using thr_handle_t = TaskHandle_t;
/**
 * @brief RTOS delay time.
 */
    using delay_t = float;
    constexpr delay_t wait_forever = 0xffffffffUL * 1000 / configTICK_RATE_HZ; // NOLINT(bugprone-integer-division)

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
#endif //Closing the RTOS thread id type.

/**
 * @brief Type used to identify thread status.
 */
    //TODO: 2 All the thread statuses have to be added here.
    //TODO: Have to remove unwanted status enumerations.
    enum class status_e { //Thread status
        //Notes: Add the failure enums above.
        eNoStatus = 0,
        eMemoryAllocationFailed = 1,
        eBlockedByChoice = 2,
        eThreadNotStarted = 4,
        eThreadStarted = 8,
        //Notes: This is the last state.Hence, everything has be above this state number.
        eInvalidStatus = 128,
    };
    using THR_STA_E = status_e;
/**
 * @brief Enumerates success returns and failure returns in the RTOS.
 */
    enum class return_status_e {
        eRTOSSuccess = 1,
        eRTOSFailure = 0,
    };
    using RET_STA_E = return_status_e;
/**
 * @brief Enumerates the scheduler status.
 */
    enum class scheduler_status_e {
        eSchedulerNotRunning = 0,
        eSchedulerRunning = 1,
    };
    using SCH_STA_E = scheduler_status_e;
/**
 * @brief   Different notification action types.
 */
    enum class notify_type_e{
        eNoAction                   = eNoAction,                /* Notify the task without updating its notify value. */
        eSetBits                    = eSetBits,                 /* Set bits in the task's notification value.         */
        eIncrement                  = eIncrement,               /* Increment the task's notification value.           */
        eSetValueWithOverwrite      = eSetValueWithOverwrite,   /* Set the task's notification value to a specific
                                                                 * value even if the* previous value has not yet been
                                                                 * read by the task.                                  */
        eSetValueWithoutOverwrite   = eSetValueWithoutOverwrite /* Set the task's notification value if the previous
                                                                 * value has been read by the task. */
    };
    using NTF_TYP_E = notify_type_e;
    /*----------------------------------------------------------------------------------------*/

    /*-------------------------------- Queue definitions -------------------------------------*/
/**
 * @brief   Handel for the queues.
 */
    using que_handle_t = QueueHandle_t;

    using queue_cb_t = StaticQueue_t*;
}
#endif //Closing RTOS_TYPES_HPP.
