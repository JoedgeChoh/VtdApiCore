#ifndef VTDAPI_EVENTHANDLER_H
#define VTDAPI_EVENTHANDLER_H

#include <map>
#include <vector>
#include <typeinfo>
#if __cplusplus >= 201103L || _MSVC_LANG >= 201103L
#include <typeindex>
#endif
#include <sstream>

namespace VTD {

/**
 * @brief The Event base class
 */
class Event {
public:
    virtual ~Event() { /**/ }
public:
    std::string partner;
};

/**
 * @brief The Event Callback base class.
 * TODO: Currently not supported.
 */
template <class EventT> class EventCallbackBase {
public:
    virtual ~EventCallbackBase() { /**/ }

    virtual void operator()(const EventT*) = 0;
};

#if (__cplusplus >= 201103L && __linux__) || (_MSVC_LANG >= 201103L && _WIN32)
using TypeInfo = std::type_index;
#else
/**
 * Wrapper around std::type_info to allow comparison and assignment.
 */
class TypeInfo : public std::type_info
{
public:
    TypeInfo(const TypeInfo& other) : std::type_info(other.__name) { /**/ }

    TypeInfo(const std::type_info& other) : std::type_info(other.name()) { /**/ }

    bool operator<(const TypeInfo& b) const { return before(b); }
};
#endif

namespace Internal {
    /**
     * Used internally.
     */
    class HandlerFunctionBase
    {
    public:
        virtual ~HandlerFunctionBase() { /**/ }
        void exec(const Event* event) { call(event); }

    private:
        virtual void call(const Event*) = 0;
    };

    /**
     * Used internally.
     */
    template <class ReceiverT, class EventT>
    class MemberFunctionHandler : public HandlerFunctionBase
    {
    public:
        typedef void (ReceiverT::*MemberFunc)(const EventT*);

        MemberFunctionHandler(ReceiverT* instance, MemberFunc memberFunc);

        virtual void call(const Event* event);

        const ReceiverT* getInstance() const { return instance_; }
        MemberFunc getFunction() const { return function_; }

    private:
        ReceiverT* instance_;
        MemberFunc function_;
    };

    template <class ReceiverT, class EventT>
    MemberFunctionHandler<ReceiverT, EventT>::MemberFunctionHandler(ReceiverT* instance, MemberFunctionHandler::MemberFunc memberFunc)
        : instance_(instance)
        , function_(memberFunc)
    {
#ifdef DEBUG
    assert(instance_);
    assert(function_);
#endif
    }

    template <class ReceiverT, class EventT>
    void MemberFunctionHandler<ReceiverT, EventT>::call(const Event* event)
    {
#ifdef DEBUG
        assert(event);
#endif
        (instance_->*function_)(static_cast<const EventT*>(event));
    }
} //namespace Internal

/**
 * @brief The EventHandler class
 * Allows registration of member functions to types deriving from VTD::Event.
 * Events will be immediately dispatched to all functions registered to the respective type.
 */
class EventHandler
{
public:
    typedef int ConnectionHandle;

    virtual ~EventHandler();

    void handleEvent(const Event*);

    template <class ReceiverT, class EventT>
    void registerEventFunc(ReceiverT*, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& handle);

    template <class ReceiverT, class EventT>
    void deregisterEventFunc(ReceiverT*, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& handle);

private:
    std::string connectionHandleToString(ConnectionHandle value);

    typedef std::pair<std::string, Internal::HandlerFunctionBase*> HandlerFunctionEntry;
    typedef std::vector<HandlerFunctionEntry> HandlerFunctionList;
    typedef std::map<TypeInfo, HandlerFunctionList > HandlerFunctions;
    //boost_
    HandlerFunctions handlers_;
};

template <class ReceiverT, class EventT>
void EventHandler::registerEventFunc(ReceiverT* receiver, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& handle)
{
    if (!receiver || !memberFunc) return;

    std::string handleStr = connectionHandleToString(handle);
    HandlerFunctionList& list = handlers_[TypeInfo(typeid(EventT))];
    list.push_back(HandlerFunctionEntry(handleStr, new Internal::MemberFunctionHandler<ReceiverT, EventT>(receiver, memberFunc)));
}

template <class ReceiverT, class EventT>
void EventHandler::deregisterEventFunc(ReceiverT* receiver, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& handle)
{
    if (!receiver || !memberFunc) return;

    HandlerFunctionList& handlers = handlers_[TypeInfo(typeid(EventT))];
    HandlerFunctionList::iterator it = handlers.begin();
    for (; it != handlers.end(); ++it)
    {
        Internal::MemberFunctionHandler<ReceiverT, EventT>* handler = dynamic_cast< Internal::MemberFunctionHandler<ReceiverT, EventT>*>((*it).second);
        const std::string& connectionHandle = (*it).first;
        if (handler && (handler->getInstance() == receiver)
                && (handler->getFunction() == memberFunc)
                && (connectionHandle.compare(connectionHandleToString(handle)) == 0))
        {
            break;
        }
    }

    if (it != handlers.end()) {
        delete it->second;
        handlers.erase(it);
    }
}

} //namespace VTD

#endif //VTDAPI_EVENTHANDLER_H
