#ifndef STOPPABLE_H
#define STOPPABLE_H

#include <iostream>
#include <assert.h>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include <boost/move/move.hpp>

/*
 * Class that encapsulates promise and future object and
 * provides API to set exit signal for the thread
 */
class Stoppable
{
        BOOST_MOVABLE_BUT_NOT_COPYABLE(Stoppable)
        boost::promise<void> exitSignal_;
        boost::unique_future<void> futureObj_;
public:
        Stoppable() : futureObj_(exitSignal_.get_future())
	{
 	}

        Stoppable(BOOST_RV_REF(Stoppable) obj) : exitSignal_(boost::move(obj.exitSignal_)), futureObj_(boost::move(obj.futureObj_))
    {
        std::cout << "Move Constructor is called" << std::endl;
    }
 
    Stoppable & operator=(BOOST_RV_REF(Stoppable) obj)
    {
        std::cout << "Move Assignment is called" << std::endl;
                exitSignal_ = boost::move(obj.exitSignal_);
                futureObj_ = boost::move(obj.futureObj_);
        return *this;
    }
 
	// Task need to provide defination  for this function
	// It will be called by thread function
    virtual void run() = 0;


    // Thread function to be executed by thread
    void operator()()
    {
        run();
    }
 
	//Checks if thread is requested to stop
	bool stopRequested()
	{
		// checks if value in future object is available
                if (futureObj_.wait_for(boost::chrono::milliseconds(0)) == boost::future_status::timeout)
			return false;
		return true;
	}
	// Request the thread to stop by setting value in promise object
	void stop()
	{
                exitSignal_.set_value();
	}
};

#endif // STOPPABLE_H
