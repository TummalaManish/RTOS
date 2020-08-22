/**
 * @file        ThreadMock.hpp
 * @author      Manish Tummala (Email: tummalamanish@gmail.com)
 * @brief       Implements the mock thread class that has to be inherited by all the thread based objects.
 * @version     0.1
 * @date        2020-07-22
 *
 * @copyright   Copyright (c) 2020
 *
 */

#ifndef RTOS_CPP_WRAPPER_THREADMOCK_CPP_HPP
#define RTOS_CPP_WRAPPER_THREADMOCK_CPP_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Thread.hpp>

using namespace RTOS;

//Note: thread class cannot be tested yet.
namespace TEST{

    class ThreadMock: public Thread{

        void run() override{
            suspend();
            vTaskSuspendAll();
        }

    public:
        ThreadMock(thread_name_t thread_name, thread_priority_t thread_priority, stack_size_t stack_size)
                    :Thread(thread_name, thread_priority, stack_size){
        }

        return_status_e    thread_delete() override{
            Thread::~Thread();
            return RTOS_RET_STA_E::eRTOSSuccess;
        }
    };
}
#endif //RTOS_CPP_WRAPPER_THREADMOCK_CPP_HPP
