#include <gtest/gtest.h>
#include <VtdThreads/Thread.h>
#include <VtdThreads/CriticalSection.h>
#include <VtdCore/Macros.h>

using namespace VTD;

namespace {

UInt randomInt(UInt min, UInt max) {
    return rand()%((max+1)-min) + min;
}

class MyThread : public Thread
{
public:
    MyThread(UInt& value, CriticalSection& cs) :
        Thread(),
        value_(value),
        cs_(cs)
    { /**/ }

    virtual void run() VTD_OVERRIDE
    {
        for(int i=0; i<1000; ++i) {
            {
                ScopedLock<CriticalSection> lock(cs_);
                EXPECT_EQ(0, value_);
                value_ += i;
                value_ -= i;
                yield();
            }
        }
    }

private:
    UInt& value_;
    CriticalSection& cs_;
};

}

TEST(CriticalSectionTest, CriticalSectionTest)
{
    UInt value = 0;
    CriticalSection cs;
    const UInt nThreads = 100;

    MyThread* threads[nThreads];
    for(UInt i = 0; i < nThreads; ++i) {
        threads[i] = new MyThread(value, cs);
    }

    for(UInt i = 0; i < nThreads; ++i) {
        threads[i]->start();
    }

    for(UInt i = 0; i < nThreads; ++i) {
        threads[i]->join();
        delete threads[i];
    }
}
