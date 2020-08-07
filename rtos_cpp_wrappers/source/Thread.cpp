/**
 * @file        Thread.cpp
 * @author      Manish Tummala(manish.tummala@gmail.com)
 * @brief       Thread implementation.
 * @version     0.1
 * @date        2020-07-23
 * 
 * @copyright   Copyright (c) 2020
 * 
 */

#include <MemoryManager.hpp>
#include <Thread.hpp>

namespace RTOS{

    /*--------- static value initialization ---------*/
    rtos_thread_id_t Thread::m_sThreadCount = 0;
    /*----------------------------------------------*/

    RTOS::Thread::Thread(rtos_thread_name_t thread_name, rtos_thread_priority_t thread_priority,
                         rtos_stack_size_t thread_stack_size, rtos_thread_type_e thread_type,
                         rtos_thread_id_t thread_id) : m_eThreadType(thread_type) {

        //TODO: the constructor is not symmetric for scheduler running and stalled.
        if (not is_scheduler_running()) {
            if (thread_stack_size != 0 && thread_type == RTOS_THR_TYP_E::eNonKillabe && thread_priority > 0) {

                StackType_t th_stack[thread_stack_size];
                StaticTask_t th_TCB;
                m_pStack = nullptr;
                m_pTaskCb = nullptr;

                m_pHandel = xTaskCreateStatic(thread_start, //Code to pass to the thread.
                                              thread_name,
                                              thread_stack_size,
                                              this,
                                              thread_priority,
                                              th_stack,
                                              &th_TCB);
                if (m_pHandel not_eq static_cast<void*>(nullptr)) {
                    vTaskSuspend(m_pHandel); //Places the task in the suspended list.
                    ++m_sThreadCount;
                }
            }
            else if (thread_stack_size != 0 && thread_type == RTOS_THR_TYP_E::eKillable && thread_priority > 0) {
                if (MemoryManager::get_Instance().get_stack(m_pStack, thread_stack_size) == eMemAllocationSuccess &&
                    MemoryManager::get_Instance().get_TCB(m_pTaskCb)) {

                    m_pHandel = xTaskCreateStatic(thread_start, //Code to pass to the thread.
                                                  thread_name,
                                                  thread_stack_size,
                                                  this,
                                                  thread_priority,
                                                  m_pStack,
                                                  m_pTaskCb);
                    if (m_pHandel not_eq static_cast<void*>(nullptr)) {
                        vTaskSuspend(m_pHandel); //Places the task in the suspended list.
                        ++m_sThreadCount;
                    }
                }
                else {
                    //Cannot create the task with given specs.
                    /*Note:This function must be implemented somewhere in the base of the port*/
                    __debugbreak();
                }
            }
            else {
                //Creating a task encountered the an error.
                /*Note:This function must be implemented somewhere in the base of the port*/
                __debugbreak();
            }
            if (thread_id != 0) { m_threadId = thread_id; }
                /*Review: rtos_thread_id_t type is adjusted according to the number of tasks that can be created.*/
            else { m_threadId = static_cast<rtos_thread_id_t>(uxTaskGetTaskNumber(m_pHandel)); }
        }
        else {
            if (thread_stack_size != 0 && thread_type == RTOS_THR_TYP_E::eNonKillabe && thread_priority > 0) {
                StackType_t th_stack[thread_stack_size];
                StaticTask_t th_TCB;
                m_pStack = nullptr;
                m_pTaskCb = nullptr;
                m_pHandel = xTaskCreateStatic( thread_start_suspended, //Code to pass to the thread.
                                               thread_name,
                                               thread_stack_size,
                                               this,
                                               thread_priority,
                                               th_stack,
                                               &th_TCB);
                if (m_pHandel not_eq static_cast<void*>(nullptr)) {
                    ++m_sThreadCount;
                }
            }
            else if (thread_stack_size != 0 && thread_type == RTOS_THR_TYP_E::eKillable && thread_priority > 0) {
                if (MemoryManager::get_Instance().get_stack(m_pStack, thread_stack_size) == eMemAllocationSuccess &&
                    MemoryManager::get_Instance().get_TCB(m_pTaskCb)) {
                    m_pHandel = xTaskCreateStatic(thread_start_suspended, //Code to pass to the thread.
                                                  thread_name,
                                                  thread_stack_size,
                                                  this,
                                                  thread_priority,
                                                  m_pStack,
                                                  m_pTaskCb);
                    if (m_pHandel not_eq static_cast<void*>(nullptr)) {
                        ++m_sThreadCount;
                    }
                }
                else {
                    //Cannot create the task with give specs.
                    /*Note:This function must be implemented somewhere in the base of the port*/
                    __debugbreak();
                }
            }
            else {
                //Creating a task encountered the an error.
                /*Note:This function must be implemented somewhere in the base of the port*/
                __debugbreak();
            }
            //TODO: Thread id assignment have to be made unique.
            if (thread_id != 0) { m_threadId = thread_id; }
                /*Review: rtos_thread_id_t type is adjusted according to the number of tasks that can be created.*/
            else { m_threadId = static_cast<rtos_thread_id_t>(uxTaskGetTaskNumber(m_pHandel)); }
        }
    }

    Thread::~Thread() {
        if (is_scheduler_running()){ vTaskDelete(m_pHandel); }
        if (Thread::is_thread_killable()){
            //Memory for the task has been provided from the heap hence the clean up.
            MemoryManager::release_TCB(m_pTaskCb);
            MemoryManager::release_stack(m_pStack);
        }
    }

    void Thread::thread_start(void * super){
        auto *this_obj = static_cast<Thread *>(super);
        if(this_obj->is_thread_created()){
            this_obj->thread_run();

            /*--------- Execution should never come here -----------*/
            //TODO: Invalid thread exit. The thread will be cleaned up and this has
            //      to be logged. Once the logger is implemented.
            __debugbreak();
        }
        else{
            __debugbreak();
        }
    }

    void Thread::thread_start_suspended(void * super) {
        auto *this_obj = static_cast<Thread *>(super);
        if(this_obj->is_thread_created()) {
            this_obj->thread_suspend();
            this_obj->thread_run();

            /*--------- Execution should never come here -----------*/
            //TODO: Invalid thread exit. The thread will be cleaned up and this has
            //      to be logged. Once the logger is implemented.
            __debugbreak();
        }
        else{
            __debugbreak();
        }
    }

    bool Thread::is_scheduler_running() {
        return xTaskGetSchedulerState() == taskSCHEDULER_RUNNING;
    }

    rtos_thread_id_t Thread::get_thread_id() const {
        return m_threadId;
    }

    rtos_thread_priority_t Thread::get_thread_priority() const {
        return static_cast<rtos_thread_priority_t>(uxTaskPriorityGet(m_pHandel));
    }

    //note: partially implemented.
    rtos_return_status_e Thread::set_thread_priority(rtos_thread_priority_t new_priority) {
        //TODO: This is a bit complicated function has to be implement yet.
        vTaskPrioritySet(m_pHandel, new_priority);
        return RTOS_RET_STA_E::eRTOSSuccess;
    }

    char const *Thread::get_thread_name() const {
        return static_cast<const char*>(pcTaskGetName(m_pHandel));
    }

    //todo: method not implemented yet.
    rtos_thread_status_e Thread::get_thread_status() const {
        return RTOS_THR_STA_E::eCoreMemoryAllocationFailed;
    }

    bool Thread::is_thread_killable() const {
        return m_eThreadType == RTOS_THR_TYP_E::eKillable;
    }

    void Thread::thread_yield() const {
        //This macro will be populated by the port layer.
        taskYIELD();
    }

    rtos_return_status_e Thread::thread_suspend() const {
        vTaskSuspend(m_pHandel);
        return RTOS_RET_STA_E::eRTOSSuccess;
    }

    rtos_return_status_e Thread::thread_resume() const {
        vTaskResume(m_pHandel);
        return RTOS_RET_STA_E::eRTOSSuccess;
    }

    void Thread::thread_join() const {
        thread_resume();
        if (not(is_scheduler_running())) { vTaskStartScheduler(); }
    }

    bool Thread::is_thread_created() const {
        return m_pHandel not_eq static_cast<void*>(nullptr);
    }

    void Thread::start_scheduler() {
        if (not(is_scheduler_running())){ vTaskStartScheduler(); }
    }

    void Thread::thread_delay_ms(rtos_delay_t delay) {
        vTaskDelay(static_cast<TickType_t>(pdMS_TO_TICKS(delay)));
    }
}

extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t ** ppxIdleTaskTCBBuffer,
                                              StackType_t ** ppxIdleTaskStackBuffer,
                                              uint32_t * pulIdleTaskStackSize);
void vApplicationGetIdleTaskMemory( StaticTask_t ** const ppxIdleTaskTCBBuffer,
                                    StackType_t ** const ppxIdleTaskStackBuffer,
                                    uint32_t * const pulIdleTaskStackSize){
    constexpr unsigned int stack_size = 50;
    static StaticTask_t l_tcb;
    static StackType_t l_stack[stack_size];
    *pulIdleTaskStackSize = stack_size;
    *ppxIdleTaskStackBuffer = reinterpret_cast<StackType_t *>(&l_stack);
    *ppxIdleTaskTCBBuffer = &l_tcb;
}
