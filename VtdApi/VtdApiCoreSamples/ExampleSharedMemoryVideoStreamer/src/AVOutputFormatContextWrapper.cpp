#include "AVOutputFormatContextWrapper.h"
#include "AVOutputFormatWrapper.h"
#include "StreamingOptions.h"
#include "AVCodecContextWrapper.h"
#include "AVStreamWrapper.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

#include "AVMacrosRedefined.h"

#include <stdexcept>
#include <sstream>

using namespace SharedMemoryStreaming;

AVOutputFormatContextWrapper::AVOutputFormatContextWrapper(
    AVOutputFormatWrapper &outputFormat
    , const StreamingOptions &options)
    : formatContextHandle_(NULL)
{
    // Try to create an output context that satisfies the desired format properties
    avformat_alloc_output_context2(
        &formatContextHandle_
        , outputFormat.getOutputFormatHandle()
        , options.outputShortname_.c_str()
        , options.outputFilename_.c_str());

    if (formatContextHandle_ == NULL)
    {
        throw std::runtime_error("Failed to allocate an output context.");
    }

    // Open the output file, if needed.
    if (!(outputFormat.getOutputFormatHandle()->flags & AVFMT_NOFILE))
    {
        const int errorCode = avio_open(
            &formatContextHandle_->pb
            , formatContextHandle_->filename
            , AVIO_FLAG_WRITE);
        if (errorCode < 0)
        {
            std::stringstream message;
            message << "Could not open '" << options.outputFilename_
                    << "': " << av_err2str(errorCode);
            throw std::runtime_error(message.str());
        }
    }
}

AVOutputFormatContextWrapper::~AVOutputFormatContextWrapper()
{
    if (!(formatContextHandle_->oformat->flags & AVFMT_NOFILE))
    {
        // Close the output file.
        avio_closep(&formatContextHandle_->pb);
    }

    // This free also cleans up the streams that where created for this context
    avformat_free_context(formatContextHandle_);
}

void AVOutputFormatContextWrapper::writeStreamHeader() const
{
    // Write the stream header, if any.
    const int errorCode =
        avformat_write_header(formatContextHandle_, NULL);
    if (errorCode < 0)
    {
        std::stringstream message;
        message << "Error occurred when opening output file: "
                << av_err2str(errorCode);
        throw std::runtime_error(message.str());
    }
}

bool AVOutputFormatContextWrapper::writeFrame(
    const AVCodecContextWrapper& codec
    , const AVStreamWrapper& stream
    , AVPacket& packet) const
{
    // Rescale output packet timestamp values from codec to stream timebase.
    av_packet_rescale_ts(
        &packet
        , codec.getCodecContextHandle()->time_base
        , stream.getStreamHandle()->time_base);
    packet.stream_index = stream.getStreamHandle()->index;

    // Write the compressed frame to the media file.
    const int errorCode = av_interleaved_write_frame(formatContextHandle_, &packet);

    if (errorCode < 0)
    {
        std::stringstream message;
        message << "Error writing packet: " << av_err2str(errorCode);
        throw std::runtime_error(message.str());
    }

    return true;
}
