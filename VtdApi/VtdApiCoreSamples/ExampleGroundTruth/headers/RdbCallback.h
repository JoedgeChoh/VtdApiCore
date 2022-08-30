#ifndef _RDB_CALLBACK_H
#define _RDB_CALLBACK_H

#include <VtdApi/VtdApi.h>
#ifdef HDF_ENABLED
#include <VtdHdf5/WriteHdf5Data.h>
#endif
#include <VtdCore/Timer.h>

#include "TestDefinition.h"
#include "DataFilter.h"

const static double TIME_OUT_RDB = 120.0;

class RdbCallback : public DataFilter
{

public:
    /**
     * @brief RdbCallback - constructor of the class
     */
    RdbCallback();

    /**
     * @brief ~RdbCallback
     */
    virtual ~RdbCallback();

    /**
     * @brief handleGeneralRdbMessage
     * @param msg
     */
    void handleGeneralRdbMessage(const VTD::ReceiveRDB* msg);

    /**
     * @brief initVtdApi
     * @return
     */
    bool initVtdApi();

    /**
     * @brief closeVtdApi
     * @return
     */
    bool closeVtdApi();

    /**
     * @brief openFile
     * @param fileName
     * @param hdf5Folder
     * @return
     */
    bool openFile(const std::string& fileName, const std::string& hdf5Folder);

    /**
     * @brief closeFile
     */
    void closeFile ();

    /**
     * @brief setFileName
     * @param fileName
     */
    void setFileName(const std::string& fileName);

    /**
     * @brief partToWrite
     * @param RDBMessage
     */
    void partToWrite (const RDB_MSG_t& RDBMessage);

    /**
     * @brief connectRdbHandle
     */
    bool connectRdbHandle(VTD::ConnectionHandle& connectionHandle, const double& timeOut, const unsigned int portNumber);

    bool connectSCPHandle(VTD::ConnectionHandle& connectionHandle, const double& timeOut);

    /**
     * @brief getSimulationTime
     * @return
     */
    inline double getSimulationTime(){return simulationTime_;}

public:
    //
    VTD::VtdApi vtdApi_;
    //
    VTD::ConnectionHandle generalRDBHandle_, generalSCPHandle_;

private:

    double simulationTime_;

    bool isFileOpen_, verbose_;
#ifdef HDF_ENABLED
    RdbToHdf5Writer::WriteHdf5Data writeHdf5Data_;
#endif
    VTD::Timer timer_;
};

#endif //_RDBCALLBACK_H
