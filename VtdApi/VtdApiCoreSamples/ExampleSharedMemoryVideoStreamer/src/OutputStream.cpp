#include "OutputStream.h"
#include "AVCodecWrapper.h"

#include "AVMacrosRedefined.h"

#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace SharedMemoryStreaming;

OutputStream::OutputStream(
    const SharedMemoryStreaming::StreamingOptions& options)
    : options_(options)
    , outputFormat_(options_)
    , outputFormatContext_(outputFormat_, options_)
    , stream_(outputFormatContext_, options_)
    , codecContext_(outputFormat_, options_)
    , frame_(codecContext_.getCodecContextHandle()->pix_fmt
             , codecContext_.getCodecContextHandle()->width
             , codecContext_.getCodecContextHandle()->height)
{
    AVDictionary* opt = NULL;

    av_dict_copy(&opt, options_.avDictionary_, 0);

    // copy the stream parameters to the muxer
    {
        const int errorCode = avcodec_parameters_from_context(
            stream_.getStreamHandle()->codecpar
            , codecContext_.getCodecContextHandle());
        if (errorCode < 0)
        {
            throw  std::runtime_error("Could not copy the stream parameters.");
        }
    }

    // Write basic properties of the output context to console.
    av_dump_format(
        outputFormatContext_.getFormatContextHandle()
        , 0
        , outputFormatContext_.getFormatContextHandle()->filename
        , 1);

    outputFormatContext_.writeStreamHeader();
}

OutputStream::~OutputStream()
{
    // Write the trailer, if any. The trailer must be written before you
    // close the CodecContexts when you wrote the header; otherwise
    // av_write_trailer() may try to use memory that was freed on
    // avcodec_close().
    av_write_trailer(outputFormatContext_.getFormatContextHandle());
}

void OutputStream::writeVideoFrame()
{
    AVPacket paket;
    // The size and data members have to be set explicit
    paket.size = 0;
    paket.data = NULL;

    av_init_packet(&paket);

    // Encode the frame
    int retValue = avcodec_send_frame(codecContext_.getCodecContextHandle(), frame_.getFrameHandle());
    if ( retValue < 0 ) {
        std::stringstream message;
        message << "Error encoding video frame: " <<  av_err2str(retValue);
        throw std::runtime_error(message.str());
    }

    while ( retValue == 0 ) {
        retValue = avcodec_receive_packet(codecContext_.getCodecContextHandle(), &paket);
        if ( retValue == 0 ) {
            // Success. Can continue.
        } else if ( retValue == AVERROR(EAGAIN) ) {
            std::cout << "AVERROR(EAGAIN): The encoder does not have any output ready yet in its current state. User must provide more input." << std::endl;
            break;
        } else if ( retValue == AVERROR_EOF ) {
            std::cout << "AVERROR_EOF: The encoder has been fully flushed, and there will be no more output packets." << std::endl;
            break;
        } else if ( retValue == AVERROR(EINVAL) ) {
            std::cout << "AVERROR(EINVAL): Codec not opened, or it is an encoder." << std::endl;
            break;
        } else {
            std::stringstream message;
            message << "Encoding error: " << av_err2str(AVERROR(retValue));
            throw std::runtime_error(message.str());
        }

        // If the encoding created a package, write it to the output
        paket.duration = frame_.getFrameHandle()->pkt_duration;
        outputFormatContext_.writeFrame(codecContext_, stream_, paket);

        av_packet_unref(&paket);
    }
}
