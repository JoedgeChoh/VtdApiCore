#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <VtdToolkit/Rdb/SharedMemoryIO.h>
#include <VtdToolkit/Rdb/RdbImageIO.h>

#include <iostream>
#include <unistd.h>
#include <sstream>
#include <limits.h>
#include <vector>

using namespace VTD;
/**
 * Sample showing how to use VtdApi to read from multiple shared memory regions
 */

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

    i = static_cast<T>( l );;
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

int main(int argc, char** argv)
{
    std::vector <SharedMemoryHandle> shmKeys;

    std::vector<SharedMemoryIO*> shmIoVec;

    VtdApi apiVtd;

    bool isAttached = false;

    // Handle for sending sync
    ConnectionHandle handle = 0;

    handle = apiVtd.connectRDB("localhost", DEFAULT_RDB_PORT, Protocols::RDB_TCP);

    if (handle == 0)
    {
        std::cout << "Could not connect to VTD" << std::endl;
        std::cout << "Start VTD with appropriate setup" << std::endl;
        std::cout << "for example Stereo.LDR.FullHD.Distorted.SHM.NewSync" << std::endl;
        std::cout << "Usage: Number of shared memory regions <number> ExampleShm2Png <shm-key> buffer flag <flag>" << std::endl;
        std::cout << "e.g.: ExampleShm2Png 2 0x0120a 0x0120b 2" << std::endl;
        exit(1);
    }

    double simTime = 0.0;
    float deltaT = 0.01f;

    unsigned int simFrame = 0;
    int argument = 1;

    uint32_t lastFrameNo = 0;

    unsigned int bufferFlag;
    unsigned int numberOfSharedMemories = 0;

    if (argc < 4)
    {
       std::cout << "Usage: Number of shared memory regions <number> Shm2Png <shm-key> buffer flag <flag>" << std::endl;
       std::cout << "e.g.: Four.FishEye 4 0x08130 0x08131 0x08132 0x08133 2" << std::endl;
       exit(2);
    }

    str2var(numberOfSharedMemories, argv[argument]);

    shmKeys.resize(numberOfSharedMemories);

    for (size_t i = 0; i < shmKeys.size(); i++)
    {
        str2var(shmKeys[i], argv[++argument]);
    }

    str2var(bufferFlag, argv[++argument]);

    apiVtd.sendTriggerRDB(handle, deltaT, simTime, simFrame);

    for (std::vector<SharedMemoryHandle>::const_iterator itr = shmKeys.begin(); itr < shmKeys.end(); ++itr)
    {
        std::cout << *itr << std::endl;
        shmIoVec.push_back(new SharedMemoryIO (*itr));
        shmIoVec.back()->attach();
        isAttached = shmIoVec.back()->isAttached();
        if (!isAttached)
        {
             exit(1);
        }
    }

    while (isAttached)
    {
        uint32_t frameNo = 0;
        simTime += deltaT;

        for (std::vector<SharedMemoryIO*>::iterator itr = shmIoVec.begin(); itr < shmIoVec.end(); ++itr)
        {
            SharedMemoryBuffer buffer = (*itr)->getNextBuffer(bufferFlag);
            if (buffer.rdbMsg && buffer.info)
            {
               (*itr)->lockBuffer(*buffer.info);
               frameNo = buffer.rdbMsg->hdr.frameNo;
               if (lastFrameNo != frameNo)
               {
                   std::cout << "Writing frame " << frameNo << std::endl;
                   RDB_IMAGE_t* image = fetchRdbImage(buffer.rdbMsg);
                   std::string fileName = "frame_" + toString(frameNo) + "_" + toString((*itr)->getShmHandle()) + ".png";
                   if(!RdbImageIO::writeRdbImgToFile(*image, fileName, RdbImageIO::FileFormat::PNG, 0, true))
                   {
                       std::cerr << "Error writing file " << fileName << std::endl;
                   }
               }
               buffer.info->flags &= ~bufferFlag;
               (*itr)->releaseBuffer(*buffer.info);
           }
           if (!(*itr)->isAttached())
           {
                isAttached = false;
                break;
           }
       }
        lastFrameNo = frameNo;
        boost::this_thread::sleep_for(boost::chrono::microseconds(50));
    }
    // Delete pointers to shared memory IO
    for (size_t i = 0; i < shmIoVec.size(); i++)
    {
        delete shmIoVec[i];
        shmIoVec[i] = 0;
    }

    shmIoVec.clear();
    // disconnect RDB
    apiVtd.disconnectRDB(handle);

    return 0;
}
