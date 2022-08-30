#ifndef STREAMINGOPTIONS_H
#define STREAMINGOPTIONS_H

extern "C" {
#include <libavcodec/avcodec.h>
}

#include <string>

#include <boost/chrono/duration.hpp>

#include <VtdCore/Macros.h>

struct AVDictionary;

namespace SharedMemoryStreaming {

///
/// \brief Describes the resolution of a video stream.
///
struct Resolution
{
    /// Width of the resolution.
    int width;

    /// Height of the resolution.
    int height;
};

///
/// \brief Class that holds the options to setup the properties of a stream.
///
class StreamingOptions
    /// \cond
        VTD_FINAL
    /// \endcond
{
public:
    StreamingOptions();

    ///
    /// \brief Copy constructor.
    /// \param other
    ///
    StreamingOptions(const StreamingOptions &other);

    ~StreamingOptions();

    ///
    /// \brief Get the desired duration of the stream.
    /// \return The stream duration in seconds. Max duration for infinite streams.
    ///
    boost::chrono::duration<double> getStreamDuration() const;

    /// Name of the output format the stream should have.
    std::string outputShortname_;

    /// The URL where the stream should be directed to.
    std::string outputFilename_;

    /// The mime type the stream should have.
    std::string outputMimeType_;

    /// The duration of the stream in seconds.
    double streamDuration_;

    /// The target framerate of the video source.
    AVRational inputFrameRate_;

    /// The target framerate of the video stream.
    AVRational outputFrameRate_;

    /// The pixel format the video encoder should expect for the source images.
    /// It is recommended that the pixel format of the RDB images in SHM is easily
    /// convertible into the choosen pixel format.
    /// This avoids excessive colorspace conversions.
    AVPixelFormat streamPixelFormatId_;

    /// The id of the video codec that should be used for encoding.
    /// If none if specified, FFmpeg chooses one automatically.
    AVCodecID videoCodecId_;

    /// Dictionary to hold codec private information.
    AVDictionary* avDictionary_;

    /// The desired bitrate of the stream.
    int64_t bitRate_;

    /// The key of the shared memory. to read from.
    int sharedMemoryKey_;

    /// The resolution of the created video stream.
    /// It is recomended to choose the same resolution as the IG, to avoid rescaling
    /// the source frames.
    Resolution outputResolution_;
};

} // namespace SharedMemoryStreaming
#endif
