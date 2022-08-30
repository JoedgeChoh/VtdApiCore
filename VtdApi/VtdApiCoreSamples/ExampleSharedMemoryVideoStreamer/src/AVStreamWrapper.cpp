#include "AVStreamWrapper.h"
#include "StreamingOptions.h"
#include "AVOutputFormatContextWrapper.h"

extern "C" {
#include <libavformat/avformat.h>
}

#include <stdexcept>

using namespace SharedMemoryStreaming;

AVStreamWrapper::AVStreamWrapper(
    AVOutputFormatContextWrapper &outputFormatContext
    , const StreamingOptions &options)
{
    streamHandle_ = avformat_new_stream(
        outputFormatContext.getFormatContextHandle(), NULL);
    if (streamHandle_ == NULL)
    {
        throw std::runtime_error("Could not allocate stream.");
    }

    // Assign this stream the newly created ID
    streamHandle_->id =
        outputFormatContext.getFormatContextHandle()->nb_streams - 1;
    // Since this example only has one stream, set the timebase to 1/FPS
    streamHandle_->time_base = av_inv_q(options.outputFrameRate_);
}
