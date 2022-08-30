#ifndef RDBIMAGEREADER_H
#define RDBIMAGEREADER_H

#include "RdbRawImage.h"

#include <VtdToolkit/Rdb/SharedMemoryIO.h>

#include <boost/shared_ptr.hpp>

namespace SharedMemoryStreaming {

///
/// \brief Class checks if a new RDB image is available and returns a copy if so.
///
class RdbImageReader {
public:
    ///
    /// \brief Initialize the reader for a specific shared memory usage.
    /// \param sharedMemoryKey The key of the SHM to read from.
    /// \param shmBufferFlag Defines who is reading the shared memory.
    ///
    RdbImageReader(
        const int sharedMemoryKey
        , const VTD::SharedMemoryHandle shmBufferFlag = RDB_SHM_BUFFER_FLAG_TC);

    virtual ~RdbImageReader();

    ///
    /// \brief Read a RDB image from SHM and store the result.
    /// \param rawImage Location where the RDB image is stored if one was available.
    /// \return True if a store was successful.
    ///
    bool read(boost::shared_ptr<RdbRawImage>& rawImage);

private:
    /// Object for accessing the SHM with RDB buffers.
    boost::shared_ptr<VTD::SharedMemoryIO> shdMem_;

    /// The flag used for deciding if the SHM buffer is ready to read.
    const uint shmBufferFlag_;

    /// The Id of the last frame that has been read.
    /// Id's of new frames equal to this are ignored.
    long lastFrameNumber_;
};

} // namespace SharedMemoryStreaming
#endif
