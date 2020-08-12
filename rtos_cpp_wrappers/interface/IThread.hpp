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

#include "rtos_types.hpp"

namespace RTOS{

    /**
     * @brief Interface class for the Thread objects.
     * 
     */
    class IThread{

        /**
         * @brief   Joins the thread to the kernel when asked.
         */
        virtual void                    thread_join() const = 0;

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
        virtual void                    thread_suspend() const = 0;

        /**
         * @brief Resumes the suspend task.
         * 
         * @return rtos_return_status_e 
         */
        virtual void                    thread_resume() const = 0;

        /**
         * @brief   Get the thread priority.
         *
         *          Returns the thread priority of the object the reference or the pointer
         *          of this interface class is pointing to.
         * 
         * @return  rtos_thread_priority_t.
         */
        virtual rtos_thread_priority_t  get_thread_priority() const = 0;

        /**
         * @brief   Set the thread priority object
         * 
         * @return  eRTOSSuccess if the priority setting is successful.
         * @return  eRTOSSuccess if the priority setting is unsuccessful.
         */
        virtual rtos_return_status_e    set_thread_priority(rtos_thread_priority_t) = 0;

        /**
         * @brief   Get the thread id of the thread.
         *          Returns the thread id of the object.
         * @return  rtos_thread_id_t 
         */ 
        virtual rtos_thread_id_t        get_thread_id() const = 0;

        /**
         * @brief   Get the thread name.
         * 
         * @return  char const* Pointer to the name of the thread.
         */
        virtual char const*             get_thread_name() const = 0;

        /**
         * @brief   Get the threat status.
         * 
         *          Returns the current status of the thread. No state change to the thread.
         * 
         * @return  rtos_return_status_e returns one of @ref rtos_return_status_e. 
         */
        virtual rtos_thread_status_e    get_thread_status() const = 0;

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
        virtual rtos_return_status_e    thread_delete() = 0;

        /**
         * @brief   Checks if the thread is killable or not.
         * 
         * @return  true if the thread is killabel.
         * @return  false if the thread is nonkillable.
         */
        virtual bool                    is_thread_killable() const = 0;

        /**
         * @breif   Check if the thread is created or had issues while creating the thread.
         *
         * @return  true if the thread is created else false.
         */
        virtual bool                    is_thread_created() const = 0;

        /**
         *
         */
        virtual rtos_base_t             notify(rtos_notify_value, RTOS_NTF_TYP_E) = 0;
    };
}