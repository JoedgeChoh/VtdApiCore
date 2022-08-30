#ifndef VTDAPI_VTDSTATE_H
#define VTDAPI_VTDSTATE_H

#include <string>
#include <map>

#include <VtdCore/Logging/Log.h>
#include <VtdCore/BasicTypes.h>
#include "VtdApi/IVtdApi.h"

namespace VTD {

class VtdApi;

namespace Internal {

#define ENUM_STR_CASE(enumLabel) case enumLabel: return #enumLabel
#define ENUM_STR_DEFAULTCASE(enumLabel) case enumLabel: default: return #enumLabel
#define STR_EQ_ENUM_IF(value, enumLabel) if (value.compare(#enumLabel)) { return enumLabel; }

/**
 * TaskControl sim states, see SCP Documentation.
 */
struct SimState {
    enum Enum {
        UNDEFINED = 0,
        INIT,
        RUN,
        PAUSE,
        EXIT,
        READY,
        POST_INIT,
        WAIT_FOR_INIT_CONFIRM
    };

    static std::string toString(Enum stage)
    {
        switch (stage) {
            ENUM_STR_CASE(INIT);
            ENUM_STR_CASE(RUN);
            ENUM_STR_CASE(PAUSE);
            ENUM_STR_CASE(EXIT);
            ENUM_STR_CASE(READY);
            case POST_INIT: return "POST-INIT";
            ENUM_STR_CASE(WAIT_FOR_INIT_CONFIRM);
            ENUM_STR_DEFAULTCASE(UNDEFINED);
        }
    }

    static Enum fromString(const std::string& stageStr)
    {
        if (stageStr.compare("INIT") == 0) {
            return INIT;
        }
        else if (stageStr.compare("RUN") == 0) {
            return RUN;
        }
        else if (stageStr.compare("PAUSE") == 0) {
            return PAUSE;
        }
        else if (stageStr.compare("EXIT") == 0) {
            return EXIT;
        }
        else if (stageStr.compare("READY") == 0) {
            return READY;
        }
        else if (stageStr.compare("POST-INIT") == 0) {
            return POST_INIT;
        }
        else if (stageStr.compare("WAIT_FOR_INIT_CONFIRM") == 0) {
            return WAIT_FOR_INIT_CONFIRM;
        }

        return UNDEFINED;
    }
};

/**
 * Process RunStage, used internally for process running stages
 */
struct RunStage {
    enum Enum
    {
        UNDEFINED = 0,
        NONE,
        FAIL,
        IDLE,
        RUN,
        PAUSE
    };

    static std::string toString(Enum stage)
    {
        switch (stage) {
        case FAIL:
            return "fail";
        case IDLE:
            return "idle";
        case RUN:
            return "run";
        case PAUSE:
            return "pause";
        case UNDEFINED:
            return "undefined";
        case NONE:
        default:
            return "none";
        }
    }

    static Enum fromString(const std::string& stageStr)
    {
        if (stageStr.compare("none") == 0) {
            return NONE;
        }
        else if (stageStr.compare("fail") == 0) {
            return FAIL;
        }
        else if (stageStr.compare("idle") == 0) {
            return IDLE;
        }
        else if (stageStr.compare("run") == 0) {
            return RUN;
        }
        else if (stageStr.compare("pause") == 0) {
            return PAUSE;
        }

        return UNDEFINED;
    }
};

class State;
typedef std::pair<std::string, RunStage::Enum> RunTablePair;
typedef std::map<RunTablePair::first_type, RunTablePair::second_type> RunTable;
typedef std::map<OperationStage::Enum, State*> StatePool;


/**
 * The VtdStateContext class keeps track of process run states as well as the (VTD wide) operation stage based
 * on inputs from SCP.
 */
class VtdStateContext
{
public:
    VtdStateContext();

    ~VtdStateContext();


private:
    friend class VTD::VtdApi;
    friend class State;

    State* currentState_;

    UInt configFlags_;
    RunTable runTable_;
    StatePool statePool_;

    struct ConfigFlags {
        enum Enum {
            NO_FLAG = 0,
            TC_HAS_SIMSTATE = 1 ///< TC >= 4.4.13 offers <SimState> messages
        };
    };
    void setCurrentState(State* state) { currentState_ = state; }

    OperationStage::Enum getCurrentOperationStage() const;
    RunStage::Enum getProcessRunStage(const std::string& processName) const;
    void reset();

    /**
     * @brief handleScpMessage - handle scp messages
     * @param scpMessage - SCP message event
     */
    void handleScpMessage(const ReceiveSCP* scpMessage);

    void handleConnectionEvent(const ConnectionEvent* msg);

};

} //namespace Internal
} //namespace VTD

#endif //VTDAPI_VTDSTATE_H
