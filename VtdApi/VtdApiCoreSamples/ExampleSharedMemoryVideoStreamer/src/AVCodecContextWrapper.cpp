#include "AVCodecContextWrapper.h"
#include "StreamingOptions.h"
#include "AVCodecWrapper.h"
#include "AVOutputFormatWrapper.h"
#include "AVMacrosRedefined.h"

#include <stdexcept>
#include <sstream>

using namespace SharedMemoryStreaming;

AVCodecContextWrapper::AVCodecContextWrapper(
    const AVOutputFormatWrapper &outputFormat
    , const StreamingOptions& options)
{
    // Search the codec with the desired ID
    const AVCodecWrapper codec(outputFormat.getOutputFormatHandle()->video_codec);

    // Allocate a context
    codecContextHandle_ = avcodec_alloc_context3(codec.getCodecHandle());

    if (codecContextHandle_ == NULL)
    {
        throw std::runtime_error("Could not alloc an encoding context.");
    }

    // Since this is a video streaming example
    // a video codec is required.
    switch (codec.getCodecHandle()->type)
    {
        case AVMEDIA_TYPE_VIDEO:
        {
            // Initialize properties of the video stream
            codecContextHandle_->codec_id = codec.getCodecHandle()->id;
            codecContextHandle_->bit_rate = options.bitRate_;
            codecContextHandle_->width = options.outputResolution_.width;
            codecContextHandle_->height = options.outputResolution_.height;
            // time_base is the time between frames <=> inverse of framerate
            codecContextHandle_->time_base = av_inv_q(options.outputFrameRate_);
            // Set the format of the pixels the encoder should use.
            // Note that the set of supported pixel formats, varies between
            // different encoders.
            // For example most video encoders support YUV pixel formats,
            // but only some accept RGB pixels.
            codecContextHandle_->pix_fmt = options.streamPixelFormatId_;
        }
        break;
        default:
        {
            std::stringstream message;
            message << "The codec of type " << codec.getCodecHandle()->type
                    << " is unknown.";
            throw std::runtime_error(message.str());
        }
        break;
    }

    // Some formats want stream headers to be separate
    if (outputFormat.getOutputFormatHandle()->flags & AVFMT_GLOBALHEADER)
    {
        codecContextHandle_->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }

    // Open the codec using the parsed dictionary entries
    {
        AVDictionary* opt = NULL;
        av_dict_copy(&opt, options.avDictionary_, 0);

        const int errorCode = avcodec_open2(
            codecContextHandle_
            , codec.getCodecHandle()
            , &opt);
        av_dict_free(&opt);
        if (errorCode < 0)
        {
            std::stringstream message;
            message << "Could not open video codec: " << av_err2str(errorCode);
            throw std::runtime_error(message.str());
        }
    }
}

AVCodecContextWrapper::~AVCodecContextWrapper()
{
    avcodec_close(codecContextHandle_);
}
