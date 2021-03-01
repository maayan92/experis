#ifndef CONTROLLERS_API_HPP
#define CONTROLLERS_API_HPP

#include "iSubscription.hpp"
#include "iObserver.hpp"

extern "C"
smart_house::IObserver* CreateObserver(smart_house::ISubscription* a_subscription, std::vector<smart_house::EventTypeLoc>& a_typeLoc);
typedef smart_house::IObserver* (*Creator)(smart_house::ISubscription* a_subscription, std::vector<smart_house::EventTypeLoc>& a_typeLoc);

#endif