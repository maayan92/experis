#ifndef SINGLETON_MULTI_THREADS
#define SINGLETON_MULTI_THREADS

#include "uncopyable.hpp"
#include "atomic.hpp"

namespace advcpp {

template<typename T>
class Singleton : private experis::Uncopyable {
public:
    static T& Instance();
    //~Singleton() = default;

private:
    Singleton();
    static bool firstOneToCome();
    static void createSingleton();
    static void waitTillSingletonIsCreated();

private:
    static T* instance;
    static experis::AtomicFlag firstThread;
    static experis::AtomicFlag wasCreated;
};

} // advcpp

#include "inl/singleton.hxx"

#endif