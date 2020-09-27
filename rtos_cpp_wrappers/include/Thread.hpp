/**
 * @file        Thread.hpp
 * @author      manish Tummala (manish.tummala@domain.com)
 * @brief       Provides the implementation for the thread class.
 * @version     0.1
 * @date        2020-07-23
 * 
 * @copyright   Copyright (c) 2020
 */

#ifndef RTOS_THREAD_HPP
#define RTOS_THREAD_HPP

#include "IThread.hpp"
#include "ISignal.hpp"

namespace RTOS{

    /**
     * @brief This class implements the thread i.e. the wrapper for the FreeRTOS Task.
     */
    class Thread : public IThread, public ISignal{

    public:
        /**
         * @brief   Enumerates the different return types from signal apis.
         */
        enum class signal_return_values{
            eTimeOut = 0,                             /**<When the time has passed out of given deadline.             */
            eExpectedSignalReceived,                  /**<When the Expected signal is received.                       */
            eUnexpectedSignalReceived,                /**<When an unexpected signal is received.                      */
        };
        using SIG_RET_VAL = signal_return_values;

        /**
         * @brief   Struct used to pass the notification value that encapsulates both value and time-out status.
         */
        struct notify_value{
            // The below wiggles are due to problem with the cpp-check.
            bool timed_out;                           /**<Holds the time-out information of the notification.         */
            uint32_t received_value;                  /**<Holds the 32-bit notification value.                        */
        };
        using NTF_VALUE_S = struct notify_value;

    private:
        static id_t m_sThreadCount;                   /**<Holds the count of the threads that have been created       */

        /*---------------- Non Static member variables -------------*/
        status_e           m_threadStatus;            /**<Hold the status of the thread.                              */
        id_t               m_threadId;                /**<Holds the id of the current thread.                         */
        thr_handle_t       m_pHandle;                 /**<Points to the task handle of the created thread.        */
        stack_t            m_pStack;                  /**<Points to the stack of the thread created.                  */
        control_block_t    m_pTaskCb;                 /**<Points to the task's control block.                         */
    public:

        explicit Thread() = delete;                  /**<Default constructor is deleted.                              */

        /**
         * @brief   Make's a mask with the specified bit set.
         *
         * @param   value Any number between 0 and 31.
         * @return  returns a 32 bit value with the bit specified set.
         */
        static uint32_t SIG_BIT(unsigned int value);

        /**
         * @brief   Thread constructor.
         * 
         * @param   thread_name Name of the thread.
         * @param   thread_priority Thread priority.
         * @param   thread_stack_size Thread stack size.
         * @param   thread_id Thread id by default will be 0.
         */
        Thread(name_t               thread_name,     /**<Single constructor for the thread class.                     */
               priority_t           thread_priority,
               stack_size_t         thread_stack_size,
               id_t                 thread_id = 0);

        ~Thread() override;
        /*------------------ Static Methods -------------------*/
        /**
         * @brief   Starts the freeRTOS scheduler if not running.
         */
        static  void            start_scheduler();

        /**
         * @brief   Ends the scheduler.
         */
        static  void            end_scheduler();

        /**
         * @brief   Used to identify if the scheduler is running or not.
         * @return  True if the scheduler is currently running.
         */
        static  bool            is_scheduler_running();

    private:
        /**
         * @brief   Thread starter functions that'll be passed into the kernel.
         */
        static  void            start(void*);

    public:
        /*---- Methods that are from the IThread interface ----*/
        id_t                    get_id() const override;
        priority_t              get_priority() const override;
        return_status_e         set_priority(priority_t) override;
        char const*             get_name() const override;
        status_e                get_status() const override;

        void                    signal_on_bits(uint32_t bitsToSet) override;
        void                    send_value_with_over_write(uint32_t valueToSend) override;
        RET_STA_E               send_value_with_no_over_write(uint32_t valueToSend) override;
        void                    suspend() const override;
        void                    resume() const override;
        bool                    is_thread_created() const override;
        RET_STA_E               notify(notify_value_t, NTF_TYP_E) override;
        void                    join() override;
        // This is a simple default implementation inheriting class have to override.
        RET_STA_E               thread_delete() override;



    protected:

        /**
         * @brief   Yields the thread from execution.
         */
        static  void            yield();
        /**
         * @brief   Calling this function will move the thread to blocked state for a
         *          given amount of time.
         * @param   This should be a non-negative value describing the number of milli
         *          -seconds the thread has to be in blocked state before being resumed.
         */
        static  void            delay_ms(delay_t);
        /**
         * @brief   Call to this member paces the thread in blocked state till the thread
         *          is notified by some other task or the time-out expires.
         * 
         * @param   entryClearMask      MASK to clear the bits of notification value on entry.
         * @param   exitClearMask       MASK to cleat the bits of notification value on exit.
         * @param   msDelay             Time-out for the wait.
         * @param   notificationValue   Pointer to the memory that notify uses to place the notification value.
         * @return  RET_STA_E           True if the notification is received well before the time-out else false.
         */
        static RET_STA_E        wait_for_notification(uint32_t entryClearMask, uint32_t exitClearMask,
                                                      delay_t msDelay, uint32_t* pNotificationValue = nullptr);
        /**
         * @brief   Call to this method blocks the thread for the given time or until the
         *          signal on specified bit is received which ever is sooner.
         *
         *          If the wait-time times out. The function returns times-out if not the
         *          signal received is expected or not.
         *
         * @param   signalMask  32 bit mask. Bits set in uint32_t value to receive the signal over.
         * @param   blockTime   Time for which the thread will be placed on blocked list.
         * @return  SIG_RET_VAL returns one of the possible enum values.
         */
        static SIG_RET_VAL      wait_for_signal_on_bits(uint32_t signalMask, delay_t blockTime);

        /**
         * @brief   Call to this method blocks the thread for the given time or until the
         *          signal on specified bit is received i.e forever.
         * 
         * @param   signalMask  32 bit mask. Bits set in uint32_t value to receive the signal over.
         * @return SIG_RET_VAL  returns one of the possible enum values.
         */
        static SIG_RET_VAL      wait_for_signal_on_bits_blocked(uint32_t signalMask);

        /**
         * @brief   Call to this method blocks the thread for the given time or until the
         *          value is received which ever is sooner.
         *
         * @param   blockTime time for which the task will be waiting for the value.
         * @return  returns the NTF_VALUE_S with the received notification.
         */
        static NTF_VALUE_S      wait_for_value(delay_t blockTime);

        /**
         * @brief   Call to this method blocks the thread for the given time or until the
         *          value is received i.e forever.
         * 
         *          For this method the NTF_VALUE_S.timed_out is always false as there is
         *          no time out.
         * 
         * @return  NTF_VALUE_S Returns the value received as a signal.
         */
        static NTF_VALUE_S      wait_for_value_blocked();

        /**
         * @brief   thread_run function that all the inherited classes have to implement.
         */
        virtual void            run() = 0;
    };
}
#endif //RTOS_THREAD_HPP
