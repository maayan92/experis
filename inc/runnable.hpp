#ifndef RUNNABLE_HPP
#define RUNNABLE_HPP

#include "uncopyable.hpp"

namespace experis {

class IRunnable : private Unassignable {
public:
    //IRunnable() = default;
    //IRunnable(const Runnable &a_other) = default;
    virtual ~IRunnable() {}
    virtual void operator()() = 0;
};

} // experis

#endif