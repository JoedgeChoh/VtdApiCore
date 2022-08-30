 
#include <gtest/gtest.h>
#include <VtdThreads/Thread.h>
#include <VtdCore/Macros.h>
#include <VtdCore/Timer.h>

using namespace VTD;

namespace {

class MyThread : public Thread {
public:
    MyThread(){ /**/ }

    virtual void run() VTD_OVERRIDE
    {
        processQueue(10);
        EXPECT_EQ(getId(), Thread::getCurrentId());
    }

    void processQueue(unsigned N)
    {
        float ms = N * 1e3;
        boost::posix_time::milliseconds workTime(ms);

        std::cout << "Worker: started, will work for "
                  << ms << "ms"
                  << std::endl;

        // We're busy, honest!
        boost::this_thread::sleep(workTime);

        std::cout << "Worker: completed" << std::endl;
    }
};

}

TEST(ThreadTest, ThreadIdTest)
{
    MyThread threadA, threadB, threadC, threadD;
    threadA.start();
    threadB.start();
    threadC.start();
    threadD.start();
    threadA.join();
    threadB.join();
    threadC.join();
    threadD.join();
}

class MySleepyThread : public Thread
{
public:
    MySleepyThread(unsigned long usecs) : usecs_(usecs)
    { /**/ }

    virtual void run() VTD_OVERRIDE
    {
        Thread::sleep(usecs_);
    }

private:
    unsigned long usecs_;
};

TEST(ThreadTest, ThreadSleepTest)
{
    MySleepyThread thread(50000); //wait for 50ms

    Timer t;
    t.start();
    thread.start();
    bool result = thread.join();
    EXPECT_EQ(t.elapsedTime(), 50.0);
    EXPECT_TRUE(result);
}

TEST(ThreadTest, ThreadTimedJoinTest)
{
    MySleepyThread thread(500000); //wait for 500ms

    Timer t;
    t.start();
    thread.start();

    bool result = thread.join(50000); //join will time out before thread is finished
    EXPECT_FALSE(result);

    result = thread.join();
    EXPECT_TRUE(result);

    EXPECT_GT(t.elapsedTime(), 50.0);
}
