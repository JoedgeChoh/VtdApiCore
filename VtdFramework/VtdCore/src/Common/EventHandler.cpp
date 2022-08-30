#include "VtdCore/EventHandler.h"


namespace
{
    static const int CAPTURE_ALL_HANDLE = -666;
    static const std::string CAPTURE_ALL_HANDLE_STR = "-666";
}

namespace VTD {

std::string EventHandler::connectionHandleToString(ConnectionHandle value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

EventHandler::~EventHandler()
{
    for(HandlerFunctions::iterator listIt = handlers_.begin(); listIt != handlers_.end(); ++listIt) {
        HandlerFunctionList& handlerList = listIt->second;
        for(HandlerFunctionList::iterator it = handlerList.begin(); it != handlerList.end(); ++it ) {
            delete it->second;
        }
    }
}

void EventHandler::handleEvent(const Event* event)
{
    if(!event) return;

    HandlerFunctions::iterator listIt = handlers_.find(TypeInfo(typeid(*event)));
    if(listIt != handlers_.end()) {
        HandlerFunctionList& handlerList = listIt->second;
        for(HandlerFunctionList::iterator it = handlerList.begin(); it != handlerList.end(); ++it )
        {
            if (it->first.compare(event->partner) == 0 || it->first.compare(CAPTURE_ALL_HANDLE_STR) == 0)
            {
                it->second->exec(event);
            }
        }
    }
}


} //namespace VTD
