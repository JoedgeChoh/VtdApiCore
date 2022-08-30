#ifndef PRESENTATIONTIMESTAMPGENERATOR_H
#define PRESENTATIONTIMESTAMPGENERATOR_H

#include <stdint.h>

struct AVRational;

namespace SharedMemoryStreaming {

class RdbRawImage;

///
/// \brief Class generates presentations time stamps (PTS) for raw RDB images.
///
class PresentationTimeStampGenerator {
public:
    ///
    /// \brief Setup the generator for PTS generation.
    /// \param inputFrameRate The target framerate of the input RDB image source.
    /// \param outputFrameRate The target framerate of the output video source.
    ///
    PresentationTimeStampGenerator(
        const AVRational& inputFrameRate
        , const AVRational& outputFrameRate);

    ///
    /// \brief Generate the PTS that would be best suited for this rdb image at
    /// this point in time.
    /// \param rdbImage The rdb image to generate a PTS for.
    /// \return The PTS with the timebase of the output framerate.
    ///
    int64_t generate(const RdbRawImage& rdbImage);

private:
    /// The target framerate of the input source (usually the IG)
    const AVRational& inputFrameRate_;

    /// The target framerate of the output stream
    const AVRational& outputFrameRate_;

    /// True if this is the first time a PTS is beeing generated
    bool isFirstFrame_;

    /// The frame id of the first frame that is passed to generate()
    int64_t firstSeenFrameId_;

    /// The id of the frame that was passed last to generate()
    int64_t lastSeenFrameId_;

    /// The number of skipped input frames. Avoids large pauses in the stream.
    int64_t numberOfSkippedFrames_;
};

} // namespace SharedMemoryStreaming
#endif
