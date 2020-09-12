/**
 * @file        IQueue.hpp
 * @author      Manish Tummala (manish.tummala@gmail.com)
 * @brief       Implements the wrapper for the queue.
 * @version     0.1
 * @date        2020-09-02
 * 
 * @copyright   Copyright (c) 2020
 * 
 */

#ifndef RTOS_CPP_WRAPPER_IQUEUE_HPP
#define RTOS_CPP_WRAPPER_IQUEUE_HPP

#include "rtos_types.hpp"

namespace RTOS {
    /**
     * @brief   Interface class for the Queue objects.
     */
    class IQueue {

    public:
        virtual ~IQueue() = 0;

        /**
         * @brief   Places the item at the front of the queue.
         * 
         *          Call to this method block's the calling thread until space is avaliable over
         *          the queue or the time-out expires. Whichever is the earlier.
         * 
         * @param   pv_item_to_queue pointer to the object that has to be queued. 
         * @param   wait_time Time for which the calling thread has to be blocked for queue space to be avaliable.
         * @return  RET_STA_E Returns eRTOSSuccess if an item is received before the time-out else eRTOSFailure.
         */
        virtual RET_STA_E               place_item_at_front(const void * const pv_item_to_queue, delay_t wait_time) = 0;

        /**
         * @brief   Places the item at the front of the queue.
         * 
         *          Call to this method block's the calling thread until space is avaliable indefinitely.
         * 
         * @param   pv_item_to_queue pointer to the object that has to be queued. 
         */
        virtual void                    place_item_at_front_blocked(const void * const pv_item_to_queue) = 0;

        /**
         * @brief   Places the item at the back of the queue.
         * 
         *          Call to this method block's the calling thread until space is avaliable over
         *          the queue or the time-out expires. Whichever is the earlier.
         * 
         * @param   pv_item_to_queue pointer to the object that has to be queued. 
         * @param   wait_time Time for which the calling thread has to be blocked for queue space to be avaliable.
         * @return  RET_STA_E Returns eRTOSSuccess if an item is received before the time-out else eRTOSFailure.
         */
        virtual RET_STA_E               place_item_at_back(const void * const pv_item_to_queue, delay_t wait_time) = 0;

        /**
         * @brief   Places the item at the back of the queue.
         * 
         *          Call to this method block's the calling thread until space is avaliable indefinitely.
         * 
         * @param   pv_item_to_queue pointer to the object that has to be queued. 
         */
        virtual void                    place_item_at_back_blocked(const void * const pv_item_to_queue) = 0;

        /**
         * @brief   Receives the value from the queue.
         * 
         *          Call to this method blocks the thread till the specified time-out is received or
         *          a value is available on the queue. Whichever is the earlier.
         * 
         * @param   pv_buffer buffer for the item to be received.
         * @param   wait_time time for the thread to wait for the item over queue.
         * @return  RET_STA_E Returns eRTOSSuccess if an item is received before the time-out else eRTOSFailure.
         */
        virtual RET_STA_E               get_item(void * const pv_buffer, delay_t wait_time) = 0;

        /**
         * @brief   Receives the value from the queue.
         * 
         *          Call to this method blocks the thread indefinitely until a value is avaliable 
         *          on the queue to be received.
         * 
         * @param   pv_buffer buffer for the item to be received.
         */
        virtual void                    get_item_blocked(void * const pv_buffer) = 0;

        /**
         * @brief   Just gets the item from queue without removing the item from the queue.
         * 
         *          The thread will be in blocked state till a value is posted to the queue. Else, the 
         *          wait time is timed-out. Whichever, is the earlier.
         * 
         * @param   pv_buffer Pointer to the memory that'll be used for holding the item from the queue.
         * @param   wait_time Time-out for the thread to be in blocked state to receive the message. 
         * @return  RET_STA_E Returns eRTOSSuccess if an item is received before time-out else eRTOSFailure.
         */
        virtual RET_STA_E               look_at_item(void * const pv_buffer, delay_t wait_time) = 0;

        /**
         * @brief   Just gets the item from queue without removing the item from the queue.
         *
         *          This function is same as the method: look_at_item excpet that this method blocks the
         *          called thread indefinitely.
         * 
         * @param   buffer Buffer for the item to be copied from the queue.
         */
        virtual void                    look_at_item_blocked(void * const buffer) = 0;
    };
}
#endif //RTOS_CPP_WRAPPER_IQUEUE_HPP
