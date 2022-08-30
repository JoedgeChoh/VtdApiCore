#include <VtdThreads/Thread.h>
#include <VtdCore/Logging/Log.h>
#include <VtdCore/Macros.h>

#include <sched.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <unistd.h>

namespace VTD {

Thread::Thread() :
    id_(0),
    name_("")
{ /**/ }

Thread::Thread(const std::string& name) :
    id_(0),
    name_(name)
{ /**/ }

Thread::~Thread()
{ /**/ }

UInt64 Thread::getId() const
{
    return id_;
}

const std::string& Thread::getName() const
{
    return name_;
}

void* Thread::startFunc(void* args)
{    //set name on the calling thread.
    Thread* thread = static_cast<Thread*>(args);

    if(!thread->name_.empty()) {
        prctl(PR_SET_NAME, thread->name_.c_str());
    }
    else {
        char name[16];
        prctl(PR_GET_NAME, name);
        thread->name_ = name;
    }

    thread->run();
}

void Thread::start()
{
    int retVal;

    pthread_attr_t attr;
    retVal = pthread_attr_init(&attr);
    if (retVal != 0) {
        VTD_LOG_ERR("VtdToolkit: pthread_attr_init" << strerror(retVal));
    }

    pthread_t threadId;
    retVal = pthread_create(&threadId, &attr, &startFunc, static_cast<void*>(this));
    if(retVal != 0) {
        VTD_LOG_ERR("VtdToolkit: pthread_create" << strerror(retVal));
    }
    id_ = threadId;

    retVal = pthread_attr_destroy(&attr);
    if (retVal != 0) {
        VTD_LOG_ERR("VtdToolkit: pthread_attr_destroy" << strerror(retVal));
    }
}

void Thread::run()
{
    /* execute some task */
}

bool Thread::join()
{
    int err = pthread_join(id_, NULL);
    if(err != 0) {
        VTD_LOG_ERR("VtdToolkit: pthread_join" << strerror(err));
        return false;
    }
    return true;
}

bool Thread::join(TimeValue time)
{
    struct timespec abstime = { time.seconds, time.microSeconds/1000 };
    int err = pthread_timedjoin_np(id_, NULL, &abstime);
    if(err != 0) {
        VTD_LOG_ERR("VtdToolkit: pthread_timedjoin_np" << strerror(err));
        return false;
    }
    return true;
}

UInt64 Thread::getCurrentId()
{
    return static_cast<UInt64>(::pthread_self());
}

void Thread::sleep(UInt64 microSeconds)
{
    ::usleep(microSeconds);
}

void Thread::yield()
{
    ::sched_yield();
}


} //namespace VTD
