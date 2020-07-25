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
#include <task.h>

namespace RTOS{

    /**
     * @brief This class implements the thread i.e. the warapper for the FreeRTOS Task.
     */
    class Thread : public IThread{

        rtos_thread_id_t        m_threadId;         /**<Holds the id of the current thread.                 >*/
        rtos_thread_type_e      m_ethreadType;      /**<Hold the type of the curent thread object.          >*/
        rtos_thread_handel_t    m_pHandel;          /**<Points to the task handel of the created thread.    >*/
        rtos_thread_stack_t     m_pStack;           /**<Points to the stack of the thread created.          >*/
        rtos_thread_cb_t        m_pTaskCb;          /**<Points to the task's control block.                 >*/

    public:

        explicit Thread() = delete;                 /**<Default constructor is deleted.                     >*/
        
        Thread(rtos_thread_name_t       thread_name,/**<Single constructor for the thread class.            >*/
               rtos_thread_priority_t   thread_priority,
               rtos_stack_size_t        thread_stack_size,
               rtos_thread_type_e       thread_type,
               rtos_thread_id_t         thread_id = 0);

        ~Thread();
        /*------------------ Static Methods -------------------*/
        static  bool            is_schedular_running();
        static  void            thread_start(void *);
        static  void            thread_start_suspended(void*);

        /*---- Methods that are from the IThread interface ----*/
        rtos_thread_id_t        get_thread_id() const override;
        rtos_thread_priority_t  get_thread_priority() const override;
        rtos_return_status_e    set_thread_priority(rtos_thread_priority_t) override;
        char const*             get_thread_name() const override;
        rtos_thread_status_e    get_thread_status(void) const override;
        bool                    is_thread_killable(void) const override;
        rtos_return_status_e    thread_resume() override;
        void                    thread_join() override;

        void                    thread_yield(void) override;
        rtos_return_status_e    thread_suspend(void) override;


        virtual void                    thread_run(void) = 0;
    };
}