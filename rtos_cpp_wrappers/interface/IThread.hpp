/**
 * @file        IThread.hpp
 * @author      manish tummala (manish.tummala@gmail.com)
 * @brief       Interface for the thread class.
 * @version     0.1
 * @date        2020-07-15
 * 
 * @copyright   Copyright (c) 2020
 * 
 */

#ifndef RTOS_ITHREAD_HPP
#define RTOS_ITHREAD_HPP

#include "rtos_types.hpp"

namespace RTOS{

    /**
     * @brief Interface class for the Thread objects.
     * 
     */
    class IThread{

    public:

        virtual ~IThread() = default;
        /**
         * @brief   Joins the thread to the kernel when invoked.
         */
        virtual void                    join() = 0;

        /**
         * @brief   stops the running thread. And, returns the status of the thread stop.
         *
         *          Every derived class can have its own implementation of this function.
         *          This is provided so as to have a customized thread control. The thread
         *          owner himself decides if the thread had to be stopped upon a function
         *          call by some module. By default the Thread class will be evaluated at
         *          the least possible ownership. The difference between the thread_delete
         *          and this call is that here the underling task is just suspended.
         *
         * @return  rtos_return_status_e eRTOSSuccess if thread stopped else eRTOSFailure.
         */
        virtual void                    suspend() const = 0;

        /**
         * @brief Resumes the suspend task.
         * 
         * @return rtos_return_status_e 
         */
        virtual void                    resume() const = 0;

        /**
         * @brief   Get the thread priority.
         *
         *          Returns the thread priority of the object the reference or the pointer
         *          of this interface class is pointing to.
         * 
         * @return  rtos_thread_priority_t.
         */
        virtual priority_t              get_priority() const = 0;

        /**
         * @brief   Set the thread priority object
         * 
         * @return  eRTOSSuccess if the priority setting is successful.
         * @return  eRTOSSuccess if the priority setting is unsuccessful.
         */
        virtual return_status_e         set_priority(priority_t) = 0;

        /**
         * @brief   Get the thread id of the thread.
         *          Returns the thread id of the object.
         * @return  rtos_thread_id_t 
         */ 
        virtual id_t                    get_id() const = 0;

        /**
         * @brief   Get the thread name.
         * 
         * @return  char const* Pointer to the name of the thread.
         */
        virtual char const*             get_name() const = 0;

        /**
         * @brief   Get the threat status.
         * 
         *          Returns the current status of the thread. No state change to the thread.
         * 
         * @return  rtos_return_status_e returns one of @ref rtos_return_status_e. 
         */
        virtual status_e                get_status() const = 0;

        /**
         * @brief   Deletes the thread.
         *
         *          Deletes the underling task and then. As the FreeRTOS is implemented
         *          The resources are not unallocated till the control passes to the idle
         *          task. This call fails when the task is locked by the owner task. The 
         *          difference between the thread_suspend and thread_delete is that here the
         *          underling task is deleted and the object is destroyed.
         *
         * @return  rtos_return_status_e returns one of @ref rtos_return_status_e.
         */
        virtual return_status_e         thread_delete() = 0;

        /**
         * @brief   Check if the thread is created or had issues while creating the thread.
         *
         * @return  true if the thread is created else false.
         */
        virtual bool                    is_thread_created() const = 0;

    };
}
#endif //RTOS_ITHREAD_HPP
