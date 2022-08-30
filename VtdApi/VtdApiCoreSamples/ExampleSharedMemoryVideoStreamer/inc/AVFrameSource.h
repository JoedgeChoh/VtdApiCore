#ifndef AVFRAMESOURCE_H
#define AVFRAMESOURCE_H

struct AVFrame;

namespace SharedMemoryStreaming {

///
/// \brief Interface class for defining a source of AVFrames.
///
class AVFrameSource {
public:

    ///
    /// \brief Fill a frame with data from the video source.
    /// \param pict The variable where the new frame data will be stored.
    /// \return True if the source had new frame data and the data was stored.
    ///
    virtual bool getAvFrame(AVFrame& pict) = 0;
};

} // namespace SharedMemoryStreaming
#endif
