#include <VtdCore/Timer.h>
#include <VtdCore/Logging/Log.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <cstring>

namespace {
    const clockid_t CLOCK = CLOCK_MONOTONIC;
}

namespace VTD {

Timer::Timer() {

    //check resolution
    struct timespec res;
    if(clock_getres(::CLOCK, &res) < 0) {
        VTD_LOG_ERRNO("VtdToolkit: Timer error: ");
    }

    if(res.tv_nsec > 1000000) {
        //resolution too coarse for millisecond accuracy.
        VTD_LOG_ERR("VtdToolkit: Timer accuracy of " << res.tv_nsec << " nanoseconds is not sufficient for millisecond accuracy");
    }

    start();
}

void Timer::start() {
    startTime = getCurrentTime();
}

double Timer::elapsedTime() {
    TimeValue currentTime = getCurrentTime();
    double elapsedTime = static_cast<double>(currentTime.seconds - startTime.seconds) * 1000.0;
    elapsedTime += static_cast<double>(currentTime.microSeconds - startTime.microSeconds) / 1000.0;
    return elapsedTime;
}

Timer::TimeValue Timer::getCurrentTime() {
    struct timespec tp;
    if(clock_gettime(::CLOCK, &tp) < 0) {
        VTD_LOG_ERRNO("VtdToolkit: Timer error: ");
    }

    TimeValue timeValue;
    timeValue.seconds = tp.tv_sec;
    timeValue.microSeconds = tp.tv_nsec/1000;
    return timeValue;
}

} //namespace VTD
