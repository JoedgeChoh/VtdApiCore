#include "ExampleWriteHDF5.h"

#include <string>
#include <cmath>
#include <cstdio>

using namespace VTD;

namespace
{
    // default host local ip where VTD is running
    const std::string DEFAULT_HOST = "127.0.0.1";
    int MAX_TIME_OUT = 120;
} // namespace

ExampleWriteHDF5::ExampleWriteHDF5()
    : RDBConnectionHandle_(0)
    , SCPConnectionHandle_(0)
    , hasNewFrameBeenReceived(true)  
    , is_fileopen(false)
    , receivedStop_(false)
    , receivedStart_(false)
    , simulationtime(0)
    , simulationframe(0)

{
}
ExampleWriteHDF5::~ExampleWriteHDF5()
{
    closeVtdApi();
}

bool ExampleWriteHDF5::initVtdApiRDB()
{
    // Handle for incoming data and outgoing data
    timer_.start();
    while (RDBConnectionHandle_ == 0 && timer_.elapsedSeconds() < MAX_TIME_OUT)
    {
    RDBConnectionHandle_ = api_.connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP);
    sleep(2);
    }
    timer_.stop();

    // Register event if RDB has been connected
    if (RDBConnectionHandle_)
    {
        api_.registerEventFunc<ExampleWriteHDF5, ReceiveRDB>(this, &ExampleWriteHDF5::handleRdbMessage, RDBConnectionHandle_);
        api_.update();
        return true;
    }
    else
    {
        printf("ERROR: Could not establish connection\n");
        return false;
    }
}

bool ExampleWriteHDF5::initVtdApiSCP()
{
    // Handle for incoming data and outgoing data
    timer_.start();
    while (SCPConnectionHandle_ == 0 && timer_.elapsedSeconds() < MAX_TIME_OUT)
    {
    SCPConnectionHandle_ = api_.connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    sleep(2);
    }
    timer_.stop();

    // Register event if RDB has been connected
    if (SCPConnectionHandle_)
    {
        api_.registerEventFunc<ExampleWriteHDF5, ReceiveSCP>(this, &ExampleWriteHDF5::handleMessageSCP, SCPConnectionHandle_);
        api_.update();
        return true;
    }
    else
    {
        printf("ERROR: Could not establish connection\n");
        return false;
    }
}

bool ExampleWriteHDF5::closeVtdApi()
{
    bool retVal = true;

    if (api_.isConnected(RDBConnectionHandle_))
    {
        api_.deregisterEventFunc<ExampleWriteHDF5, ReceiveRDB>(this, &ExampleWriteHDF5::handleRdbMessage, RDBConnectionHandle_);
        api_.disconnectRDB(RDBConnectionHandle_);
        RDBConnectionHandle_ = 0;
        printf("\n RDB disconnected\n");
    }
    else
    {
        printf("ERROR: Not connected anyway\n");

        retVal = false;
    }

    if (api_.isConnected(SCPConnectionHandle_))
    {
        api_.deregisterEventFunc<ExampleWriteHDF5, ReceiveSCP>(this, &ExampleWriteHDF5::handleMessageSCP, SCPConnectionHandle_);
        api_.disconnectSCP(SCPConnectionHandle_);
        SCPConnectionHandle_= 0;
        printf("SCP disconnected\n");
    }
    else
    {
            printf("ERROR: Not connected anyway\n");

        retVal = false;
    }

    return retVal;
}

void ExampleWriteHDF5::handleRdbMessage(const ReceiveRDB* msg)
{
    parttowrite(msg->getData());
}



bool ExampleWriteHDF5::openfile(std::string file)
{

    if (VTD::Internal::FileSystemIO::checkIfFileExists(file + ".h5"))
        VTD::Internal::FileSystemIO::removeFile(file + ".h5");

#ifdef HDF_ENABLED
    writeHdf5Data_.openHdf5File(file);
#endif

    VTD::Internal::FileSystemIO::setPermissions(file + ".h5", boost::filesystem::all_all, true);
    is_fileopen = true;
    return true;
}


void ExampleWriteHDF5::closeFile ()
{
#ifdef HDF_ENABLED
    writeHdf5Data_.closeHdf5AllFolders();
    writeHdf5Data_.closeHdf5File();
#endif
    is_fileopen = false;
    simulationtime = 0.0;
    simulationframe = 0;
    hasNewFrameBeenReceived = true;
}

void ExampleWriteHDF5::handleMessageSCP(const ReceiveSCP* msg)
{
    if (!msg)
        return;

    std::string messageStr = msg->getDataString();
    if ((messageStr.find("SimCtr") != std::string::npos) && (messageStr.find("Stop") != std::string::npos)) //<SimCtrl><Stop/></SimCtrl>
    {
        printf("Message found: <SimCtrl><Stop/></SimCtrl>\n");
        receivedStop_ = true;
    }

    if ((messageStr.find("SimCtr") != std::string::npos) && (messageStr.find("Start") != std::string::npos)) //<SimCtrl><Start/></SimCtrl>
    {
        printf("Message found: <SimCtrl><Start/></SimCtrl>\n");
        receivedStart_= true;
    }

}

void ExampleWriteHDF5::parttowrite(const RDB_MSG_t& RDBMessage)
{
    if (!is_fileopen)
        return;

        #ifdef HDF_ENABLED
        writeHdf5Data_.writeRdbMessage(RDBMessage);
        #endif

       simulationtime = RDBMessage.hdr.simTime;
       simulationframe = RDBMessage.hdr.frameNo;

    if (RDBMessage.entryHdr.pkgId == RDB_PKG_ID_END_OF_FRAME)
    {
        hasNewFrameBeenReceived = true;
        std::cout << "GOT FRAME:" << simulationframe << std::endl;
    }
}


void ExampleWriteHDF5::updateapi()
{
    api_.update();
}


bool ExampleWriteHDF5::sendSCPCommand(COMMAND command)
{

// function to send SCP Commands START, INIT and STOP
    bool isCommandSucSend = false;
    switch (command)
    {
    case STOP:
    {
        api_.stopSimulation(/*isBlocking*/ false);
        timer_.start();
        while (api_.getOperationStage() != OperationStage::READY && timer_.elapsedSeconds() < MAX_TIME_OUT)
        {
            api_.update();
            sleep(1);
        }

        if (api_.getOperationStage() == OperationStage::READY)
            isCommandSucSend = true;

        timer_.stop();
    } break;

    case INIT:
    {
        api_.initSimulation(VtdApi::OperationMode::OPERATION, false);
        timer_.start();
        while (OperationStage::INITDONE != api_.getOperationStage() &&  timer_.elapsedSeconds() < MAX_TIME_OUT)
        {
            api_.update();
            sleep(1);
        }

        if (api_.getOperationStage() == OperationStage::INITDONE)
            isCommandSucSend = true;

        timer_.stop();

    } break;

    case START:
    {
        api_.startSimulation(VtdApi::OperationMode::OPERATION, -1.0f, false);
        timer_.start();
        api_.update();

        while (api_.getOperationStage() != OperationStage::RUN && timer_.elapsedSeconds() < MAX_TIME_OUT)
        {
            api_.update();
            sleep(1);
        }

        if (api_.getOperationStage() == OperationStage::RUN)
            isCommandSucSend = true;

        timer_.stop();
    } break;
    }

    return isCommandSucSend;
}




