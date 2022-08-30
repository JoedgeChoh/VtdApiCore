#ifndef AVCODECWRAPPER_H
#define AVCODECWRAPPER_H

extern "C" {
#include <libavcodec/avcodec.h>
}

namespace SharedMemoryStreaming {

///
/// \brief Class verifies that the av codec with a given ID exists.
///
class AVCodecWrapper {
public:
    ///
    /// \brief Checks if a codec ID is used and provides the found AvCodec
    /// \param codecId The codec ID to search
    ///
    AVCodecWrapper(const AVCodecID& codecId);

    ///
    /// \brief Get the AvCodec having the specified id
    /// \return The AvCodec
    ///
    const AVCodec* getCodecHandle() const
    {
        return codecHandle_;
    }

private:
    /// The found AvCodec for the given id
    const AVCodec* codecHandle_;
};

} // namespace SharedMemoryStreaming
#endif
