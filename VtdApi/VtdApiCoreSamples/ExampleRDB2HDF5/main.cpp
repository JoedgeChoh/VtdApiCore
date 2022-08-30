#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <iostream>
#include <unistd.h>

#include "ExampleWriteHDF5.h"

using namespace VTD;

/**
 * Sample showing how to use VtdApi to write RdbMessages in HDF5 File by using RDB trigger.
 */
namespace
{
static const bool SHOULD_SEND_TRIGGER = true;
static const float DEFAULT_FRAME_TIME = 0.033f;
}

int main(int argc, char** argv)
{
    ExampleWriteHDF5 HDF5Sample;
    double simTime = 0.0;
    float deltaT = 0.01f;

    int simFrame = 0;
    uint32_t currentframe;
    uint32_t lastframe=-1;

    bool isfileClosed_ = false;
    bool startSent_ = false;


    if(!HDF5Sample.openfile("example")) //specify the file name
    {
        std::cerr << "Error Opening a HDF5 File" << std::endl;
        std::cerr << "Exiting the Example" << std::endl;
        exit(1);
    }


    bool isRDBConnected = HDF5Sample.initVtdApiRDB();
    bool isSCPConnected = HDF5Sample.initVtdApiSCP();


    if (!isRDBConnected)
    {
        std::cout << "RDB Connection Error" << std::endl;
        std::cout << "Exiting the Example" << std::endl;
        exit(1);
    }


    if (!isSCPConnected)
    {
        std::cout << "SCP Connection Error" << std::endl;
        std::cout << "Exiting the Example" << std::endl;
        exit(1);
    }

    HDF5Sample.api_.update();
    //command for stablizing TaskControl

    HDF5Sample.api_.sendScpCommand("<TaskControl><ImageGenerator alwaysUpdate=\"true\"/></TaskControl>");

    //Load Scenario and Init
    HDF5Sample.api_.loadScenario("TrafficDemo.xml");
    HDF5Sample.sendSCPCommand(INIT);
    HDF5Sample.api_.update();


    while((HDF5Sample.getoperatingstage() != VTD::OperationStage::RUN)&& !startSent_)
    {
        if(HDF5Sample.getoperatingstage() == VTD::OperationStage::INITDONE)
        {
            HDF5Sample.sendSCPCommand(START);
            HDF5Sample.api_.update();
            startSent_ = true;

        }
        HDF5Sample.api_.update();
    }


    HDF5Sample.setreceivedStop_(false);
    HDF5Sample.api_.sendTriggerRDB( HDF5Sample.RDBConnectionHandle_, deltaT, simTime, simFrame );
    HDF5Sample.api_.sendTriggerRDB( HDF5Sample.RDBConnectionHandle_, deltaT, simTime, simFrame );
    HDF5Sample.api_.sendTriggerRDB( HDF5Sample.RDBConnectionHandle_, deltaT, simTime, simFrame );
    HDF5Sample.api_.sendTriggerRDB( HDF5Sample.RDBConnectionHandle_, deltaT, simTime, simFrame );
    HDF5Sample.updateapi();

    while ((HDF5Sample.api_.isConnected(HDF5Sample.RDBConnectionHandle_) &&(HDF5Sample.api_.isConnected(HDF5Sample.SCPConnectionHandle_))) && startSent_)
    {
        sleep(1);

        if(HDF5Sample.gethasNewFrameBeenReceived())
        {
            currentframe = HDF5Sample.getsimframe();

            if(lastframe != currentframe)
            {
                uint32_t requestFrameNo = currentframe + 1;
                std::cout << "SEND TRIGGER (" << requestFrameNo << "): ";
                HDF5Sample.api_.sendTriggerRDB(HDF5Sample.RDBConnectionHandle_, DEFAULT_FRAME_TIME, 0, requestFrameNo);
                HDF5Sample.sethasNewFrameBeenReceived(false);
                HDF5Sample.updateapi();
                lastframe = currentframe;
            }

            if(currentframe - lastframe > 1) {
                std::cerr << "[!!!] WRITEHDF5 Skipped " << (currentframe - lastframe) << " frames [!!!]" << std::endl;
            }

        }


        if (HDF5Sample.getreceivedstop())
        {
            HDF5Sample.closeFile();
            isfileClosed_=true;
            break;


        }

    }

    if (!isfileClosed_)
        HDF5Sample.closeFile();

    return 0;
}
