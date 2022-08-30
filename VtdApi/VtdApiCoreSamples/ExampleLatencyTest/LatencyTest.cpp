#include "LatencyTest.h"

#include <string>
#include <cstdio>
#include <cmath>

namespace
{
	// default player
	const unsigned int EGO_ID = 1u;
	// if message contains extended data structure

	const std::string DEFAULT_PLAYER_NAME = "Ego";

    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";
}

LatencyTest::LatencyTest()
    : ConnectionHandle_(0)
    , playerId_(EGO_ID)
    , mLastSimTime(0.0)
    , mStartTime(0.0)
    , mCurrentPitch(0.0)
    , mPrintMsg(0)
    , mOldPrintMsg(0)
{
    // initialize object state structure
    memset(&ownObjectState_, 0, sizeof(RDB_OBJECT_STATE_t));
}

bool LatencyTest::initVtdApi()
{
    mCsvFile.open("/tmp/TimeOutputSendObjectState.csv");
    if (!mCsvFile.is_open())
    {
        printf("ERROR: Could not open or create file /tmp/TimeOutputSendObjectState.csv\n");
        return false;
    }
    
    mCsvFile << "pitch (rad), time (ms)" << std::endl;
    
    
    // Handle for incoming data and outgoing data
    ConnectionHandle_ =  api_.connectRDB (DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::Protocols::RDB_TCP);

    // Register event if RDB has been connected
    if(ConnectionHandle_)
    {
        api_.registerEventFunc<LatencyTest, ReceiveRDB>(this, &LatencyTest::handleRdbMessage, ConnectionHandle_);
        return true;
    }
    else
    {
        printf("ERROR: Could not establish connection\n");
        return false;
    }
}

bool LatencyTest::isConnected()
{
    return api_.isConnected(ConnectionHandle_);
}

void LatencyTest::update()
{
    api_.update();
}

void LatencyTest::handleRdbMessage(const ReceiveRDB* msg)
{
    struct timeval tme;
    gettimeofday(&tme, 0);    
    
    if ( ( tme.tv_sec % 6 ) == 0 )
    {
        mCurrentPitch = 0.7f;
        mPrintMsg = 1;
    }
    else if ( ( tme.tv_sec % 6 ) == 3 )
    {
        mCurrentPitch = -0.7f;
        mPrintMsg = 2;
    } else {
        mPrintMsg = 0;
    }

    if ((mLastSimTime >= 0.0))
    {
        ownObjectState_.base.id = playerId_;
        ownObjectState_.base.category = RDB_OBJECT_CATEGORY_PLAYER;
        ownObjectState_.base.type = RDB_OBJECT_TYPE_PLAYER_CAR;
        strcpy(ownObjectState_.base.name, DEFAULT_PLAYER_NAME.c_str());

        ownObjectState_.base.geo.dimX = 4.60f;
        ownObjectState_.base.geo.dimY = 1.86f;
        ownObjectState_.base.geo.dimZ = 1.60f;
        
        ownObjectState_.base.geo.offX = 0.80f;
        ownObjectState_.base.geo.offY = 0.00f;
        ownObjectState_.base.geo.offZ = 0.30f;
        
        ownObjectState_.base.pos.x     = 1000.0;
        ownObjectState_.base.pos.y     = 1000.0;
        ownObjectState_.base.pos.z     = 0.0;
        ownObjectState_.base.pos.h     = 0.0f;
        ownObjectState_.base.pos.p     = mCurrentPitch;
        ownObjectState_.base.pos.r     = 0.0f;
        ownObjectState_.base.pos.flags = RDB_COORD_FLAG_POINT_VALID | RDB_COORD_FLAG_ANGLES_VALID;
        
        ownObjectState_.ext.speed.x     = 0.0;
        ownObjectState_.ext.speed.y     = 0.0;
        ownObjectState_.ext.speed.z     = 0.0;
        ownObjectState_.ext.speed.h     = 0.0f;
        ownObjectState_.ext.speed.p     = 0.0f;
        ownObjectState_.ext.speed.r     = 0.0f;
        ownObjectState_.ext.speed.flags = 0;
        
        ownObjectState_.ext.accel.x     = 0.0;
        ownObjectState_.ext.accel.y     = 0.0;
        ownObjectState_.ext.accel.z     = 0.0;
        ownObjectState_.ext.accel.flags = 0;

        // ok, I have a new object state, so let's send the data
        sendOwnObjectState(msg->getData());
        
        if ( mPrintMsg && ( mPrintMsg != mOldPrintMsg ) )
        {
            mStartTime = boost::numeric_cast<double>( tme.tv_sec ) + 1.0e-6 * boost::numeric_cast<double>( tme.tv_usec );
            fprintf(stderr, "LatencyTest: pitch, timestamp = %.3f, %.3lf\n", ownObjectState_.base.pos.p, fmod( 1000.0 * mStartTime, 100000.0 ));
            
            mCsvFile << ownObjectState_.base.pos.p << ", " << std::fmod( 1000.0 * mStartTime, 100000.0 ) << std::endl;
            mCsvFile.flush();
        }
        mOldPrintMsg = mPrintMsg;
    }

    // remember last simulation time
    mLastSimTime = msg->getData().hdr.simTime;
}

void LatencyTest::sendOwnObjectState(const RDB_MSG_t& RDBMessage)
{
    Framework::RDBHandler myHandler;

    // start a new message
    myHandler.initMsg();

    // begin with an SOF identifier
    myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_START_OF_FRAME);

    // add extended package for the object state
    RDB_OBJECT_STATE_t*objState = reinterpret_cast<RDB_OBJECT_STATE_t*>(myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_OBJECT_STATE, 1, true));

    if (!objState)
    {
        fprintf(stderr, "sendOwnObjectState: could not create object state\n");
        return;
    }

    // copy contents of internally held object state to output structure
    memcpy(objState, &ownObjectState_, sizeof(RDB_OBJECT_STATE_t));

    // terminate with an EOF identifier
    myHandler.addPackage(RDBMessage.hdr.simTime, RDBMessage.hdr.frameNo, RDB_PKG_ID_END_OF_FRAME);

    api_.sendRdbMessage(ConnectionHandle_, *myHandler.getMsg());
}


