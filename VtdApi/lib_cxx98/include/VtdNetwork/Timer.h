#ifndef _TIMER_H
#define _TIMER_H

#include <iostream>
#include <boost/chrono.hpp>
#include <ctime>
#include <cmath>

namespace VTD
{
    static const unsigned int MILLISEC_IN_SEC = 1000;

    class Timer
    {
    public:

        Timer() : isRunning_(false){}

        void start()
        {
            startTime_ = boost::chrono::system_clock::now();
            isRunning_ = true;
        }

        void stop()
        {
            endTime_ = boost::chrono::system_clock::now();
            isRunning_ = false;
        }

        double elapsedMilliseconds()
        {
            boost::chrono::time_point<boost::chrono::system_clock> endTime;

            if (isRunning_)
            {
                endTime = boost::chrono::system_clock::now();
            }
            else
            {
                endTime = endTime_;
            }

            return static_cast<double>( boost::chrono::duration_cast<boost::chrono::milliseconds>(endTime - startTime_).count() );
        }

        double elapsedSeconds()
        {
            return elapsedMilliseconds() / 1000.0;
        }

        boost::chrono::time_point<boost::chrono::system_clock> getStartTime(){return startTime_;}

        boost::chrono::time_point<boost::chrono::system_clock> getEndTime(){return endTime_;}

    private:

        boost::chrono::time_point<boost::chrono::system_clock> startTime_;

        boost::chrono::time_point<boost::chrono::system_clock> endTime_;

        bool isRunning_;
    };
}


#endif // _TIMER_H
