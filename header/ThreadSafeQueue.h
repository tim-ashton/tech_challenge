#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace tech_challenge {

/*
A thread safe queue
*/
template <class T>
class ThreadSafeQueue
{
        std::queue<T> m_queue;
        mutable std::mutex m_mutex;
        std::condition_variable m_condition;

public:
  ThreadSafeQueue()
  {}

  ~ThreadSafeQueue(void)
  {}

  int size()
  {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_queue.size();
  }

  void push(T &&t)
  {
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_queue.push(std::move(t));
    }
    m_condition.notify_one();
  }

  bool try_pop(T& result_out, const std::chrono::milliseconds &timeout)
  {
    std::unique_lock<std::mutex> lock(m_mutex);

    if(!m_condition.wait_for(lock, timeout, [this] { return !m_queue.empty(); }))
        return false;

    result_out = std::move(m_queue.front());
    m_queue.pop();
    return true; 
  }
};

}