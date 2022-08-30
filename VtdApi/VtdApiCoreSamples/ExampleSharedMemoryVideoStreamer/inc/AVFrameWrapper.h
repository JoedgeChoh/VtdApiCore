#ifndef AVFRAMEWRAPPER_H
#define AVFRAMEWRAPPER_H

struct AVFrame;

namespace SharedMemoryStreaming {

///
/// \brief Class wraps the AVFrame struct for automatic allocation and destruction.
///
class AVFrameWrapper {
public:
    ///
    /// \brief Create an AVFrame with specified properties.
    /// \param avFrameFormat Must be one of AVPixelFormat.
    /// \param width
    /// \param height
    ///
    AVFrameWrapper(
        const int avFrameFormat
        , const int width
        , const int height);

    virtual ~AVFrameWrapper();

    ///
    /// \brief Getter for the managed AVFrame
    /// \return The managed AVFrame
    ///
    const AVFrame* getFrameHandle() const { return frameHandle_; }

    AVFrame* getFrameHandle() { return frameHandle_; }


private:
    ///
    /// \brief Allocate an AVFrame, set essential properties and get a buffer.
    /// \param avFrameFormat The pixelformat the AVFrame should have.
    /// \param width
    /// \param height
    ///
    void initAVFrame(
        const int avFrameFormat
        , const int width
        , const int height);

    /// Handle to the AVFrame.
    AVFrame* frameHandle_;
};

} // namespace SharedMemoryStreaming
#endif
