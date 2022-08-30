#include "VtdApi/Internal/VtdState.h"
#include <VtdCore/Logging/Log.h>

#include <sstream>

namespace VTD {
namespace Internal {

/**
 * Helper function returns true if the process is in the given RunStage, false if it is not. If the process is missing, the function will return the value of isOptional.
 */
bool checkState(const RunTable& runTable, const std::string& processName, RunStage::Enum runStage, bool isOptional)
{
    RunTable::const_iterator it = runTable.find(processName);
    if (it == runTable.end() || (*it).second == VTD::Internal::RunStage::UNDEFINED ) {
        return isOptional;
    }

    return runStage == (*it).second;
}

/**
 * Helper function returns true when all the started, processes are in their respective states. Optional processes must also be in their respective states, unless they are not started at all.
 */
bool checkProcessStates(const RunTable& runTable, RunStage::Enum taskControl, RunStage::Enum traffic, RunStage::Enum vig, RunStage::Enum moduleManager)
{
    return checkState(runTable, "TaskControl", taskControl, /*isOptional*/ false)
            && checkState(runTable, "Traffic", traffic, /*isOptional*/ false)
            && checkState(runTable, "ImageGenerator", vig, /*isOptional*/ true)
            && ( checkState(runTable, "ModuleManager", moduleManager, /*isOptional*/ true) || checkState(runTable, "MM_moduleMgr", moduleManager, /*isOptional*/ true) );
}

class State
{
public:
    virtual ~State() { }

    virtual OperationStage::Enum getOperationStage() const { return OperationStage::UNDEFINED; }

    // the following functions are called based on the event that could trigger a transition
    // the conditions for transition to another state is implemented in the concrete states.
    virtual void updateRunTable(VtdStateContext& context, const RunTable& runTable) { }
    virtual void updateSimState(VtdStateContext& context, const SimState::Enum& simState) { }
    virtual void updateInitDone(VtdStateContext& context) { }

protected:
    friend class VtdStateContext;

    void setState(VtdStateContext& context, const OperationStage::Enum& stage)
    {
        StatePool::iterator state = context.statePool_.find(stage);
        if (state != context.statePool_.end()) {
            VTD_DEBUG_LOG("Changing to " << OperationStage::toString(stage) << std::endl);
            context.setCurrentState(state->second);
        }
    }
};

class UndefinedState : public State
{
public:
    virtual OperationStage::Enum getOperationStage() const { return OperationStage::UNDEFINED; }

    virtual void updateRunTable(VtdStateContext& context, const RunTable& runTable)
    {
        bool isInReadyStage = checkProcessStates(runTable, /*TC*/ RunStage::IDLE, /*TF*/ RunStage::IDLE, /*IG*/ RunStage::RUN, /*MM*/ RunStage::RUN);
        if (isInReadyStage)
            State::setState(context, OperationStage::READY);

        bool isInRunState = checkProcessStates(runTable, /*TC*/ RunStage::RUN, /*TF*/ RunStage::RUN, /*IG*/ RunStage::RUN, /*MM*/ RunStage::RUN);
        if(isInRunState)
            State::setState(context, OperationStage::RUN);

        bool isInPauseState = checkProcessStates(runTable, /*TC*/ RunStage::PAUSE, /*TF*/ RunStage::PAUSE, /*IG*/ RunStage::RUN, /*MM*/ RunStage::RUN);
        if(isInPauseState)
            State::setState(context, OperationStage::PAUSE);
    }

    virtual void updateSimState(VtdStateContext& context, const SimState::Enum& simState)
    {
        switch (simState) {
        case SimState::READY:
            State::setState(context, OperationStage::READY);
            break;
        case SimState::POST_INIT:
            State::setState(context, OperationStage::INITDONE);
            break;
        case SimState::RUN:
            State::setState(context, OperationStage::RUN);
            break;
        case SimState::PAUSE:
            State::setState(context, OperationStage::PAUSE);
            break;
        default:
            /**/
            break;
        }
    }

    virtual void updateInitDone(VtdStateContext& context)
    {
        State::setState(context, OperationStage::INITDONE);
    }
};

class ConfigureState : public State
{
public:
    virtual OperationStage::Enum getOperationStage() const { return OperationStage::CONFIG; }

    virtual void updateRunTable(VtdStateContext& context, const RunTable& runTable)
    {
        bool isInReadyStage = checkProcessStates(runTable, /*TC*/ RunStage::IDLE, /*TF*/ RunStage::IDLE, /*IG*/ RunStage::RUN, /*MM*/ RunStage::RUN);

        if (isInReadyStage) {
            State::setState(context, OperationStage::READY);
        }
    }

    virtual void updateSimState(VtdStateContext& context, const SimState::Enum& simState)
    {
        switch (simState) {
        case SimState::READY:
            State::setState(context, OperationStage::READY);
            break;
        default:
            /**/
            break;
        }
    }
};

class ReadyState : public State
{
public:
    virtual OperationStage::Enum getOperationStage() const { return OperationStage::READY; }

    virtual void updateRunTable(VtdStateContext& /*context*/, const RunTable& /*runTable*/)  { }

    virtual void updateSimState(VtdStateContext& context, const SimState::Enum& simState)
    {
        switch (simState) {
        case SimState::POST_INIT:
            State::setState(context, OperationStage::INITDONE);
            break;
        default:
            /**/
            break;
        }
    }

    virtual void updateInitDone(VtdStateContext& context)
    {
        State::setState(context, OperationStage::INITDONE);
    }
};

class InitDoneState : public State
{
public:
    virtual OperationStage::Enum getOperationStage() const { return OperationStage::INITDONE; }

    virtual void updateRunTable(VtdStateContext& context, const RunTable& runTable)
    {
        //TODO: transition to configure

        //[GK] Ready stage is equal to init done stage in terms of run table, ignore it.

        bool isInRunState = checkProcessStates(runTable, /*TC*/ RunStage::RUN, /*TF*/ RunStage::RUN, /*IG*/ RunStage::RUN, /*MM*/ RunStage::RUN);

        if(isInRunState) {
            State::setState(context, OperationStage::RUN);
        }
    }

    virtual void updateSimState(VtdStateContext& context, const SimState::Enum& simState)
    {
        switch (simState) {
        case SimState::READY:
            State::setState(context, OperationStage::READY);
            break;
        case SimState::RUN:
            State::setState(context, OperationStage::RUN);
            break;
        default:
            /**/
            break;
        }
    }
};

class RunState : public State
{
public:
    virtual OperationStage::Enum getOperationStage() const { return OperationStage::RUN; }

    virtual void updateRunTable(VtdStateContext& context, const RunTable& runTable)
    {
        //TODO: transition to configure

        bool isInReadyStage = checkProcessStates(runTable, /*TC*/ RunStage::IDLE, /*TF*/ RunStage::IDLE, /*IG*/ RunStage::RUN, /*MM*/ RunStage::RUN);

        if(isInReadyStage) {
            State::setState(context, OperationStage::READY);
        }

        bool isInPauseState = checkProcessStates(runTable, /*TC*/ RunStage::PAUSE, /*TF*/ RunStage::PAUSE, /*IG*/ RunStage::RUN, /*MM*/ RunStage::RUN);

        if(isInPauseState) {
            State::setState(context, OperationStage::PAUSE);
        }
    }

    virtual void updateSimState(VtdStateContext& context, const SimState::Enum& simState)
    {
        switch (simState) {
        case SimState::READY:
            State::setState(context, OperationStage::READY);
            break;
        case SimState::PAUSE:
            State::setState(context, OperationStage::PAUSE);
            break;
        default:
            /**/
            break;
        }
    }
};

class PauseState : public State
{
public:
    virtual OperationStage::Enum getOperationStage() const { return OperationStage::PAUSE; }
    virtual void updateRunTable(VtdStateContext& context, const RunTable& runTable)
    {
        //TODO: transition to configure

        bool isInReadyStage = checkProcessStates(runTable, /*TC*/ RunStage::IDLE, /*TF*/ RunStage::IDLE, /*IG*/ RunStage::RUN, /*MM*/ RunStage::RUN);

        if(isInReadyStage) {
            State::setState(context, OperationStage::READY);
        }

        bool isInRunState = checkProcessStates(runTable, /*TC*/ RunStage::RUN, /*TF*/ RunStage::RUN, /*IG*/ RunStage::RUN, /*MM*/ RunStage::RUN);

        if(isInRunState) {
            State::setState(context, OperationStage::RUN);
        }
    }

    virtual void updateSimState(VtdStateContext& context, const SimState::Enum& simState)
    {
        switch (simState) {
        case SimState::READY:
            State::setState(context, OperationStage::READY);
            break;
        case SimState::RUN:
            State::setState(context, OperationStage::RUN);
            break;
        default:
            /**/
            break;
        }
    }
};

VtdStateContext::VtdStateContext()
    : currentState_(0)
    , configFlags_(0)
{
    statePool_[OperationStage::CONFIG] = new ConfigureState();
    statePool_[OperationStage::READY] = new ReadyState();
    statePool_[OperationStage::INITDONE] = new InitDoneState();
    statePool_[OperationStage::RUN] = new RunState();
    statePool_[OperationStage::PAUSE] = new PauseState();
    statePool_[OperationStage::UNDEFINED] = new UndefinedState();

    currentState_ = statePool_[OperationStage::UNDEFINED];
}

VtdStateContext::~VtdStateContext()
{
    currentState_ = 0;

    for(StatePool::iterator it = statePool_.begin(); it != statePool_.end(); ++it) {
        delete (*it).second;
    }
}
/**
 * Helper function to return the value of the first occurence of an
 * XML formatted attribute in the given string.
 * Fetches anything inbetween searchStr and '\"'.
 * SearchStr should be given in the format: "attribute=\""
 */
std::string fetchXmlAttribute(const std::string& searchStr, const std::string& scpTag)
{
    //<regex> is c++11 only. Then we could use: (?<=\attribute=\")[^\"]*
    size_t startPos = scpTag.find(searchStr);
    if (startPos != std::string::npos) {
        startPos += searchStr.length();
        size_t endPos = scpTag.find("\"", startPos);
        return scpTag.substr(startPos, endPos - startPos);
    }
    return "";
}

void VtdStateContext::reset()
{
    VTD_DEBUG_LOG(" enter")
    runTable_.clear();
    currentState_ = statePool_[OperationStage::CONFIG];
    configFlags_ = ConfigFlags::NO_FLAG;
}

void VtdStateContext::handleScpMessage(const ReceiveSCP* scpMessage)
{
    if (!scpMessage) {
        return;
    }

    const std::string& msgStr =scpMessage->getDataString();
    if (msgStr.empty()) {
        return;
    }

    // due to compiler optimizations in release builds the header has to be copied
    const SCP_MSG_HDR_t msgHdr = *(reinterpret_cast<const SCP_MSG_HDR_t*>(scpMessage->getHeaderData().data()));

    if (msgStr.find("TaskState") != std::string::npos)
    {
        //update runtable with proccess run stage
        std::istringstream msgStream(msgStr);
        std::string msgTag;
        bool hasUpdate = false;
#ifdef VTD_DEBUG
        bool hasChanged = false;
#endif
        while (getline(msgStream, msgTag, '>'))
        {
            std::string name = fetchXmlAttribute("name=\"", msgTag);
            std::string state = fetchXmlAttribute("state=\"", msgTag);
            if (!name.empty() && !state.empty())
            {
#ifdef VTD_DEBUG
                RunStage::Enum runStage = RunStage::fromString(state);
                hasChanged = hasChanged
                        || (runTable_.find(name) == runTable_.end())
                        || (runTable_[name] != runStage);
                runTable_[name] = RunStage::fromString(state);
#else
                runTable_[name] = RunStage::fromString(state);
#endif
                hasUpdate = true;
            }
        }

        if (hasUpdate && ((configFlags_ & ConfigFlags::TC_HAS_SIMSTATE) == 0))
        {
            // TC < 4.4.13
#ifdef VTD_DEBUG

            if(hasChanged) {
                VTD_DEBUG_LOG("RunTable Updated: "
                              << "TC: " << RunStage::toString(runTable_["TaskControl"])
                              << "; MM: " << RunStage::toString(runTable_["MM_moduleMgr"])
                              << "; IG: " << RunStage::toString(runTable_["ImageGenerator"])
                              << "; TF: " << RunStage::toString(runTable_["Traffic"]) );
            }
#endif

        }
    }
    else if ((strcmp(msgHdr.sender, "TaskControl") == 0) && (msgStr.find("SimState") != std::string::npos)) {
        //TC >= 4.4.13 only

        std::istringstream msgStream(msgStr);
        std::string msgTag;
        while (getline(msgStream, msgTag, '>'))
        {
            std::string source = fetchXmlAttribute("source=\"", msgTag);
            std::string state = fetchXmlAttribute("state=\"", msgTag);
            if (!state.empty() && source == "TaskControl")
            {
                VTD_DEBUG_LOG("SimState \"" << state << "\" received.");
                configFlags_ |= ConfigFlags::TC_HAS_SIMSTATE;
                currentState_->updateSimState(*this, SimState::fromString(state));
            }
        }
    }
    else if (((configFlags_ & ConfigFlags::TC_HAS_SIMSTATE) == 0) && (strcmp(msgHdr.sender, "TaskControl") == 0) && (msgStr.find("InitDone") != std::string::npos)) {
        // TC < 4.4.13
        std::istringstream msgStream(msgStr);
        std::string msgTag;
        while (getline(msgStream, msgTag, '>'))
        {
            std::string place = fetchXmlAttribute("place=\"", msgTag);
            if (msgTag.find("InitDone") != std::string::npos && place == "checkInitConfirmation")
            {
                VTD_DEBUG_LOG("InitDone received.");
                currentState_->updateInitDone(*this);
            }
        }
    }
}

void VtdStateContext::handleConnectionEvent(const ConnectionEvent* msg)
{
    //[GK] TODO
    if(!msg) {
        return;
    }

    switch(msg->getType()) {
    case ConnectionEvent::DISCONNECT:
        //force reset
        reset();
        break;

    default:
        /* do nothing */
        break;
    }
}

OperationStage::Enum VtdStateContext::getCurrentOperationStage() const
{
    return currentState_->getOperationStage();
}

RunStage::Enum VtdStateContext::getProcessRunStage(const std::string& processName) const
{
    RunTable::const_iterator it = runTable_.find(processName);
    if (it != runTable_.end()) {
        return (*it).second;
    }
    return RunStage::UNDEFINED;
}

} //namespace Internal
} //namespace VTD
