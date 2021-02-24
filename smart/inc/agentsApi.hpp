#ifndef AGENTS_API_HPP
#define AGENTS_API_HPP

#include "iSubscription.hpp"
#include "iObserver.hpp"
#include "device.hpp"

extern "C"
smart_house::IObserver* CreateObserver(smart_house::ISubscription* a_subscription, smart_house::Device& a_device);
typedef smart_house::IObserver* (*Creator)(smart_house::ISubscription* a_subscription, smart_house::Device& a_device);

#endif