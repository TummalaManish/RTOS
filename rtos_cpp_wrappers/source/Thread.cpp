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

    /*Structure to pass the TCB details*/
    struct TCB_pass_s{
        thread_stack_t m_pStack;
        stack_size_t m_stackSize;
        thread_priority_t m_threadPrio;
        char m_threadName[configMAX_TASK_NAME_LEN];
    };
    using TCB_PASS_STR = struct TCB_pass_s;

    /*--------- static value initialization ---------*/
    thread_id_t Thread::m_sThreadCount = 0;
    /*----------------------------------------------*/

    RTOS::Thread::Thread(thread_name_t thread_name, thread_priority_t thread_priority,
                         stack_size_t thread_stack_size, thread_id_t thread_id){
        m_pStack = NULL;
        m_pTaskCb = NULL;
        m_pHandel = NULL;
        bool result = ((MemoryManager::get_Instance().get_TCB(m_pTaskCb) == eMemoryResult::eMemAllocationSuccess) &&
                       (MemoryManager::get_Instance().get_stack(m_pStack, thread_stack_size)
                        == eMemoryResult::eMemAllocationSuccess));

        if (result){
            auto* block = reinterpret_cast<TCB_PASS_STR*>(m_pTaskCb);
            block->m_pStack = m_pStack;
            block->m_threadPrio = thread_priority;
            block->m_stackSize = thread_stack_size;
            for (auto index = static_cast<uint8_t>(0); index < configMAX_TASK_NAME_LEN; ++index ){
                if (thread_name[index] != static_cast<char>(0x00)){
                    block->m_threadName[index] = thread_name[index];
                }
                else{
                    //End of the line reached.
                    break;
                }
            }
            m_sThreadCount++;
            if (thread_id != 0) { m_threadId = thread_id; }
            else { m_threadId = m_sThreadCount; }
        }
        else{
            //Have to use te BASE versioned debug interface.
            __debugbreak();
        }
    }

    Thread::~Thread() {
        if (is_scheduler_running()){ vTaskDelete(m_pHandel); }
        //Memory for the task has been provided from the heap hence the clean up.
        MemoryManager::release_TCB(m_pTaskCb);
        MemoryManager::release_stack(m_pStack);
    }

    void Thread::start(void * super){
        auto *this_obj = static_cast<Thread *>(super);
        if(this_obj->is_thread_created()){
            this_obj->run();

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

    void Thread::yield(){
        //This macro will be populated by the port layer.
        taskYIELD();
    }

    void Thread::start_scheduler() {
        if (!(is_scheduler_running())){ vTaskStartScheduler(); }
    }

    void Thread::delay_ms(delay_t delay) {
        vTaskDelay(static_cast<TickType_t>(pdMS_TO_TICKS(delay)));
    }

    thread_priority_t Thread::get_priority() const {
        return static_cast<thread_priority_t>(uxTaskPriorityGet(m_pHandel));
    }

    //note: partially implemented.
    return_status_e Thread::set_priority(thread_priority_t new_priority) {
        //TODO: This is a bit complicated function has to be implement yet.
        vTaskPrioritySet(m_pHandel, new_priority);
        return RTOS_RET_STA_E::eRTOSSuccess;
    }

    char const *Thread::get_name() const {
        return static_cast<const char*>(pcTaskGetName(m_pHandel));
    }

    //todo: method not implemented yet.
    thread_status_e Thread::get_status() const {
        return RTOS_THR_STA_E::eCoreMemoryAllocationFailed;
    }

    void Thread::suspend() const {
        vTaskSuspend(m_pHandel);
    }

    void Thread::resume() const {
        vTaskResume(m_pHandel);
    }

    void Thread::join(){
        //Temp Variable to pass the parameters.
        TCB_PASS_STR block;
        block.m_threadPrio = (reinterpret_cast<TCB_PASS_STR*>(m_pTaskCb))->m_threadPrio;
        block.m_pStack = (reinterpret_cast<TCB_PASS_STR*>(m_pTaskCb))->m_pStack;
        block.m_stackSize = (reinterpret_cast<TCB_PASS_STR*>(m_pTaskCb))->m_stackSize;
        for(auto index = static_cast<uint8_t>(0); index < configMAX_TASK_NAME_LEN; ++index){
            if((reinterpret_cast<TCB_PASS_STR*>(m_pTaskCb))->m_pStack[index] != static_cast<char>(0x00)){
                block.m_threadName[index] = (reinterpret_cast<TCB_PASS_STR*>(m_pTaskCb))->m_pStack[index];
            }
            else{
                //End of the character reached.
                block.m_threadName[index] = static_cast<char>(0x00);
                break;
            }
        }

        /* Justification: The function signature doesn't match the function signature*/
        // clang-format off
        m_pHandel =  xTaskCreateStatic(start,
                                       block.m_threadName,
                                       block.m_stackSize,
                                       (void *const)(this),
                                       block.m_threadPrio,
                                       block.m_pStack,
                                       m_pTaskCb);
        // clang-format on
        start_scheduler();
    }

    bool Thread::is_thread_created() const {
        return (m_pHandel != static_cast<void*>(NULL));
    }

    thread_id_t Thread::get_id() const {
        return m_threadId;
    }

    RTOS_RET_STA_E Thread::notify(notify_value notifyValue, NTF_TYP_E actionType) {
        base_t ret_val = xTaskNotify(m_pHandel, notifyValue, static_cast<eNotifyAction>(actionType));
        return ret_val == pdPASS ? RTOS_RET_STA_E::eRTOSSuccess: RTOS_RET_STA_E::eRTOSFailure;
    }

    void Thread::end_scheduler() {
        vTaskEndScheduler();
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
