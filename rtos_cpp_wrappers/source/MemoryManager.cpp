/**
 * @file        MemoryManager.cpp
 * @author      Tummala Manish (manish.tummala@gmail.com)
 * @brief       This file implements the memory manager for that uses the RTOS memory
 *              allocation function.
 * @version     0.1
 * @date        2020-07-17
 * 
 * @copyright   Copyright (c) 2020
 * 
 */

#include "MemoryManager.hpp"

namespace RTOS{

    //Warning: Usage of a singleton. The presence is essential for the operation.
    MemoryManager MemoryManager::m_rMemoryManager;

    MemoryManager::MemoryManager() {
    /*TODO: This implementation can be improved to have book keeping of the memory.*/
    }

    MemoryManager& MemoryManager::get_Instance(){
        return m_rMemoryManager;
    }

    /*Note: This is not a const function because we might want to add book keeping feature
            to the memory manager. Same reason these are not static functions*/
    eMemoryResult MemoryManager::get_stack(rtos_thread_stack_t& ppStack, rtos_stack_size_t StackSize){

        ppStack = static_cast<StackType_t*>(pvPortMalloc(StackSize*sizeof(StackType_t)));
        return ppStack != NULL ? eMemAllocationSuccess : eMemAllocationFailed;
    }

    void MemoryManager::release_stack(rtos_thread_stack_t ppStack) {
        vPortFree(ppStack);
    }

    /*Note: This is not a const function because we might want to add book keeping feature
            to the memory manager. Same reason these are not static functions*/
    eMemoryResult MemoryManager::get_TCB(rtos_thread_cb_t& ppTCB){
        
        ppTCB = static_cast<StaticTask_t*>(pvPortMalloc(sizeof(StaticTask_t)));
        return ppTCB != NULL ? eMemAllocationSuccess : eMemAllocationFailed;
    }

    void MemoryManager::release_TCB(rtos_thread_cb_t ppTCB) {
        vPortFree(ppTCB);
    }

    /*Note: This is not a const function because we might want to add book keeping feature
            to the memory manager. Same reason these are not static functions*/
    eMemoryResult MemoryManager::get_block(void**  pMemHolder, size_t iNumBytes){
        
        *pMemHolder = pvPortMalloc(iNumBytes);
        return *pMemHolder != NULL ? eMemAllocationSuccess : eMemAllocationFailed;
    }

    void MemoryManager::release_block(void *pMemHolder) {
        vPortFree(pMemHolder);
    }
}

//TODO: How the failed memory allocations have to be dealt with.
extern "C" void vApplicationMallocFailedHook(void);
void vApplicationMallocFailedHook(void){
    //TODO: memory allocation fails have to the handled more appropiatly.
#ifdef SIM
    __debugbreak();
#endif
}

