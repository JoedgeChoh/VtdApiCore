#ifndef AVSTREAMWRAPPER_H
#define AVSTREAMWRAPPER_H

struct AVStream;

namespace SharedMemoryStreaming {

class AVOutputFormatContextWrapper;
class StreamingOptions;

///
/// \brief Class manages the creation of an AVStream.
///
class AVStreamWrapper {
public:
    ///
    /// \brief Add a stream to the output context. The output context is responsible
    /// for freeing the stream.
    /// \param outputFormatContext The context where the sream will be assigned to.
    /// \param options The options where the stream gets required properties from.
    ///
    AVStreamWrapper(
        AVOutputFormatContextWrapper& outputFormatContext
        , const StreamingOptions& options);

    virtual ~AVStreamWrapper() { }

    ///
    /// \brief Getter for the wrapped AVStream.
    /// \return The wrapped AVStream.
    ///
    const AVStream* getStreamHandle() const
    {
        return streamHandle_;
    }

private:
    /// The managed AVStream
    AVStream* streamHandle_;
};

} // namespace SharedmemoryStreaming
#endif
