#ifndef EXAMPLE_WRITE_HDF5_H
#define EXAMPLE_WRITE_HDF5_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>
#ifdef HDF_ENABLED
#include <VtdHdf5/WriteHdf5Data.h>
#endif
#include <VtdCore/Timer.h>
#include <VtdCore/FileSystemIO.h>

/**
 * Class ExampleWriteHDF5 a simple example to write RDB Data into HDF5 files.
 */

using namespace VTD;

enum COMMAND {STOP, START, INIT};

class ExampleWriteHDF5 {
public:
    /**
     * constructor
     */
    ExampleWriteHDF5();

    ~ExampleWriteHDF5();

    /**
     * @brief handleRdbMessage - receive RDB
     * @param msg - RDB message
     */
    void handleRdbMessage(const ReceiveRDB* msg);
    
    
    /**
     * @brief handleMessageSCP - receive SCP
     * @param msg - SCP message
     */

    void handleMessageSCP(const ReceiveSCP* msg);

    
    
    /**
     * @brief initVtdApiRDB - initalaze VtdApi connection to RDB
     * @return true when API is initalized and connected to VTD's RDB
     */
    
    bool initVtdApiRDB();
    
        /**
     * @brief initVtdApiSCP - initalaze VtdApi connection to SCP
     * @return true when API is initalized and connected to VTD's SCP
     */

    bool initVtdApiSCP();
    
    /**
     * @brief closeVtdApi - closed the active connection to SCP and RDB
     */
    
    bool closeVtdApi();
    
    
    bool sendSCPCommand(COMMAND command);
    

    //getters
    bool gethasNewFrameBeenReceived() {return hasNewFrameBeenReceived;}
    
    bool getreceivedstop() {return receivedStop_;}

    bool getreceivedstart() {return receivedStart_;}
    
    double getsimtime() {return simulationtime;}
    uint32_t getsimframe(){return simulationframe;}


    VTD::OperationStage::Enum getoperatingstage() {
        api_.update();
        return api_.getOperationStage();}

    //setters
    void setreceivedStop_(bool value) {receivedStop_ = value;}

    void sethasNewFrameBeenReceived(bool value) {hasNewFrameBeenReceived = value;}


    
    /**
     * @brief parttowrite - writes the RDB Message to a HDF5 File
     * @param RDBMessage - RDB message
     */
    void parttowrite(const RDB_MSG_t& RDBMessage);


        /**
     * @brief  openfile- creates and opens a HDF5 file for writing
     */
    bool openfile(std::string file);

    
    /**
     * @brief  closeFile- closes the HDF5 file after writing
     */
    void closeFile ();

    
    //interface to update the VTDApi
    void updateapi();



    // Handle for incomming and outgoing RDB data
    ConnectionHandle RDBConnectionHandle_;
    ConnectionHandle SCPConnectionHandle_;

#ifdef HDF_ENABLED
RdbToHdf5Writer::WriteHdf5Data writeHdf5Data_;
#endif

    // VtdApi instance
    VtdApi api_;

private:
    // Default player ID

    // If sample should send trigger
    bool hasNewFrameBeenReceived;

    bool is_fileopen;

    bool receivedStop_;

    bool receivedStart_;

    double simulationtime;

    uint32_t simulationframe;

    Timer timer_;




};
#endif // EXAMPLE_RDB_PRINT_H
