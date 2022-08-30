#ifndef VTDAPI_ASYNCEVENTHANDLER_H
#define VTDAPI_ASYNCEVENTHANDLER_H

#include <map>
#include <deque>
#include <vector>

#include <VtdToolkit/scpIcd.h>
#include <VtdThreads/CriticalSection.h>

#include <VtdCore/EventHandler.h>


namespace VTD {
namespace Internal {
/**
 * @brief The AsyncEventHandler queues events which are fired with the next call to update in a threadsafe manner.
 *
 * Ownership of the events is passed to the AsyncEventHandler instance, which calls delete on any queued event pointers
 * once they are handled. By extension this means that Events must be allocated on heap and any receivers must make copies of the
 * events if they wish to retain them after returning from the event handler function.
 */
class AsyncEventHandler : public EventHandler {
public:
    AsyncEventHandler();
    virtual ~AsyncEventHandler();

    /**
     * Call to fire events and clear the current Event queue.
     */
    void update();

    /**
     * Queue an Event.
     * Ownership is passed to the AsyncEventHandler, referenced Event must be allocated on heap.
     * @param event a valid pointer to an event instance.
     */
    void queueEvent(Event* event);

private:
    typedef std::deque<Event*> EventQueue;
    EventQueue eventQueue0_;
    EventQueue eventQueue1_;

    CriticalSection cs_;
    EventQueue* writeQueue_;
};

} //namespace Internal
} //namespace VTD

#endif //VTDAPI_ASYNCEVENTHANDLER_H
