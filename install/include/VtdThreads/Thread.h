#ifndef VTD_FRAMEWORK_THREAD_H
#define VTD_FRAMEWORK_THREAD_H

#include <string>

#include <VtdCore/BasicTypes.h>
#include<boost/thread.hpp>

/**
 *  system indepented implementation just is remained in linux folder
 */

namespace VTD {

class Thread {

public:

    explicit Thread();

    virtual ~Thread();

    boost::thread::id getId() const;

    virtual void start();

    virtual void run();

    bool join();

    bool join(UInt64 time);

    static boost::thread::id getCurrentId();

    static void sleep(const UInt64& microSeconds);
    
    static void sleepNanoSec(const UInt64& microSeconds);

    static void yield();

private:
    boost::thread::id id_;
    std::string name_;
    boost::thread thread_;

    static void* startFunc(void* args);
};

} //namespace VTD

#endif //VTDFRAMEWORK_THREAD_H
