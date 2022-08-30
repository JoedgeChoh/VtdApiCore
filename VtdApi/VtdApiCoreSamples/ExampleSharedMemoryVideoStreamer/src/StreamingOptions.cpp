#include "StreamingOptions.h"

using namespace SharedMemoryStreaming;

StreamingOptions::StreamingOptions()
    : avDictionary_(NULL)
{
    av_dict_set(&avDictionary_, NULL, NULL, 0);
}

StreamingOptions::StreamingOptions(
    const StreamingOptions &other)
    : avDictionary_(NULL)
{
    outputFilename_ = other.outputFilename_;
    outputShortname_ = other.outputShortname_;
    outputMimeType_ = other.outputMimeType_;
    streamDuration_ = other.streamDuration_;
    inputFrameRate_ = other.inputFrameRate_;
    outputFrameRate_ = other.outputFrameRate_;
    streamPixelFormatId_ = other.streamPixelFormatId_;
    videoCodecId_ = other.videoCodecId_;
    bitRate_ = other.bitRate_;
    sharedMemoryKey_ = other.sharedMemoryKey_;
    outputResolution_ = other.outputResolution_;
    av_dict_copy(&avDictionary_, other.avDictionary_, 0);
}

StreamingOptions::~StreamingOptions()
{
    if (avDictionary_ != NULL)
    {
        av_dict_free(&avDictionary_);
    }
}

boost::chrono::duration<double>
StreamingOptions::getStreamDuration() const
{
    if (streamDuration_ <= 0.0)
    {
        return boost::chrono::duration<double>::max();
    }
    else
    {
        return boost::chrono::duration<double>(streamDuration_);
    }
}

