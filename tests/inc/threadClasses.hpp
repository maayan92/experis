#ifndef THREAD_CLASSES_HPP
#define THREAD_CLASSES_HPP

#include "waitableQueue.hpp"
#include "runnable.hpp"

namespace experis {

template<typename T>
class waitableQueueEnque : public experis::IRunnable {
public:
    waitableQueueEnque(advcpp::WaitableQueue<T>& a_waQueue, std::vector<T>& a_values)
    : m_waQueue(a_waQueue)
    , m_values(a_values)
    {}

    void operator()() {
        for(size_t i = 0 ; i < m_values.size() ; ++i) {
            m_waQueue.Enque(m_values[i]);
        }
    }

private:
    advcpp::WaitableQueue<T>& m_waQueue;
    std::vector<T> m_values;
};

template<typename T>
class waitableQueueDeque : public experis::IRunnable {
public:
    waitableQueueDeque(advcpp::WaitableQueue<T>& a_waQueue, std::vector<T>& a_result)
    : m_waQueue(a_waQueue)
    , m_result(a_result)
    {}
    
    void operator()() {
        for(size_t i = 0 ; i < m_result.size() ; ++i) {
            T val;
            m_waQueue.Deque(val);
            m_result[i] = val;
        }
    }

    std::vector<T> GerResult() const { return m_result; }

private:
    advcpp::WaitableQueue<T>& m_waQueue;
    std::vector<T>& m_result;
};

} // experis

#endif