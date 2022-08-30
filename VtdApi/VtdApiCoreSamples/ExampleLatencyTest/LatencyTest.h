#ifndef EXAMPLE_VEH_DYN_INTEQ_H
#define EXAMPLE_VEH_DYN_INTEQ_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>

#include <fstream>

/**
 * Class Communication Sample is an example how to use Vtd Api to control vihecle
 */

using namespace VTD;

class LatencyTest {
public:
    /**
     * constructor
     */
    LatencyTest(void);

    /**
     * @brief handleRdbMessage - receive RDB
     * @param msg - RDB message
     */
    void handleRdbMessage(const ReceiveRDB* msg);

    /**
     * @brief processObjectState
     * @param RDBMessage
     */
    void sendObjectStateUpdate(const RDB_MSG_t& RDBMessage);

    /**
     * @brief sendOwnObjectState -
     * @param RDBMessage - RDB message
     */
    void sendOwnObjectState(const RDB_MSG_t& RDBMessage);

    /**
     * @brief initVtdApi - initalaze VtdApi
     * @return true if API is initalized
     */
    bool initVtdApi(void);

    /**
     * @brief isConnected - return connection state
     * @return true if connected
     */
    bool isConnected(void);

    /**
     * @brief update - update routine
     */
    void update(void);

private:
    //VTD api
    VtdApi api_;
    //ConnectionHandle_ handles for incoming and outgoing RDB connections
    ConnectionHandle ConnectionHandle_;
    // Default player Ego Id
    unsigned int playerId_;

    RDB_OBJECT_STATE_t ownObjectState_;
    
    std::ofstream mCsvFile;    
    double mLastSimTime;
    double mStartTime;
    float mCurrentPitch;
    int    mPrintMsg;
    int    mOldPrintMsg;    
};
#endif //  EXAMPLE_VEH_DYN_INTEQ_H
