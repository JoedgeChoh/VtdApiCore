#include <gtest/gtest.h>
#include <VtdNetwork/message.h>
#include <VtdNetwork/MessageCallback.h>

const std::string DEFAULT_HOST = "127.0.0.1";

using namespace VTD;

namespace
{
    static const ConnectionHandle CAPTURE_ALL_HANDLE = -666;
    static const ConnectionHandle WRONG_HANDLE = 1203981023;
}

class EventReceiver : public Message<MESSAGE_RDB>
{
public:
    unsigned int counter_;
    unsigned int counterA_;
    unsigned int counterB_;

    EventReceiver() : counter_(0), counterA_(0), counterB_(0) {}

    void handleEvent(const EventReceiver* event) {
        EXPECT_TRUE(event != 0);
        ++counter_;
        std::cout << "counter " << counter_ <<std::endl;
    }

    void handleEventA(const EventReceiver* event) {
        EXPECT_TRUE(event != 0);
        counter_++;
        counterA_++;
    }

    void handleEventB(const EventReceiver* event) {
        EXPECT_TRUE(event != 0);
        counter_++;
        counterB_++;
    }
};

class EventA : public EventReceiver
{
public:
    void handleEvent(const EventA* event) {
        EXPECT_TRUE(event != 0);
        ++counter_;
        std::cout << "counter " << counter_ <<std::endl;
    }
};

class EventB : public EventReceiver
{
public:
    void handleEvent(const EventB* event) {
        EXPECT_TRUE(event != 0);
        ++counter_;
        std::cout << "counter " << counter_ <<std::endl;
    }
};

TEST(SigSlot, SimpleEventTest) {

    EventReceiver receiver;
    MessageHandler messageHandle;
    Message<MESSAGE_RDB> message;

    messageHandle(&message); //no handlers, will not count

    messageHandle.setHandler<EventReceiver>(boost::bind(&EventReceiver::handleEvent, &receiver, _1));

    messageHandle.handleMessage(&message); //handler registered, counter incremented

    EXPECT_EQ(receiver.counter_, 1);
}

TEST(SigSlot, DeregisterTest) {

    EventReceiver receiver;
    MessageHandler messageHandle;
    Message<MESSAGE_RDB> message;

    messageHandle.handleMessage(&message); //no handlers, will not count

    messageHandle.setHandler<EventReceiver>(boost::bind(&EventReceiver::handleEvent, &receiver, _1));

    messageHandle.handleMessage(&message); // wrong handler registered, will not count

    EXPECT_EQ(receiver.counter_, 1);

    messageHandle.unsetHandler<EventReceiver>();

    messageHandle.handleMessage(&message); //handler registered, counter incremented

    EXPECT_EQ(receiver.counter_, 1);
}

TEST(Callback, WrongHandleTest)
{

    EventReceiver receiver;
    MessageCallback handler;
    std::vector<char> bufferData (100,0);

    handler.update(); //no handlers, will not count

    handler.registerEventFunc(&receiver, &EventReceiver::handleEvent, WRONG_HANDLE);

    handler.updateRDBdeque(bufferData, CAPTURE_ALL_HANDLE);

    handler.update(); //wrong handler, will not count

    handler.registerEventFunc(&receiver, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.updateRDBdeque(bufferData, CAPTURE_ALL_HANDLE);
    handler.update(); //handler registered, counter incremented

    EXPECT_EQ(receiver.counter_, 1);

    handler.deregisterEventFunc(&receiver, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.update(); //handler registered, counter incremented
    handler.updateRDBdeque(bufferData, CAPTURE_ALL_HANDLE);
    EXPECT_EQ(receiver.counter_, 1);
}

TEST(EventHandlerTest, InheritedEventTest) {

    EventReceiver receiver;
    MessageCallback handler;
    std::vector<char> bufferData (100,0);

    handler.registerEventFunc(&receiver, &EventReceiver::handleEventA, CAPTURE_ALL_HANDLE);
    handler.registerEventFunc(&receiver, &EventReceiver::handleEventB, CAPTURE_ALL_HANDLE);
    handler.updateRDBdeque(bufferData, CAPTURE_ALL_HANDLE);
    handler.update();

    EXPECT_EQ(receiver.counter_, 2);
    EXPECT_EQ(receiver.counterA_, 1);
    EXPECT_EQ(receiver.counterB_, 1);

    handler.registerEventFunc(&receiver, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);
    handler.updateRDBdeque(bufferData, CAPTURE_ALL_HANDLE);
    handler.update();

    EXPECT_EQ(receiver.counter_, 5);
    EXPECT_EQ(receiver.counterA_, 2);
    EXPECT_EQ(receiver.counterB_, 2);
}

TEST(EventHandlerTest, MulticastTest) {

    EventReceiver receiver0;
    EventReceiver receiver1;
    MessageCallback handler;
    std::vector<char> bufferData (100,0);


    handler.registerEventFunc(&receiver0, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);
    handler.registerEventFunc(&receiver1, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.updateRDBdeque(bufferData, CAPTURE_ALL_HANDLE);
    handler.update();

    EXPECT_EQ(receiver0.counter_, 1);
    EXPECT_EQ(receiver1.counter_, 1);
}

TEST(EventHandlerTest, TwoEvents)
{

    EventA receiver0;
    EventB receiver1;
    MessageCallback handler;
    std::vector<char> bufferData (100,0);


    handler.registerEventFunc(&receiver0, &EventA::handleEvent, CAPTURE_ALL_HANDLE);
    handler.registerEventFunc(&receiver1, &EventB::handleEvent, CAPTURE_ALL_HANDLE);

    handler.updateRDBdeque(bufferData, CAPTURE_ALL_HANDLE);
    handler.update();

    EXPECT_EQ(receiver0.counter_, 1);
    EXPECT_EQ(receiver1.counter_, 1);
}
