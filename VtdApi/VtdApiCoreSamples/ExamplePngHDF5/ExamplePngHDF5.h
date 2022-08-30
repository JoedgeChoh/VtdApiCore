#ifndef EXAMPLE_RDB_PRINT_H
#define EXAMPLE_RDB_PRINT_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/RDBHandler.hh>
#ifdef HDF_ENABLED
#include <VtdHdf5/WriteHdf5Data.h>
#endif
#include <VtdCore/Timer.h>
#include <VtdCore/FileSystemIO.h>

/**
 * Class ExamplePngHDF5 a simple example to write RDB Data into HDF5 files.
 */

using namespace VTD;

enum COMMAND {STOP, START, INIT};

class ExamplePngHDF5 {
public:
    /**
     * constructor
     */
    ExamplePngHDF5();

    ~ExamplePngHDF5();
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
     * @brief parttowrite - writes the RDB Message to a HDF5 File
     * @param RDBMessage - RDB message
     */
    void parttowrite(const RDB_MSG_t& RDBMessage);

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

    /**
     * @brief  gethasNewFrameBeenReceived - interface to check if a new frame has been received
     */


    /**
     * @brief  openfile- creates and opens a HDF5 file for writing
     */
    bool openfile(std::string file);


    /**
     * @brief  closeFile- closes the HDF5 file after writing
     */
    void closeFile ();

      /**
     * @brief  updateapi- Interface to Update the VtdApi
     */
    void updateapi();
    
          /**
     * @brief  sendSCPCommand- SendSCP Start,Stop and Init Command
     * @param OMMAND- enum containing the command list
     */

    bool sendSCPCommand(COMMAND command);
    
    
    //getters
    bool gethasNewFrameBeenReceived() {return hasNewFrameBeenReceived;}

    bool getreceivedstop() {return receivedStop_;}

    bool getreceivedstart() {return receivedStart_;}

    VTD::OperationStage::Enum getoperatingstage() {
        api_.update();
        return api_.getOperationStage();}


    double getsimtime() {return simulationtime; }
    uint32_t getsimframe() {return simulationframe;}


    // setters
    void setreceivedStop_(bool value) {receivedStop_ = value;}


    void sethasNewFrameBeenReceived(bool value) {hasNewFrameBeenReceived = value;}





    // Handle for incomming and outgoing RDB data
    ConnectionHandle RDBConnectionHandle_;
    ConnectionHandle SCPConnectionHandle_;

    //Handle for opening, writing and closing HDF5 files
#ifdef HDF_ENABLED
RdbToHdf5Writer::WriteHdf5Data writeHdf5Data_;
#endif

    // VtdApi instance
    VtdApi api_;

private:

    // If sample should send trigger
    bool hasNewFrameBeenReceived;

    // is HDF5 file open
    bool is_fileopen;

    // has the stop command been received
    bool receivedStop_;

   // has the start command been received
    bool receivedStart_;

    //Simulation Specific
    double simulationtime;

    uint32_t simulationframe;

    Timer timer_;




};
#endif // EXAMPLE_RDB_PRINT_H
