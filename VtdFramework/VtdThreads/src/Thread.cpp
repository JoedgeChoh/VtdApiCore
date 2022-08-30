#include "VtdThreads/Thread.h"

#include <VtdCore/Logging/Log.h>
#include <VtdCore/Macros.h>

#include <boost/bind.hpp>

namespace VTD {

Thread::Thread()
{ /**/ }

Thread::~Thread()
{ /**/ }

boost::thread::id Thread::getId() const
{
    return id_;
}

void* Thread::startFunc(void* args)
{    //set name on the calling thread.
    Thread* thread = static_cast<Thread*>(args);

    thread->run();

    return NULL;
}

void Thread::start()
{
    thread_ = boost::thread(&Thread::startFunc, this);

    id_ = thread_.get_id();

}

void Thread::run()
{
    /* execute some task */
}

bool Thread::join()
{
    if (thread_.joinable())
        thread_.join();

    return true;
}

bool Thread::join(UInt64 time)
{
    if (thread_.try_join_for(boost::chrono::microseconds(time)))
    {
        thread_.join();
        VTD_LOG_ERR("VtdThreads: thread_try_join_for_joined");
        return true;

    }
    else
    {
        VTD_LOG_ERR("VtdThreads: thread_try_join_for_could_not_be_joined");
        return false;
    }
}

boost::thread::id Thread::getCurrentId()
{
    return boost::this_thread::get_id();
}

void Thread::sleep(const UInt64& microSeconds)
{
    boost::this_thread::sleep_for(boost::chrono::microseconds(microSeconds));
}

void Thread::sleepNanoSec(const UInt64& nanoSeconds)
{
    boost::this_thread::sleep_for(boost::chrono::nanoseconds(nanoSeconds));
}

void Thread::yield()
{
    boost::this_thread::yield();
}


} //namespace VTD
