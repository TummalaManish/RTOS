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

        static thread_id_t m_sThreadCount;          /**<Holds the count of the threads that have been created       >*/

        /*---------------- Non Static member variables -------- ----*/
        thread_id_t        m_threadId;               /**<Holds the id of the current thread.                        >*/
        thread_handel_t    m_pHandel{};              /**<Points to the task handle of the created thread.           >*/
        thread_stack_t     m_pStack;                 /**<Points to the stack of the thread created.                 >*/
        thread_cb_t        m_pTaskCb{};              /**<Points to the task's control block.                        >*/
    public:

        explicit Thread() = delete;                 /**<Default constructor is deleted.                             >*/
        
        Thread(thread_name_t       thread_name,     /**<Single constructor for the thread class.                    >*/
               thread_priority_t   thread_priority,
               stack_size_t        thread_stack_size,
               thread_id_t         thread_id = 0);

        ~Thread();
        /*------------------ Static Methods -------------------*/
        /**
         * @breif   Starts the freeRTOS scheduler if not running.
         */
        static  void            start_scheduler();

        /**
         * @breif   Ends the scheduler.
         */
        static  void            end_scheduler();

        /**
         * @breif   Used to identify if the scheduler is running or not.
         * @return  True if the scheduler is currently running.
         */
        static  bool            is_scheduler_running();

    private:
        /**
         * @breif   Thread starter functions that'll be passed into the kernel.
         */
        static  void            start(void*);

    public:
        /*---- Methods that are from the IThread interface ----*/
        thread_id_t        get_id() const override;
        thread_priority_t  get_priority() const override;
        return_status_e    set_priority(thread_priority_t) override;
        char const*        get_name() const override;
        thread_status_e    get_status() const override;

        void                    suspend() const override;
        void                    resume() const override;
        bool                    is_thread_created() const override;
        RTOS_RET_STA_E          notify(notify_value, NTF_TYP_E) override;
        void                    join() override;


    protected:

        /**
         * @brief   Yields the thread from execution.
         */
        static  void            yield();
        /**
         * @breif   Calling this function will move the thread to blocked state for a
         *          given amount of time.
         * @param   This should be a non-negative value describing the number of milli
         *          -seconds the thread has to be in blocked state before being resumed.
         */
        static  void            delay_ms(delay_t);
        /**
         * @breif
         */
        //TODO: static  void            wait_for_notification();
        /**
         * @breif   thread_run function that all the inherited classes have to implement.
         */
        virtual void            run() = 0;
    };
}