#ifndef RDBRAWIMAGE_H
#define RDBRAWIMAGE_H

#include <vector>

#include <boost/chrono/system_clocks.hpp>

#include <VtdToolkit/viRDBIcd.h>

namespace SharedMemoryStreaming {

///
/// \brief Represents a raw rdb image that has been copied from shared memory.
///
struct RdbRawImage
{
    /// A copy of the RDB image header block.
    RDB_IMAGE_t                             imageHeader;

    /// A copy of the RDB image data block.
    std::vector<uint8_t>                    imageData;

    /// The time at which the RDB image was read from the SHM.
    boost::chrono::system_clock::time_point timeOfCreation;
};

} // namespace SharedMemoryStreaming
#endif
