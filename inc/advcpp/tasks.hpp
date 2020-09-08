#ifndef TASKS_HPP
#define TASKS_HPP

#include <exception>
#include "runnable.hpp"
#include "shared_ptr.hpp"
#include "waitableQueue.hpp"

namespace advcpp {

struct EndOfWork : public std::exception {
};

class Tasks : private experis::Uncopyable {
    typedef WaitableQueue<shared_ptr<experis::IRunnable> > WaitQueue;
public:
    Tasks(WaitQueue& a_tasks, experis::AtomicFlag& a_shutDownImmediately);
    //~Tasks() = default;

    void operator()();

private:
    WaitQueue& m_tasks;
    experis::AtomicFlag& m_shutDownImmediately;
};

} // advcpp

#endif