#ifndef _MESSAGE_CALL_BACK_H
#define _MESSAGE_CALL_BACK_H

#include <vector>
#include <iostream>
#include <map>
#include <deque>

#include <boost/function.hpp>
#include <boost/thread.hpp>

#include "message.h"

namespace VTD
{
/**
 * @brief The MessageCallback class handel callback event function
 */
class MessageCallback
{
public:
    /**
     * @brief MessageCallback constructor
     */
    MessageCallback ();

    /**
     * @brief ~MessageCallback destructor
     */
    virtual ~MessageCallback ();
    // callback functions
    typedef boost::function<void(const ReceiveSCP*)> FuncSCP;
    typedef boost::function<void(const ConnectionEvent*)> ConnEven;
    typedef boost::function<void(const ReceiveRDB*, const ConnectionHandle&)> FuncRDB;

    /**
     * @brief registerEventFunc register event callback
     * @templ Receiver - class which should receive event
     * @templ Event - type of event for example ReceiveScp or ReceiveRdb
     * @param ReceiverT* - pointer to class which holds member function
     * @param ReceiverT::*memberFunc - member function which will receive event
     * @param handle communication handle
     */
    template <class ReceiverT, class EventT>
    void registerEventFunc(ReceiverT*, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& handle);

    /**
     * @brief deregisterEventFunc register event callback
     * @templ Receiver - class which should receive event
     * @templ Event - type of event for example ReceiveScp or ReceiveRdb
     * @param ReceiverT* - pointer to class which holds member function
     * @param ReceiverT::*memberFunc - member function which will receive event
     * @param handle communication handle
     */
    template <class ReceiverT, class EventT>
    void deregisterEventFunc(ReceiverT*, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& handle);

    /**
     * @brief update call all callback
     */
    void update();

    /**
     * @brief updateRDBdeque update rdb data
     * @param bufferRDBData vector conatning rdb data
     * @param handle communication handle
     */
    void updateRDBdeque(const std::vector<char>& bufferRDBData, const ConnectionHandle& handle);

    /**
     * @brief updateSCPdeque update scp data
     * @param bufferSCPData buffer contaning scp data
     * @param bufferSCPHdr  buffer conatning scp header
     * @param handle communication handle
     */
    void updateSCPdeque(const std::vector<char>& bufferSCPData, const boost::array<char, SCP_HEADER_SIZE>& bufferSCPHdr, const ConnectionHandle& handle);

    /**
     * @brief activate or deactivate the direct mode (aka bufferless)
     *
     * If off (default) all received messages will be stored in a buffer (deque) and only delivered on a call of update().
     * If activated the received messages will be directly passed-through the callback in thread-context of handles.
     */
    void setDirectMode(bool active = true) { directModeActive_ = active; }

public:
    // callback scp functions
    std::vector<MessageHandler> callbackScp_;
    // one com handler can have more callbacks so we have to use multi map
    std::multimap<ConnectionHandle, MessageHandler> handleRDBMessages_;
    // connection event
    ConnEven connEvent_;
protected:
    bool directModeActive_;
    // deques with scp and rdb data
    RDBdeque rdbDeque_;
    SCPdeque scpDeque_;
    // mutexes
    boost::mutex mutex1_, mutex2_;

private:
    // call callback and deliver data to outside
    void updateSCP();
    void updateRDB();
};

template <class ReceiverT, class EventT>
void MessageCallback::registerEventFunc(ReceiverT* receiver, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& connectionHandle)
{
    MessageHandler messageHandle;

    if (EventT::MsgId == MESSAGE_RDB)
    {
        messageHandle.setHandler<EventT>(boost::bind(memberFunc, receiver, boost::placeholders::_1));
        handleRDBMessages_.insert(std::make_pair(connectionHandle, messageHandle));
    }

    if (EventT::MsgId == MESSAGE_SCP)
    {
        messageHandle.setHandler<EventT>(boost::bind(memberFunc, receiver, boost::placeholders::_1));
        callbackScp_.push_back(messageHandle);
    }

    if (EventT::MsgId == MESSAGE_CONNECTION_EVENT)
    {
        messageHandle.setHandler<EventT>(boost::bind(memberFunc, receiver, boost::placeholders::_1));
        connEvent_ = messageHandle;
    }
}

template <class ReceiverT, class EventT>
void MessageCallback::deregisterEventFunc(ReceiverT* receiver, void (ReceiverT::*memberFunc)(const EventT*), const ConnectionHandle& handle)
{
    if (!receiver || !memberFunc) return;

    if (EventT::MsgId == MESSAGE_RDB)
        handleRDBMessages_.find(handle)->second.unsetHandler<EventT>();

     if (EventT::MsgId == MESSAGE_SCP)
         callbackScp_.back().unsetHandler<EventT>();
}

}

#endif // _MESSAGE_CALL_BACK
