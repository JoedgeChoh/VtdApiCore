#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H

#include "StreamingOptions.h"
#include "AVOutputFormatWrapper.h"
#include "AVOutputFormatContextWrapper.h"
#include "AVStreamWrapper.h"
#include "AVCodecContextWrapper.h"
#include "AVFrameWrapper.h"

namespace SharedMemoryStreaming {

///
/// \brief The class is responsible for creating the FFmpeg components
/// that are required for streaming. The class also writes a uncompressed
/// AVFrame to the output stream.
///
class OutputStream
{
public:
    ///
    /// \brief Create the FFmpeg components according to the passed options.
    /// \param options The settings to use for setting up FFmpeg.
    ///
    OutputStream(const StreamingOptions& options);

    virtual ~OutputStream();

    ///
    /// \brief Encode the AVFrame in frame_ with the choosen encoder
    /// and send the result to the output.
    ///
    void writeVideoFrame();

    /// getter
    /// \return a reference to the internal AVFrameWrapper class
    const AVFrameWrapper& getFrame() const { return frame_; }
    AVFrameWrapper& getFrame() { return frame_; }

private:
    /// A copy of the passed streaming options.
    StreamingOptions options_;

    /// The format the chosen output has
    AVOutputFormatWrapper outputFormat_;

    /// An instance of the chosen output format
    AVOutputFormatContextWrapper outputFormatContext_;

    /// The video stream where encoded AVFrames are send to.
    /// The stream is assigned to the created output context.
    AVStreamWrapper stream_;

    /// An encoder who creates encoded video frames.
    /// The encoder is chosen for the selected output format.
    AVCodecContextWrapper codecContext_;

    /// This AVFrame is used by writeVideoFrame() as the video source that
    /// is to be encoded. The user is responsible to fill this frame's
    /// entire WIDTH x HEIGHT with the pixel format the AVFrame is created with.
    /// This AVFrame's pixel format id must be identical to the one used to
    /// initialize the codec context with.
    AVFrameWrapper frame_;
};

} // namespace SharedMemoryStreaming
#endif
