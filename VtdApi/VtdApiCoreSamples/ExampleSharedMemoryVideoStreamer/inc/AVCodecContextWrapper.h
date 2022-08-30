#ifndef AVCODECCONTEXTWRAPPER_H
#define AVCODECCONTEXTWRAPPER_H

struct AVCodecContext;

namespace SharedMemoryStreaming {

class StreamingOptions;
class AVOutputFormatWrapper;

///
/// \brief Class handles the creation/setup/destruction of an AVCodecContext
///
class AVCodecContextWrapper {
public:
    ///
    /// \brief Create a codec for a given output format and command line options.
    ///
    AVCodecContextWrapper(
        const AVOutputFormatWrapper& outputFormat
        , const StreamingOptions& options);

    /// Close the codex context
    virtual ~AVCodecContextWrapper();

    ///
    /// \brief Get the wrapped AVCodecContext
    /// \return The wrapped AVCodecContext
    ///
    AVCodecContext* getCodecContextHandle()
    {
        return codecContextHandle_;
    }

    ///
    /// \brief Get the wrapped AVCodecContext
    /// \return The wrapped AVCodecContext
    ///
    const AVCodecContext* getCodecContextHandle() const
    {
        return codecContextHandle_;
    }

private:
    /// This AVCodecContext is managed by this class
    AVCodecContext* codecContextHandle_;
};

} // namespace SharedMemoryStreaming
#endif
