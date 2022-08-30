#include "RdbImageReader.h"

#include <boost/chrono/system_clocks.hpp>

using namespace SharedMemoryStreaming;

namespace {

///
/// \brief Return a copy of a rdb image if the rdb message of type image.
/// \param msg The rdb message to inspect.
/// \param rawImage A copy of the rdb image is stored here as well as the rdb
/// message header and the time at which the buffer is copied.
/// \return True if an rdb image was copied.
///
bool fetchRawImage(
    RDB_MSG_t* msg
    , boost::shared_ptr<RdbRawImage>& rawImage)
{
    // Get the header of the message
    RDB_MSG_ENTRY_HDR_t* entry = reinterpret_cast<RDB_MSG_ENTRY_HDR_t*>(
        reinterpret_cast<unsigned char*>(msg) + msg->hdr.headerSize);
    uint32_t remainingBytes = msg->hdr.dataSize;

    while (remainingBytes)
    {
        // Get the number of elements in this entry
        unsigned int noElements =
            entry->elementSize ? (entry->dataSize / entry->elementSize) : 0;
        // Get pointer to the first data element
        unsigned char* dataPtr = reinterpret_cast<unsigned char*>(entry);
        dataPtr += entry->headerSize;

        while (noElements--)
        {
            switch (entry->pkgId)
            {
                case RDB_PKG_ID_IMAGE:
                {
                    // Copy the rdb image, header and save the time
                    RDB_IMAGE_t* rdbImage =
                        reinterpret_cast<RDB_IMAGE_t*>(dataPtr);
                    rawImage->imageHeader = *rdbImage;
                    rawImage->timeOfCreation = boost::chrono::system_clock::now();
                    rawImage->imageData.assign(
                        dataPtr + sizeof(RDB_IMAGE_t)
                        , dataPtr + sizeof(RDB_IMAGE_t) + rdbImage->imgSize);
                    return true;
                }
                default:
                { /* not handled */ }
                                    break;
            }
            dataPtr += entry->elementSize;
        }

        remainingBytes -= (entry->headerSize + entry->dataSize);

        if (remainingBytes)
        {
            entry = reinterpret_cast<RDB_MSG_ENTRY_HDR_t*>(
                reinterpret_cast<unsigned char*>(entry)
                + entry->headerSize
                + entry->dataSize);
        }
    }
    return false;
}

} // namespace {

RdbImageReader::RdbImageReader(
    const int sharedMemoryKey
    , const uint shmBufferFlag)
    : shmBufferFlag_(shmBufferFlag)
    , lastFrameNumber_(-1)
{
    shdMem_ = boost::shared_ptr<VTD::SharedMemoryIO>(
        new VTD::SharedMemoryIO(sharedMemoryKey));
}

RdbImageReader::~RdbImageReader()
{

}

bool RdbImageReader::read(
    boost::shared_ptr<RdbRawImage>& rawImage)
{
    if (shdMem_ == NULL)
    {
        return false;
    }

    if (!shdMem_->isAttached())
    {
        shdMem_->attach();
        if (!shdMem_->isAttached())
        {
            return false;
        }
    }

    VTD::SharedMemoryBuffer buffer = shdMem_->getNextBuffer(shmBufferFlag_);

    if (buffer.rdbMsg && buffer.info)
    {
        // Lock the buffer
        shdMem_->lockBuffer(*buffer.info);

        // Only accept this message, and the possible rdb image, if
        // it is not the previously read ID.
        const bool hasNewRawImage =
            lastFrameNumber_ != buffer.rdbMsg->hdr.frameNo;

        if (hasNewRawImage)
        {
            fetchRawImage(buffer.rdbMsg, rawImage);
            // Remember the frame number to prevent duplicate reads
            lastFrameNumber_ = buffer.rdbMsg->hdr.frameNo;
        }

        buffer.info->flags &= ~shmBufferFlag_;

        // Unlock the buffer
        shdMem_->releaseBuffer(*buffer.info);

        return hasNewRawImage;
    }
    else
    {
        return false;
    }
}
