#include "absController.hpp"

namespace smart_house {

Controller::~Controller()
{}

void Controller::CreateEvent(const SensorInfo& a_info, struct Event& a_event)
{
    (void)a_info;
    (void)a_event;
}

} // smart_house
