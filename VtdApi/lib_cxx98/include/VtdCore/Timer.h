#ifndef VTDFRAMEWORK_TIMER_H
#define VTDFRAMEWORK_TIMER_H

#include <VtdCore/Macros.h>
#include <boost/chrono.hpp>

namespace VTD {

    class Timer {

        public:

            Timer() : isRunning_(false){}

            void start();
            void stop();
            double elapsedTime(); //elapsed time in milliseconds
            double elapsedSeconds();
    private:

        typedef struct {
            long seconds;
            long microSeconds;
        } TimeValue;

    public:
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
        boost::chrono::time_point<boost::chrono::steady_clock> getStartTime(){return startTime_;}
        boost::chrono::time_point<boost::chrono::steady_clock> getEndTime(){return endTime_;}
#else
        boost::chrono::time_point<boost::chrono::system_clock> getStartTime(){return startTime_;}
        boost::chrono::time_point<boost::chrono::system_clock> getEndTime(){return endTime_;}
#endif
    private:
#ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
        boost::chrono::time_point<boost::chrono::steady_clock> endTime_;
        boost::chrono::time_point<boost::chrono::steady_clock> startTime_;
#else
        boost::chrono::time_point<boost::chrono::system_clock> endTime_;
        boost::chrono::time_point<boost::chrono::system_clock> startTime_;
#endif


        bool isRunning_;
    };

 namespace Util {
        VTD_DEPRECATED("Use VTD::Timer instead", typedef VTD::Timer Timer);
    } //namespace Util

} //namespace VTD

#endif // VTDFRAMEWORK_TIMER_H
