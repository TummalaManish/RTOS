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

namespace RTOS{
/**
 * @brief Type used for rtos thread priories.
 */
#if configMaxPriorities <= 255
    using rtos_thread_priority_t = uint8_t;
#elif configMaxPriorities <= 65535
    using rtos_thread_priority_t = uint16_t;
#else
    #error("RTOS: The port dose not suppot prorites more than 65535!!")
#endif //Closing rtos priority type.
/**
 * @breif Base type used for all the rtos operations.
 */
    using rtos_base_t = BaseType_t;
/**
 * @brief Type used for the thread names.
 */
    //TODO: 1 Have to implement inline low over head test for names.
    using rtos_thread_name_t = const char *;
/**
 * @brief Type used for the RTOS stack size.
 */
    using rtos_stack_size_t = configSTACK_DEPTH_TYPE;
/**
 * @brief Packs the parameters for the thread.
 */
    using rtos_thread_parmas_pack = void *;
/**
 * @brief Stack of the thread.
 */
    using rtos_thread_stack_t = StackType_t*;
/**
 * @brief Static TCB of the thread.
 */
    using rtos_thread_cb_t = StaticTask_t*;
/**
 * @brief Handel for the created thread.
 */
    using rtos_thread_handel_t = TaskHandle_t;
/**
 * @breif RTOS delay time.
 */
    using rtos_delay_t = float;
/**
 * @breif   Type for the notification value.BaseType_t
 */
    using rtos_notify_value = uint32_t;
/**
 * @brief Type of the thread id.
 */
#if configMaxPriorities <= 255
    using rtos_thread_id_t = uint8_t;
#elif configMaxPriorities <= 65535
    using rtos_thread_id_t = uint16_t;
#else
    #error("RTOS: The port dose not suppot threads more than 65535!!")
#endif //Closing the RTOS thread id type.

/**
 * @brief Type used to identify thread status.
 */
    //TODO: 2 All the thread statuses have to be added here.
    //TODO: Have to remove unwanted status enumerations.
    enum class rtos_thread_status_e { //Thread status
        //Notes: Add the failure enums above.
        eCoreMemoryAllocationFailed = -1,
        eNoStatus = 0,
        eBlockedByChoice = 1,
        eCoreThreadInitializationFailed,
        eCoreThreadNotInitialized,
        eCoreThreadInitialized,
        //Notes: This is the last state.Hence, everything has be above this state number.
        eInvalidStatus = 127,
    };
    using RTOS_THR_STA_E = rtos_thread_status_e;
/**
 * @brief Enumerates success returns and failure returns in the RTOS.
 */
    enum class rtos_return_status_e {
        eRTOSSuccess = 1,
        eRTOSFailure = 0,
    };
    using RTOS_RET_STA_E = rtos_return_status_e;
/**
 * @brief Enumerates the scheduler status.
 */
    enum class rtos_scheduler_status_e {
        eSchedulerNotRunning = 0,
        eSchedulerRunning = 1,
    };
    using RTOS_SCH_STA_E = rtos_scheduler_status_e;
/**
 * @brief Enumerates the different thread types that can be created.
 * 
 *          The stack and TCB for the Killable threads are allocated from the 
 *          heap block using the memory manager i.e using the portMalloc API's
 * 
 *          The stack and TCB for the NonKillable threads are not allocated from
 *          the heap. Rather these are allocated on the stack.
 */
    enum class rtos_thread_type_e {
        eKillable = 0,
        eNonKillabe
    };
    using RTOS_THR_TYP_E = rtos_thread_type_e;
/**
 * @breif   Different notification action types.
 */
    enum class rtos_notify_type_e{
        eNoAction = 0,              /* Notify the task without updating its notify value. */
        eSetBits,                   /* Set bits in the task's notification value. */
        eIncrement,                 /* Increment the task's notification value. */
        eSetValueWithOverwrite,     /* Set the task's notification value to a specific value even if the
                                     * previous value has not yet been read by the task. */
        eSetValueWithoutOverwrite   /* Set the task's notification value if the previous value has been read by the
                                     * task. */
    };
    using RTOS_NTF_TYP_E = rtos_notify_type_e;
}
#endif //Closing RTOS_TYPES_HPP.
