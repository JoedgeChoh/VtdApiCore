#include "AVFrameWrapper.h"

extern "C" {
#include <libavutil/frame.h>
}

#include <stdexcept>

using namespace SharedMemoryStreaming;

AVFrameWrapper::AVFrameWrapper(
    const int avFrameFormat
    , const int width
    , const int height)
{
    initAVFrame(avFrameFormat, width, height);
}

AVFrameWrapper::~AVFrameWrapper()
{
    av_frame_free(&frameHandle_);
}

void AVFrameWrapper::initAVFrame(
    const int avFrameFormat
    , const int width
    , const int height)
{
    frameHandle_ = av_frame_alloc();
    if (frameHandle_ == NULL)
    {
        throw std::runtime_error("Failed to allocate an AVFrame.");
    }

    frameHandle_->format = avFrameFormat;
    frameHandle_->width = width;
    frameHandle_->height = height;

    {
        int err = av_frame_get_buffer(frameHandle_, 0);
        if (err < 0)
        {
            throw std::runtime_error("Could not allocate buffers for frame.");
        }
    }
}
