#include "RdbCallback.h"
#include "LogFile.h"

#include <VtdCore/FileSystemIO.h>
#include <VtdToolkit/RDBHandler.hh>
#include <boost/bind.hpp>

#include <unistd.h>
#include <string>
#include <cmath>

using namespace VTD;
using namespace test_definition;
namespace
{
    // default host
    const std::string DEFAULT_HOST = "127.0.0.1";
}

RdbCallback::RdbCallback() :
      generalRDBHandle_ (0)
    , generalSCPHandle_(0)
    , simulationTime_(0)
    , isFileOpen_(false)
    , verbose_(false)
{
    // Initilaze filter
    initFilter();
}

RdbCallback::~RdbCallback()
{
    closeVtdApi();
}

bool RdbCallback::initVtdApi()
{
    // Handle SCP message
    if (!connectSCPHandle(generalSCPHandle_, TIME_OUT_RDB))
        return false;

    // Handle for general RDB daten
    if (!connectRdbHandle(generalRDBHandle_, TIME_OUT_RDB, DEFAULT_RDB_PORT))
        return false;

    if (generalRDBHandle_)
    {
       vtdApi_.registerEventFunc<RdbCallback, ReceiveRDB>(this, &RdbCallback::handleGeneralRdbMessage, generalRDBHandle_);
       std::cout << "VtdApi: Initalized \n";
       return true;
    }
    else
    {
       return false;
    }
}

void RdbCallback::handleGeneralRdbMessage(const ReceiveRDB* msg)
{
    partToWrite(msg->getData());
}

bool RdbCallback::closeVtdApi()
{
    if (vtdApi_.isConnected(generalRDBHandle_))
    {
        vtdApi_.deregisterEventFunc<RdbCallback, ReceiveRDB>(this, &RdbCallback::handleGeneralRdbMessage, generalRDBHandle_);
        // Handle for RDB daten
        vtdApi_.disconnectRDB(generalRDBHandle_);
        generalRDBHandle_ = 0;
        vtdApi_.disconnectSCP(generalSCPHandle_);
        generalSCPHandle_ = 0;
        printf("VtdApi: Close \n");
        return true;
    }
    else
    {
        if (verbose_)
            printf("ERROR: Could not establish connection\n");

        return false;
    }
}

bool RdbCallback::openFile(const std::string& fileName, const std::string& hdf5Folder)
{
    isFileOpen_ = true;
#ifdef HDF_ENABLED
    writeHdf5Data_.openHdf5File(hdf5Folder + "/" + fileName);
#endif
    return true;
}

void RdbCallback::setFileName(const std::string& fileName)
{
    std::string temp = "/tmp/";
    temp.append(Internal::FileSystemIO::getFileNameFromPath(fileName));
}

void RdbCallback::closeFile ()
{
#ifdef HDF_ENABLED
    writeHdf5Data_.closeHdf5AllFolders();
    writeHdf5Data_.closeHdf5File();
#endif
    isFileOpen_ = false;
    simulationTime_ = 0;
}

void RdbCallback::partToWrite (const RDB_MSG_t& RDBMessage)
{
    if (!isFileOpen_)
        return;
#ifdef HDF_ENABLED
    if (filter_.find(RDBMessage.entryHdr.pkgId)->second == true)
        writeHdf5Data_.writeRdbMessage(RDBMessage);
#endif
    simulationTime_ = RDBMessage.hdr.simTime;
}

bool RdbCallback::connectRdbHandle(ConnectionHandle& connectionHandle, const double& timeOut, const unsigned int portNumber)
{
    // Handle for EGO sensor data
    timer_.start();
    while (connectionHandle == 0 && timer_.elapsedSeconds() < timeOut)
    {
         connectionHandle =  vtdApi_.connectRDB(DEFAULT_HOST, portNumber, Protocols::RDB_TCP);
         sleep(1);
    }
    timer_.stop();

    if (verbose_)
        if (connectionHandle == 0)
        {
            g_pLogFile->fTextOut("Cann't connect handle %d communication time out\n ", connectionHandle);
        }

    return (connectionHandle == 0) ? false : true;
}

bool RdbCallback::connectSCPHandle(ConnectionHandle& connectionHandle, const double& timeOut)
{
    // Handle for EGO sensor data
    timer_.start();
    while (connectionHandle == 0 && timer_.elapsedSeconds() < timeOut)
    {
         connectionHandle =  vtdApi_.connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
         sleep(1);
    }
    timer_.stop();

    if (verbose_)
        if (connectionHandle == 0)
        {
            g_pLogFile->fTextOut("Cann't connect handle %d communication time out\n ", connectionHandle);
        }

    return (connectionHandle == 0) ? false : true;
}
