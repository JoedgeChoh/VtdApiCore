#ifndef RDBIMAGESTREAMER_H
#define RDBIMAGESTREAMER_H

#include "AVFrameSource.h"
#include "AVFrameWrapper.h"
#include "RdbImageReader.h"
#include "StreamingOptions.h"
#include "PresentationTimeStampGenerator.h"

namespace SharedMemoryStreaming {

///
/// \brief Class handles the countinued reading of RDB images from shared
/// memory and conversion into AVFrames.
///
class RdbImageStreamer : public AVFrameSource {
public:
    ///
    /// \brief Setup the video stream for a specific shared memory.
    /// \param sharedMemoryKey The key of the SHM where to read RDB images from.
    ///
    RdbImageStreamer(
        const StreamingOptions& sharedMemoryKey);

    virtual ~RdbImageStreamer();

    bool getAvFrame(AVFrame& encoderFrame);

private:
    /// The collection of parsed command line options.
    const StreamingOptions streamingOptions_;

    /// Reader creates a copy of newly available RDB images in shared memory.
    RdbImageReader rdbImageReader_;

    /// This contains the AVFrame equivalent of the read RDB image.
    boost::shared_ptr<AVFrameWrapper> convertedAVFrame_;

    /// This is the RDB images that is to be converted into an AVFrame next.
    boost::shared_ptr<RdbRawImage> originalRdbFrame_;

    /// This tracks the largest generated PTS for a RDB image.
    /// FFmpeg requires PTS to be strictly increasing.
    /// Next PTS must be at least this large.
    int64_t minimalAcceptablePresentationTimeStamp_;

    /// The generator for creating timestamps for the outgoing video.
    PresentationTimeStampGenerator presentationTimeStampGenerator_;
};

} // namespace SharedMemoryStreaming
#endif
