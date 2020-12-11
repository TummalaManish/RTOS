/**
 * @file        QueueCreateAndRun.cpp
 * @author      Tummala Manish (manish.tummala@gmail.com)
 * @brief       Func test for the queue wrapper.
 * @version     0.1
 * @date        2020-09-26
 *
 * @copyright   Copyright (c) 2020
 *
 */

#include "TQueue.hpp"
#include "Thread.hpp"
#include <iostream>

struct msg {
  uint8_t msgId;
  char name[12];
};
using msg = struct msg;

class RThread : public RTOS::Thread {
public:
  explicit RThread(RTOS::IQueueReceiver &r_que)
      : m_Iqueue(r_que), m_tempHolder(), Thread("RcvThr", 1, 100) {}

private:
  [[noreturn]] void run() override {
    // This thread will receive three messages from the sender.
    uint8_t cnt = 0;
    for (;;) {
      if (cnt == 3)
        end_scheduler();
      // Waiting or the message from the sender.
      m_Iqueue.dequeue(static_cast<void *>(&m_tempHolder));
      std::cout << "Message " << static_cast<int>(m_tempHolder.msgId) << ": "
                << static_cast<const char *>(m_tempHolder.name) << std::endl;
      ++cnt;
    }
  }
  RTOS::IQueueReceiver &m_Iqueue;
  msg m_tempHolder{};
};

class SThread : public RTOS::Thread {
public:
  SThread(RTOS::IQueueSender &r_que, RTOS::IThread &r_thr)
      : m_Iqueue(r_que), m_Islave(r_thr), Thread("SndThr", 1, 100) {}

private:
  [[noreturn]] void run() override {
    // This thread will send three messages to the queue.
    msg msg_lst[3] = {{1, "Hello"}, {2, "Hello w"}, {3, "Hello wo"}};
    // Join the received to the kernel.
    m_Islave.join();
    for (;;) {
      for (int i = 0; i < 3; ++i) {
        m_Iqueue.enqueue(&msg_lst[i]);
      }
      suspend();
    }
  }

  RTOS::IQueueSender &m_Iqueue;
  RTOS::IThread &m_Islave;
};

int main() {
  static RTOS::TQueue<msg, 10> msg_q;
  RThread thr_r(msg_q);
  SThread thr_s(msg_q, thr_r);
  thr_s.join();
}

void vAssertCalled(unsigned long ulLine, const char *const pcFileName) {
  printf("ASSERT: %s : %d\n", pcFileName, (int)ulLine);
  while (1)
    ;
}
