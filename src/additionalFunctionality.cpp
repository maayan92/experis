#include "additionalFunctionality.hpp"

namespace experis {

void GoToSleep(size_t a_nanoseconds)
{
    const size_t FROM_NANO_TO_SEC = 1000000000;
    struct timespec timeToSleep =  { time_t(a_nanoseconds / FROM_NANO_TO_SEC), long(a_nanoseconds % FROM_NANO_TO_SEC) };

    struct timespec remainingTime;
    int status;
    do {
        status = nanosleep(&timeToSleep, &remainingTime);
        if(0 != status) {
            assert(EFAULT != status);
            assert(EINVAL != status);

            if(EINTR == status) {
                timeToSleep = remainingTime;
            }
            else {
                assert(!"undocumented error for nanosleep");
            }
        }

    } while(0 != status);
}



} // experis