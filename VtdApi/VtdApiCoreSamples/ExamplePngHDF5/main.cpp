#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <iostream>
#include <unistd.h>

#include <VtdToolkit/Rdb/SharedMemoryIO.h>
#include <VtdToolkit/Rdb/RdbImageIO.h>
#include "ExamplePngHDF5.h"

using namespace VTD;

/**
 * Sample showing how to use VtdApi with RdbMessages and SHM with RDB Trigger to write RDB Messages in HDF5 File and Images in SHM as PNG Images.
 */
namespace
{
static const float DEFAULT_FRAME_TIME = 0.033f;
}

// global variables
uint32_t lastFrameNo=0;
uint32_t frameNo = 0;
bool allpictureswritten_ = false;
bool lastframenotread = false;
uint32_t FIRST_IMAGE_FRAME_NO = 3;


template<typename T>
std::string toHexString(T value)
{
    std::stringstream ss;
    ss << std::hex << value;
    return ss.str();
}

template<typename T>
std::string toString(T value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template<typename T>
void str2var (T &i, char const *s, int base = 0)
{
    char *end;
    long  l;
    errno = 0;
    l = strtol(s, &end, base);

    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) std::cerr << "Overflow" << std::endl;
    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) std::cerr << "Underflow" << std::endl;
    if (*s == '\0' || *end != '\0') std::cerr << "Inconvertible" << std::endl;

    i = static_cast<T>( l );
    std::cerr << "Success" << std::endl;
}


RDB_IMAGE_t* fetchRdbImage(RDB_MSG_t* msg)
{
    RDB_MSG_ENTRY_HDR_t* entry = reinterpret_cast<RDB_MSG_ENTRY_HDR_t*>(reinterpret_cast<unsigned char*>(msg) + msg->hdr.headerSize);
    uint32_t remainingBytes = msg->hdr.dataSize;

    while (remainingBytes)
    {
        unsigned int noElements = entry->elementSize ? (entry->dataSize / entry->elementSize) : 0;
        unsigned char* dataPtr = reinterpret_cast<unsigned char*>(entry);
        dataPtr += entry->headerSize;

        while (noElements--)
        {
            switch(entry->pkgId)
            {
            case RDB_PKG_ID_IMAGE: return reinterpret_cast<RDB_IMAGE_t*>(dataPtr);
            default: /* not handled */ break;
            }
            dataPtr += entry->elementSize;
        }

        remainingBytes -= (entry->headerSize + entry->dataSize);

        if (remainingBytes)
        {
            entry = reinterpret_cast<RDB_MSG_ENTRY_HDR_t*>(reinterpret_cast<unsigned char*>(entry) + entry->headerSize + entry->dataSize);
        }
    }
    return reinterpret_cast<RDB_IMAGE_t*>(0);
}


void run(SharedMemoryIO *shmIo, unsigned int bufferFlag)
{

    allpictureswritten_ = false;
    while (shmIo->isAttached())
    {
        SharedMemoryBuffer buffer = shmIo->getNextBuffer(bufferFlag);
        while(buffer.rdbMsg && buffer.info)
        {
            shmIo->lockBuffer(*buffer.info);
            frameNo = buffer.rdbMsg->hdr.frameNo;
            if (lastFrameNo != frameNo)
            {
                RDB_IMAGE_t* image = fetchRdbImage(buffer.rdbMsg);
                std::string fileName = "frame_" + toString(frameNo) + "_" + toHexString(shmIo->getShmHandle()) + ".png";
                if(!RdbImageIO::writeRdbImgToFile(*image, fileName, RdbImageIO::FileFormat::PNG, 0, true))
                {
                    std::cerr << "Error writing file " << fileName << std::endl;
                }

                if(frameNo - lastFrameNo > 1) {
                    lastframenotread = true;
                    std::cerr << "[!!!] VIG skipped " << (frameNo - lastFrameNo) << " frames [!!!]" << std::endl;
                }
            }
            lastFrameNo = frameNo;

            buffer.info->flags &= ~bufferFlag;
            shmIo->releaseBuffer(*buffer.info);
            buffer = shmIo->getNextBuffer(bufferFlag);

        }


        allpictureswritten_ = true;
    }
    delete shmIo;

}



int main(int argc, char** argv)
{

    ExamplePngHDF5 HDF5PngSample;

    boost::thread imagethread_;
    std::vector <SharedMemoryHandle> shmKeys;

    std::vector<SharedMemoryIO*> shmIoVec;

    double simTime = 0.0;
    float deltaT = 0.01f;
    int simFrame = 0;
    int argument = 1;
    bool isAttached =false;

    unsigned int bufferFlag;
    unsigned int numberOfSharedMemories = 0;
    bool isfileClosed_ = false;
    bool startSent_    = false;


    if (argc < 4)
    {
        std::cout << "Usage: Number of shared memory regions <number> Shm2Png <shm-key> buffer flag <flag>" << std::endl;
        std::cout << "e.g.: Deterministic.headless 1 0x08130 2" << std::endl;
        exit(2);
    }

    bool isSCPConnected = HDF5PngSample.initVtdApiSCP();
    bool isRDBConnected = HDF5PngSample.initVtdApiRDB();


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

    if(!HDF5PngSample.openfile("file"))
    {
        std::cerr << "Error Opening a HDF5 File" << std::endl;
        std::cerr << "Exiting the Example" << std::endl;
        exit(1);
    }


    HDF5PngSample.api_.update();
    //command for stablizing TaskControl

    HDF5PngSample.api_.sendScpCommand("<TaskControl><ImageGenerator alwaysUpdate=\"true\"/></TaskControl>");

    //Load Scenario and Init
    HDF5PngSample.api_.loadScenario("TrafficDemo.xml");
    HDF5PngSample.sendSCPCommand(INIT);
    HDF5PngSample.api_.update(-1);


    str2var(numberOfSharedMemories, argv[argument]);

    shmKeys.resize(numberOfSharedMemories);

    for (size_t i = 0; i < shmKeys.size(); i++)
    {
        str2var(shmKeys[i], argv[++argument]);
    }

    str2var(bufferFlag, argv[++argument]);

    SharedMemoryIO* shmIo = new SharedMemoryIO (shmKeys[0]);


    while ((HDF5PngSample.getoperatingstage() != VTD::OperationStage::RUN)&& !startSent_ )
    {
        if(HDF5PngSample.getoperatingstage() == VTD::OperationStage::INITDONE)
        {
            HDF5PngSample.sendSCPCommand(START);
            HDF5PngSample.api_.update();

            shmIo->attach();
            isAttached = shmIo->isAttached();
            startSent_ = true;
        }
        HDF5PngSample.api_.update();
    }



    //initial trigger
    HDF5PngSample.api_.sendTriggerRDB( HDF5PngSample.RDBConnectionHandle_, deltaT, simTime, simFrame);
    HDF5PngSample.api_.sendTriggerRDB( HDF5PngSample.RDBConnectionHandle_, deltaT, simTime, simFrame);
    HDF5PngSample.api_.sendTriggerRDB( HDF5PngSample.RDBConnectionHandle_, deltaT, simTime, simFrame);
    HDF5PngSample.api_.sendTriggerRDB( HDF5PngSample.RDBConnectionHandle_, deltaT, simTime, simFrame);

    if (!isAttached)
    {
        std::cerr << "\n Error Attaching to Shared Memory, Exiting" << std::endl;
        exit(1);
    }



    //thread to handle png image writing
    imagethread_= boost::thread(&run, boost::ref(shmIo), boost::ref(bufferFlag));

    HDF5PngSample.setreceivedStop_(false);

    while ((HDF5PngSample.api_.isConnected(HDF5PngSample.RDBConnectionHandle_) &&(HDF5PngSample.api_.isConnected(HDF5PngSample.SCPConnectionHandle_))) && startSent_)
    {
        uint32_t currentframe = HDF5PngSample.getsimframe();
        HDF5PngSample.api_.update();
        if(HDF5PngSample.gethasNewFrameBeenReceived())
        {
            // If image output is activated
            // ImageWriter is still reading from SHM
            if (!allpictureswritten_)
            {
                // Relevant image: Sleep a short amout of time and check again
                if (HDF5PngSample.getsimframe() > FIRST_IMAGE_FRAME_NO)
                {
                    boost::this_thread::sleep_for(boost::chrono::microseconds(10));
                    continue;
                }
                // Irrelevant image: Sleep some time but trigger them anyway
                else
                {
                    boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
                }
            }

            else if (!allpictureswritten_ && lastframenotread)
            {
                static uint32_t maxWaitMicroSeconds = 1000;
                boost::this_thread::sleep_for(boost::chrono::microseconds(maxWaitMicroSeconds));

            }

            if (HDF5PngSample.getreceivedstop())
            {
                std::cerr << "\n STOP RECEIVED" << std::endl;
                HDF5PngSample.closeFile();
                isfileClosed_=true;
                exit(1);

            }

            uint32_t requestFrameNo = currentframe + 1;
            std::cout << "SEND TRIGGER (" << requestFrameNo << "): ";
            HDF5PngSample.api_.sendTriggerRDB(HDF5PngSample.RDBConnectionHandle_, DEFAULT_FRAME_TIME, 0, requestFrameNo);
            HDF5PngSample.sethasNewFrameBeenReceived(false);
            HDF5PngSample.api_.update();

        }

    }

    imagethread_.join();

    if(!isfileClosed_)
        HDF5PngSample.closeFile();

    delete shmIo;
    shmIoVec.clear();
    return 0;

    
}
