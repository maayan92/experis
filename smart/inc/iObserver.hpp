#ifndef IOBSERVER_HPP
#define IOBSERVER_HPP

#include "event.hpp"

namespace smart_house {

class IObserver {
public:
    virtual ~IObserver();
    
    virtual void Notify(const Event& a_newEvent) = 0;

protected:
    IObserver();
};

} // smart_house

#endif