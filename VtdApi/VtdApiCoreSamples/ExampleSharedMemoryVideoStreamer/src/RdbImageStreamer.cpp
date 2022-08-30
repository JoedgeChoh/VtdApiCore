#include "RdbImageStreamer.h"
#include "RdbImageReader.h"
#include "RdbImageToAVFrameConverter.h"

extern "C" {
#include <libswscale/swscale.h>
}

#include <iostream>
#include <stdexcept>
#include <boost/make_shared.hpp>

using namespace SharedMemoryStreaming;

RdbImageStreamer::RdbImageStreamer(
    const StreamingOptions& streamingOptions)
    : streamingOptions_(streamingOptions)
    , rdbImageReader_(streamingOptions.sharedMemoryKey_)
    , originalRdbFrame_(new RdbRawImage)
    , minimalAcceptablePresentationTimeStamp_(0)
    , presentationTimeStampGenerator_(
        streamingOptions.inputFrameRate_, streamingOptions.outputFrameRate_)
{
}

RdbImageStreamer::~RdbImageStreamer()
{
}

bool RdbImageStreamer::getAvFrame(
    AVFrame& encoderFrame)
{
    if (!rdbImageReader_.read(originalRdbFrame_))
    {
        return false;
    }

    // None is available, no new frame to encode.
    if (originalRdbFrame_ == NULL)
    {
        return false;
    }

    // Generate a PTS for this RDB frame.
    const int64_t rdbFramePresentationTimeStamp =
        presentationTimeStampGenerator_.generate(*originalRdbFrame_);

    std::cout << "Read from SHM imageHeader.id=" << originalRdbFrame_->imageHeader.id << ", "
              << "generated pts=" << rdbFramePresentationTimeStamp << " for this id"
              << std::endl;

    // If the generated PTS would be not strictly increasing, ignore the frame.
    if (rdbFramePresentationTimeStamp < minimalAcceptablePresentationTimeStamp_)
    {
        return false;
    }

    // Return the generated PTS.
    encoderFrame.pts = rdbFramePresentationTimeStamp;
    encoderFrame.pkt_duration = rdbFramePresentationTimeStamp - minimalAcceptablePresentationTimeStamp_ + 1;

    // The next PTS must be larger than the current one.
    minimalAcceptablePresentationTimeStamp_ = rdbFramePresentationTimeStamp + 1;

    // Create the converter AVFrame, if it has not been created.
    if (convertedAVFrame_ == NULL)
    {
        convertedAVFrame_ = boost::make_shared<AVFrameWrapper>(
            AV_PIX_FMT_RGB0
            , originalRdbFrame_->imageHeader.width
            , originalRdbFrame_->imageHeader.height);
    }

    // Copy the frame to an AVFrame.
    // Also convert slightly differing pixel formats.
    AVFrame* convertedAVFrameHandle = convertedAVFrame_->getFrameHandle();
    assert(originalRdbFrame_ != NULL);
    assert(convertedAVFrameHandle != NULL);
    if (!RdbImageToAVFrameConverter::convert(*originalRdbFrame_, *convertedAVFrameHandle))
    {
        throw std::runtime_error("Failed to convert a rdb image to an avframe.");
    }

    // Allocate an SWS context for handling downscaling and conversion
    // between very different pixelformats.
    SwsContext* conversionContext = sws_getContext(
            convertedAVFrameHandle->width
        , convertedAVFrameHandle->height
        , AVPixelFormat(convertedAVFrameHandle->format)
        , encoderFrame.width
        , encoderFrame.height
        , AVPixelFormat(encoderFrame.format)
        , SWS_FAST_BILINEAR, NULL, NULL, NULL);

    // Scale the frame.
    // This conversion can be costly if the pixel format are very differing.
    // The RDB image should have the same format as the encoderFrame.
    sws_scale(
        conversionContext
        , convertedAVFrameHandle->data
        , convertedAVFrameHandle->linesize
        , 0
        , convertedAVFrameHandle->height
        , encoderFrame.data
        , encoderFrame.linesize);

    sws_freeContext(conversionContext);

    // The AVFrame passed to this function, is now ready to be encoded.
    return true;
}
