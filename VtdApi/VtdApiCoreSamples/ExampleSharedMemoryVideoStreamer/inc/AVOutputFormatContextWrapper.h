#ifndef AVOUTPUTFORMATCONTEXTWRAPPER_H
#define AVOUTPUTFORMATCONTEXTWRAPPER_H

struct AVFormatContext;
struct AVPacket;

namespace SharedMemoryStreaming {

class AVCodecContextWrapper;
class StreamingOptions;
class AVOutputFormatWrapper;
class AVStreamWrapper;

///
/// \brief This class manages the creation/init/destruction of an AVFromatContext.
/// For example when writing to a video file, this class creates the file, writes
/// the stream header and finalizes the header when the stream ends.
/// Or this class handles an RTSP connection to a streaming server.
///
class AVOutputFormatContextWrapper {
public:
    ///
    /// \brief Create an output context with a specified format.
    /// \param outputFormat The format the output context should have.
    /// \param options Additional options to create the context with.
    ///
    AVOutputFormatContextWrapper(
        AVOutputFormatWrapper& outputFormat
        , const StreamingOptions& options);

    virtual ~AVOutputFormatContextWrapper();

    ///
    /// \brief Write basic stream information to the output.
    ///
    void writeStreamHeader() const;

    ///
    /// \brief Write an encoded packet to a stream.
    /// Since the stream belongs to an output context, writing the packet results
    /// in sending data to a file or other consumer.
    /// \param codec The the codec who created the packet.
    /// \param stream The stream where to write the packet to.
    /// \param packet The packet to write.
    /// \return True if write was succesfull.
    ///
    bool writeFrame(
        const AVCodecContextWrapper& codec
        , const AVStreamWrapper& stream
        , AVPacket& packet) const;

    ///
    /// \brief Getter for the managed format context.
    /// \return The managed format context.
    ///
    const AVFormatContext* getFormatContextHandle() const { return formatContextHandle_; }
    AVFormatContext* getFormatContextHandle() { return formatContextHandle_; }

private:
    /// The output context of the specified output format.
    AVFormatContext* formatContextHandle_;
};

} // namespace SharedMemoryStreaming
#endif
