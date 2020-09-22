#ifndef TESTS_FUNCTIONS_HPP
#define TESTS_FUNCTIONS_HPP

#include <vector>
#include "event.hpp"
#include "controllerTest.hpp"
#include "payloadSmoke.hpp"

smart_house::Event CreateEvent(const smart_house::EventTypeLoc& a_typeLoc)
{
    time_t t;
    time(&t);
    smart_house::PayloadSmoke ps;
    smart_house::Event event = {localtime(&t), &ps, a_typeLoc};
    return event;
}

template<size_t SIZE>
bool CheckResult(const smart_house::EventTypeLoc& a_typeLoc, smart_house::ControllerTest* a_controllers)
{
    for(size_t i = 0; i < SIZE; ++i) {
        if(!(a_typeLoc == a_controllers[i].GetEventTypeLocation())) {
            return false;
        }
    }

    return true;
}

template<size_t SIZE>
bool CheckResult(const smart_house::EventTypeLoc& a_typeLoc, const std::vector<smart_house::ControllerTest*>& a_controllers)
{
    for(size_t i = 0; i < SIZE; ++i) {
        if(!(a_typeLoc == a_controllers[i]->GetEventTypeLocation())) {
            return false;
        }
    }

    return true;
}

#endif