/**
 * @file        Thread.hpp
 * @author      manish Tummala (manish.tummala@domain.com)
 * @brief       Provides the implementation for the thread class.
 * @version     0.1
 * @date        2020-07-23
 * 
 * @copyright   Copyright (c) 2020
 */

#include <IThread.hpp>
#include <rtos_types.hpp>

namespace RTOS{

    /**
     * @brief This class implements the thread i.e. the wrapper for the FreeRTOS Task.
     */
    class Thread : public IThread{

        static rtos_thread_id_t m_sThreadCount;     /**<Holds the count of the threads that have been created       >*/

        /*---------------- Non Static member variables -------- ----*/
        rtos_thread_id_t        m_threadId;         /**<Holds the id of the current thread.                         >*/
        rtos_thread_type_e      m_eThreadType;      /**<Hold the type of the current thread object.                  >*/
        rtos_thread_handel_t    m_pHandel;          /**<Points to the task handle of the created thread.            >*/
        rtos_thread_stack_t     m_pStack;           /**<Points to the stack of the thread created.                  >*/
        rtos_thread_cb_t        m_pTaskCb;          /**<Points to the task's control block.                         >*/
    public:

        explicit Thread() = delete;                 /**<Default constructor is deleted.                             >*/
        
        Thread(rtos_thread_name_t       thread_name,/**<Single constructor for the thread class.                    >*/
               rtos_thread_priority_t   thread_priority,
               rtos_stack_size_t        thread_stack_size,
               rtos_thread_type_e       thread_type,
               rtos_thread_id_t         thread_id = 0);

        ~Thread();
        /*------------------ Static Methods -------------------*/
        /**
         * @breif   Used to identify if the scheduler is running or not.
         * @return  True if the scheduler is currently running.
         */
        static  bool            is_scheduler_running();
        /**
         * @breif   Starts the freeRTOS scheduler if not running.
         */
        static  void            start_scheduler();
        /**
         * @breif   Thread starter functions that'll be passed into the kernel.
         */
        static  void            thread_start(void*);
        /**
         * @breif   Thread starter functions that'll be passed into the kernel.
         *          The primary difference is that the thread will be suspended
         *          at the moment attached to the kernel.
         */
        static  void            thread_start_suspended(void*);

        /*---- Methods that are from the IThread interface ----*/
        rtos_thread_id_t        get_thread_id() const override;
        rtos_thread_priority_t  get_thread_priority() const override;
        rtos_return_status_e    set_thread_priority(rtos_thread_priority_t) override;
        char const*             get_thread_name() const override;
        rtos_thread_status_e    get_thread_status() const override;
        bool                    is_thread_killable() const override;


        void                    thread_suspend() const override;
        void                    thread_resume() const override;
        bool                    is_thread_created() const override;
        rtos_base_t             notify(rtos_notify_value, RTOS_NTF_TYP_E) override;
        void                    thread_join() const override;


    private:

        /**
 * @brief   Yields the thread from execution.
 */
        static  void            thread_yield();
        /**
         * @breif   Calling this function will move the thread to blocked state for a
         *          given amount of time.
         * @param   This should be a non-negative value describing the number of milli
         *          -seconds the thread has to be in blocked state before being resumed.
         */
        static  void            thread_delay_ms(rtos_delay_t);
        /**
         * @breif   thread_run function that all the inherited classes have to implement.
         */
        virtual void            thread_run() = 0;
    };
}