#include <gtest/gtest.h>
#include <VtdCore/Timer.h>
#include <VtdCore/BasicTypes.h>
#include <VtdCore/Macros.h>

#include <unistd.h>

using namespace VTD;

namespace Thread
{
    static void sleep(UInt64 microseconds);
}

#ifdef VTD_OS_LINUX
void Thread::sleep(UInt64 microseconds)
{
    ::usleep(microseconds);
}

#else
VTD_COMPILETIME_WARNING("Test is not yet supported on this platform. Test will fail.")
void Thread::sleep(UInt64 microseconds)
{ /**/ }
#endif

TEST(TimerTest, TimerTest)
{
    Timer t;
    EXPECT_NEAR(0.0, t.elapsedTime(), 0.001);

    t.start();

    Thread::sleep(100000);

    EXPECT_GT(100.1, t.elapsedTime());
    EXPECT_LT(99.9, t.elapsedTime());
}

