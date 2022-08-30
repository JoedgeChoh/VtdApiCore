#include <gtest/gtest.h>
#include <VtdCore/EventHandler.h>

#include <iostream>

const std::string DEFAULT_HOST = "127.0.0.1";

using namespace VTD;

namespace
{
    static const int CAPTURE_ALL_HANDLE = -666;
    static const int WRONG_HANDLE = 1203981023;
}

class EventA : public Event {
    //
};

class EventB : public Event {
    //
};

class EventReceiver {
public:
    unsigned int counter_ ;
    unsigned int counterA_;
    unsigned int counterB_;

    EventReceiver() : counter_ (0), counterA_(0), counterB_(0) {}
    void handleEvent(const Event* event) {
        EXPECT_TRUE(event != 0);
        counter_++;
    }

    void handleEventA(const EventA* event) {
        EXPECT_TRUE(event != 0);
        counter_++;
        counterA_++;
    }

    void handleEventB(const EventB* event) {
        EXPECT_TRUE(event != 0);
        counter_++;
        counterB_++;
    }
};

class TypeInfoFriend : public std::type_info{
public:
    TypeInfoFriend(const char* name):std::type_info(name){}
    // Access to protected constructor
    friend type_info type_info(const char*);
};

TEST(TypeInfoTest, UnmergedTypeInfoTest) {

    // Create same type, with different addresses
    const std::string typeAString = "foo";
    const std::string typeBString = "foo";
    ASSERT_NE(typeAString.c_str(), typeBString.c_str());

    // Create std::type_info class with non identical string addresses
    const TypeInfoFriend typeAFriend(typeAString.c_str());
    const TypeInfoFriend typeBFriend(typeBString.c_str());

    // Create TypeInfo who use the non merged strings
    const TypeInfo typeA(typeAFriend);
    const TypeInfo typeB(typeBFriend);

    // Test should succede even if type_info is not merged
    EXPECT_FALSE(typeA < typeB);
    EXPECT_FALSE(typeB < typeA);
}


TEST(EventHandlerTest, SimpleEventTest) {

    EventReceiver receiver;
    EventHandler handler;
    Event event;

    handler.handleEvent(&event); //no handlers, will not count

    handler.registerEventFunc(&receiver, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.handleEvent(&event); //handler registered, counter incremented

    EXPECT_EQ(receiver.counter_, 1);
}

TEST(EventHandlerTest, DeregisterTest) {

    EventReceiver receiver;
    EventHandler handler;
    Event event;

    handler.handleEvent(&event); //no handlers, will not count

    handler.registerEventFunc(&receiver, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.handleEvent(&event); // wrong handler registered, will not count

    EXPECT_EQ(receiver.counter_, 1);

    handler.deregisterEventFunc(&receiver, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.handleEvent(&event); //handler registered, counter incremented

    EXPECT_EQ(receiver.counter_, 1);
}

TEST(EventHandlerTest, WrongHandleTest) {

    EventReceiver receiver;
    EventHandler handler;
    Event event;

    handler.handleEvent(&event); //no handlers, will not count

    handler.registerEventFunc(&receiver, &EventReceiver::handleEvent, WRONG_HANDLE);

    handler.handleEvent(&event); //wrong handler, will not count

    handler.registerEventFunc(&receiver, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.handleEvent(&event); //handler registered, counter incremented

    EXPECT_EQ(receiver.counter_, 1);

    handler.deregisterEventFunc(&receiver, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.handleEvent(&event); //handler registered, counter incremented

    EXPECT_EQ(receiver.counter_, 1);
}

TEST(EventHandlerTest, InheritedEventTest) {

    EventReceiver receiver;
    EventHandler handler;
    Event event;
    EventA eventA;
    EventB eventB;

    handler.registerEventFunc(&receiver, &EventReceiver::handleEventA, CAPTURE_ALL_HANDLE);
    handler.registerEventFunc(&receiver, &EventReceiver::handleEventB, CAPTURE_ALL_HANDLE);

    handler.handleEvent(&event); //no handler registered, will not increment
    handler.handleEvent(&eventA); //increment counter and counterA
    handler.handleEvent(&eventB); //increment counter and counterB

    EXPECT_EQ(receiver.counter_, 2);
    EXPECT_EQ(receiver.counterA_, 1);
    EXPECT_EQ(receiver.counterB_, 1);

    handler.registerEventFunc(&receiver, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.handleEvent(&event); //increment counter only
    handler.handleEvent(&eventA); //increment counter and counterA

    EXPECT_EQ(receiver.counter_, 4);
    EXPECT_EQ(receiver.counterA_, 2);
    EXPECT_EQ(receiver.counterB_, 1);
}

TEST(EventHandlerTest, MulticastTest) {

    EventReceiver receiver0;
    EventReceiver receiver1;
    EventHandler handler;
    Event event;

    handler.registerEventFunc(&receiver0, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);
    handler.registerEventFunc(&receiver1, &EventReceiver::handleEvent, CAPTURE_ALL_HANDLE);

    handler.handleEvent(&event);

    EXPECT_EQ(receiver0.counter_, 1);
    EXPECT_EQ(receiver1.counter_, 1);
}
