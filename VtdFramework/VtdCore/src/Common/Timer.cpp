#include <VtdCore/Timer.h>
#include <VtdCore/Logging/Log.h>

#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <cstring>
#include <boost/cast.hpp>

#ifdef VTD_OS_LINUX
#define BOOST_CHRONO_HAS_CLOCK_STEADY
#endif

namespace VTD {

void Timer::start()
{

#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
    startTime_ = boost::chrono::steady_clock::now();
#else
    startTime_ = boost::chrono::system_clock::now();
#endif
        isRunning_ = true;
}

void Timer::stop()
{ 
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
    endTime_ = boost::chrono::steady_clock::now();
#else
    endTime_ = boost::chrono::system_clock::now();
#endif
    isRunning_ = false;
}


double Timer::elapsedTime()
{
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
    boost::chrono::time_point<boost::chrono::steady_clock> endTime;
#else
    boost::chrono::time_point<boost::chrono::system_clock> endTime;
#endif

    if (isRunning_)
    {
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
      endTime = boost::chrono::steady_clock::now();
#else
      endTime = boost::chrono::system_clock::now();
#endif

    }
    else
    {
        endTime = endTime_;
    }

    return boost::numeric_cast<double>( boost::chrono::duration_cast<boost::chrono::milliseconds>(endTime - startTime_).count() );
}


double Timer::elapsedSeconds()
{
    return elapsedTime() / 1000.0;
}

} //namespace VTD
