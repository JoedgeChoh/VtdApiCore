#include <iostream>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <boost/cast.hpp>
#include <VtdToolkit/RDBHandler.hh>
#include <VtdToolkit/Rdb/SharedMemoryIO.h>
#include <VtdCore/Logging/Log.h>

namespace VTD {

SharedMemoryIO::SharedMemoryIO(SharedMemoryHandle shmKey) :
    rdbHandler_(),
    shm_(shmKey)
{
}

SharedMemoryIO::~SharedMemoryIO()
{
    /* do nothing */
}

bool SharedMemoryIO::createAndAttach(size_t size)
{
    if(shm_.createAndAttach(size)) {
        return rdbHandler_.shmConfigure( shm_.getStart(), 1, boost::numeric_cast<unsigned int>(shm_.getSize()) );
    }
    return false;
}

bool SharedMemoryIO::attach()
{
    return shm_.attach() != 0;
}

unsigned int SharedMemoryIO::getNumberOfBuffers() const
{
    void* shmPtr = shm_.getStart();
    if(shmPtr == 0) {
        return 0;
    }

    RDB_SHM_HDR_t* shmHdr = static_cast<RDB_SHM_HDR_t*>(shmPtr);
    return shmHdr->noBuffers;
}

SharedMemoryBuffer SharedMemoryIO::getBufferInfo(unsigned int index)
{
    void* mShmPtr = shm_.getStart();

    RDB_SHM_BUFFER_INFO_t* info = rdbHandler_.shmBufferGetInfo(index);
    SharedMemoryBuffer result;
    if(info != 0) {
        result.info = info;
        result.rdbMsg = reinterpret_cast<RDB_MSG_t*>( reinterpret_cast<unsigned char*>(mShmPtr) +  info->offset );
    }
    return result;
}

SharedMemoryBufferList SharedMemoryIO::getBuffers()
{
    void* mShmPtr = shm_.getStart();
    RDB_SHM_HDR_t* shmHdr = static_cast<RDB_SHM_HDR_t*>(mShmPtr);

    if(mShmPtr == 0 || shmHdr->noBuffers == 0) {
        return SharedMemoryBufferList();
    }

    SharedMemoryBufferList result;

    unsigned char* dataPtr = reinterpret_cast<unsigned char*>(shmHdr) + shmHdr->headerSize;

    for(int i=0; i<shmHdr->noBuffers; ++i) {
        SharedMemoryBuffer buffer;
        buffer.info = reinterpret_cast<RDB_SHM_BUFFER_INFO_t*>(dataPtr);
        buffer.rdbMsg = reinterpret_cast<RDB_MSG_t*>(reinterpret_cast<unsigned char*>(mShmPtr) + buffer.info->offset);
        result.push_back(buffer);

        dataPtr += buffer.info->thisSize;
    }
    return result;
}

SharedMemoryBuffer SharedMemoryIO::getNextBuffer(unsigned int checkMask) {
    void* shmPtr = shm_.getStart();
    RDB_SHM_HDR_t* shmHdr = static_cast<RDB_SHM_HDR_t*>(shmPtr);

    if(shmPtr == 0 || shmHdr->noBuffers == 0) {
        return SharedMemoryBuffer(); //empty
    }

    unsigned char* dataPtr = reinterpret_cast<unsigned char*>(shmHdr) + shmHdr->headerSize;

    RDB_SHM_BUFFER_INFO_t* currentBufferInfo = 0;
    RDB_MSG_t* currentRdbMsg = 0;
    uint32_t minFrameNo = ~0;
    for(int i = 0; i < shmHdr->noBuffers; ++i) {
        RDB_SHM_BUFFER_INFO_t* bufferInfo = reinterpret_cast<RDB_SHM_BUFFER_INFO_t*>(dataPtr);
        dataPtr += bufferInfo->thisSize;

        RDB_MSG_t* rdbMsg = reinterpret_cast<RDB_MSG_t*>(reinterpret_cast<unsigned char*>(shmPtr) + bufferInfo->offset);

        unsigned int flags = bufferInfo->flags;
        bool readyForRead = ((flags & checkMask) || !checkMask)
                             && !(flags & RDB_SHM_BUFFER_FLAG_LOCK);

        if(readyForRead && (rdbMsg->hdr.frameNo < minFrameNo)) {
            currentBufferInfo = bufferInfo;
            minFrameNo = rdbMsg->hdr.frameNo;
            currentRdbMsg = rdbMsg;
        }
    }

    SharedMemoryBuffer buffer;
    buffer.info = currentBufferInfo;
    buffer.rdbMsg = currentRdbMsg;
    return buffer;
}

SharedMemoryBuffer SharedMemoryIO::tryGetBuffer(unsigned int checkMask, uint16_t bufferId) {

    void* shmPtr = shm_.getStart();
    RDB_SHM_HDR_t* shmHdr = static_cast<RDB_SHM_HDR_t*>(shmPtr);

    if(shmPtr == 0 || shmHdr->noBuffers == 0) {
        return SharedMemoryBuffer();
    }

    unsigned char* dataPtr = reinterpret_cast<unsigned char*>(shmHdr) + shmHdr->headerSize;

    RDB_SHM_BUFFER_INFO_t* currentBufferInfo = 0;
    RDB_MSG_t* currentRdbMsg  = 0;
    for(int i=0; i<shmHdr->noBuffers; ++i) {
        RDB_SHM_BUFFER_INFO_t* bufferInfo = reinterpret_cast<RDB_SHM_BUFFER_INFO_t*>(dataPtr);
        dataPtr += bufferInfo->thisSize;

        unsigned int flags = bufferInfo->flags;
        bool readyForRead = ((flags & checkMask) || !checkMask) && !(flags & RDB_SHM_BUFFER_FLAG_LOCK);

        if(readyForRead && bufferInfo->id == bufferId) {
            currentBufferInfo = bufferInfo;
            currentRdbMsg = reinterpret_cast<RDB_MSG_t*>( ( reinterpret_cast<unsigned char*>(shmPtr) ) + bufferInfo->offset );
        }
    }

    SharedMemoryBuffer buffer;
    buffer.info = currentBufferInfo;
    buffer.rdbMsg = currentRdbMsg;
    return buffer;
}

bool SharedMemoryIO::destroy() {
    return shm_.destroy() != 0;
}

bool SharedMemoryIO::detach() {
    return shm_.detach() != 0;
}

bool SharedMemoryIO::tryLockBuffer(RDB_SHM_BUFFER_INFO_t& buffer) {
    if(!(buffer.flags & RDB_SHM_BUFFER_FLAG_LOCK)) {
        buffer.flags |= RDB_SHM_BUFFER_FLAG_LOCK;
        return true;
    }
    //already locked
    return false;
}

}//namespace VTD
