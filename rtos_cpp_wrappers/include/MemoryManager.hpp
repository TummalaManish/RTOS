/**
 * @file        MemoryManager.hpp
 * @author      Tummala Manish (manish.tummala@gmail.com)
 * @brief       This file implements the memory manager for that uses the RTOS memory
 *              allocation function.
 * @version     0.1
 * @date        2020-07-17
 * 
 * @copyright   Copyright (c) 2020
 * 
 */

#include "rtos_types.hpp"
#include "portable.h"

namespace RTOS{

    /**
     * @brief:  enumerates the different type of results memory manger can return.
     */
    enum eMemoryResult{
        eMemAllocationFailed = 0,    /**< if the allocation has succeeded. */
        eMemAllocationSuccess,       /**< if the allocation has failed.    */
    };

    /**
     * @brief   Implements the memory manager using the underlying RTOS memory allocation
     *          schemes.
     *
     *          This class is a singleton i.e. only a single object of this type maintained.
     *          Any allocation should be done after a call to the get_instance static function.
     *
     */
    class MemoryManager{
        /*------------- Static Members -------------*/
        /**
         * @brief   The singleton instance of the of the memory manager.
         */
        static MemoryManager m_rMemoryManager;

        //This can be improved to maintain memory usage.
        explicit MemoryManager(); /**< No object can be instantiated using this class */

    public:

        /**
         * @brief   Returns the singleton of the memory manager.
         *
         *          There has to be only one object of this class.
         *
         * @return MemoryManager& returns the reference to the singleton.
         */
        static MemoryManager& get_Instance();

        /**
         * @brief   Allocats the required memory as asked.
         *
         * @param   ppMemHolder [out] This argument will passout the pointer to the allocated memory block.
         * @param   iNumBytes  [in] This is the amount of the bytes that are to be reserved.
         * @return  eMemoryResult Returns eMemAllocationSuccess if the memory allocation is success
         *          -full. Else, eMemAllocationFailed is returned.
         */
        eMemoryResult get_block(void** pMemHolder, size_t iNumBytes);

        /**
         * @brief   Frees the block allocated to the user.
         *
         *          This function can be called by any one in the code and the asked block of memory will be
         *          freed and added to the pool. However, this is a very expensive call hence memory calls
         *          have to be kept as minimum as possible.
         *
         * @param   pMemHolder Pointer that holds the start address of the memory that has been allocated.
         */
        void release_block(void* pMemHolder);

        /**
         * @brief   Allocates the stack for the thread.
         * 
         *          This function is used to allocated the stack buffer for a thread. This function
         *          has a overhead and has to be used only when we know a task will be deleted. The
         *          Thread class will call this function to create a killable thread.
         * 
         * @param   ppStack [out] This argument will passout the pointer to the allocated stack block.
         * @param   StackSize [in] This is the amount of the stack that has to be allocated.
         * @return  eMemoryResult Returns eMemAllocationSuccess if the memory allocation is success
         *          -full. Else, eMemAllocationFailed is returned.
         */
        eMemoryResult get_stack(rtos_thread_stack_t& ppStack, rtos_stack_size_t StackSize);

        /**
         * @brief   Frees the allocated stack of the thread.
         * 
         *          This method is called by the thread task only. As the stack pointers are normally
         *          held by the thread class and its children. Behind the screen this function will
         *          call the FreeRTOS vPortFree().
         * 
         * @param   ppStack pointer to the stack that has been assigned. 
         */
        void release_stack(rtos_thread_stack_t ppStack);

        /**
         * @brief   Allocates the memory for the FreeRTOS control block.
         * 
         * @param   ppTCB [out] This argument will passout the pointer to the allocated TCB
         * @return  eMemoryResult 
         */
        eMemoryResult get_TCB(rtos_thread_cb_t& ppTCB);

        /**
         * @brief   Frees the allocated TCB of the thread.
         * 
         *          This method is called by the thread task only. As the TCB pointers are normally
         *          held by the thread class and its children. Behind the screen this function will
         *          call the FreeRTOS vPortFree().
         * 
         * @param   ppStack pointer to the stack that has been assigned. 
         */
        void release_TCB(rtos_thread_cb_t ppTCB);
    };
}