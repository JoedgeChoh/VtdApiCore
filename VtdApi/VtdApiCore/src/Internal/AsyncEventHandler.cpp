#include "VtdApi/Internal/AsyncEventHandler.h"

namespace VTD {
namespace Internal {
#ifndef VTD_API_BOOST
AsyncEventHandler::AsyncEventHandler() :
    writeQueue_(&eventQueue0_)
{ /**/ }

AsyncEventHandler::~AsyncEventHandler()
{
    //fire and delete all remaining Events.
    ScopedLock<CriticalSection> lock(cs_);

    EventQueue& readQueue = eventQueue0_;
    while(!readQueue.empty()) {
        Event* event = readQueue.front();
        handleEvent(event);
        delete event;
        readQueue.pop_front();
    }

    readQueue = eventQueue1_;
    while(!readQueue.empty()) {
        Event* event = readQueue.front();
        handleEvent(event);
        delete event;
        readQueue.pop_front();
    }
}

void AsyncEventHandler::update()
{
    EventQueue* readQueue = writeQueue_;
    {
        ScopedLock<CriticalSection> lock(cs_);
        writeQueue_ = ((writeQueue_ == &eventQueue0_) ? &eventQueue1_ : &eventQueue0_);
    }

    while(!readQueue->empty()) {
        Event* event = readQueue->front();
        handleEvent(event);
        delete event;
        readQueue->pop_front();
    }
}

void AsyncEventHandler::queueEvent(Event *event)
{
    ScopedLock<CriticalSection> lock(cs_);
    assert(writeQueue_ != 0);
    writeQueue_->push_back(event);
}
#endif
} //namespace Internal
} //namespace VTD
