#include "RdbImageToAVFrameConverter.h"
#include "RdbRawImage.h"

#include <VtdCore/Logging/Log.h>

#include <stdexcept>
#include <sstream>
#include <boost/cast.hpp>

extern "C" {
#include <libavutil/frame.h>
}

using namespace SharedMemoryStreaming;

namespace {

void convertRGB8ToRGB0(
    const unsigned char* rdbImageData
    , AVFrame & avImage)
{
    // Offset for the current row of the source image
    size_t sourceRowOffset = 0;

    size_t targetRowOffset = avImage.linesize[0] * (avImage.height - 1);
    for (int y = 0; y < avImage.height;
         ++y
         , sourceRowOffset += 3 * avImage.width
         , targetRowOffset -= avImage.linesize[0])
    {
        size_t sourceOffset = sourceRowOffset;
        size_t targetOffset = targetRowOffset;
        for (int x = 0; x < avImage.width;
             ++x
             , sourceOffset += 3
             , targetOffset += 4)
        {
            avImage.data[0][targetOffset + 0] =
                boost::numeric_cast<uint8_t>(rdbImageData[sourceOffset + 0]);
            avImage.data[0][targetOffset + 1] =
                boost::numeric_cast<uint8_t>(rdbImageData[sourceOffset + 1]);
            avImage.data[0][targetOffset + 2] =
                boost::numeric_cast<uint8_t>(rdbImageData[sourceOffset + 2]);
            avImage.data[0][targetOffset + 3] = 0;
        }
    }
}

} // namespace {

bool RdbImageToAVFrameConverter::convert(
    const SharedMemoryStreaming::RdbRawImage &rdbImage
    , AVFrame& avImage)
{
    // /////////////////////////////////////////////////////////////////////////
    // Perform error checks
    if (rdbImage.imageHeader.width <= 0 || avImage.width <= 0 ||
        rdbImage.imageHeader.height <= 0 || avImage.height <= 0)
    {
        throw std::runtime_error(
                  "The dimensions of the rdbimage and avframe, must be positive.");
    }

    if (rdbImage.imageHeader.width != avImage.width ||
        rdbImage.imageHeader.height != avImage.height)
    {
        throw std::runtime_error("Resolution mismatch for rdbimage and avframe.");
    }

    if (rdbImage.imageHeader.imgSize > rdbImage.imageData.size())
    {
        throw std::runtime_error(
                  "The rdb imagedata buffer is smaller than the "
                  "declared size in the header.");
    }

    if (!av_frame_is_writable(&avImage))
    {
        throw std::runtime_error(
                  "The avframe can not be filled with image data "
                  "from an rdb image, since avframe is not writable.");
    }

    if (avImage.format == -1)
    {
        throw std::runtime_error("The avframe format is unknown or unset.");
    }

    // /////////////////////////////////////////////////////////////////////////
    // Get a pointer to the sorce data
    const unsigned char* rdbImageData =
        reinterpret_cast<const unsigned char*>(rdbImage.imageData.data());

    // /////////////////////////////////////////////////////////////////////////
    // Choose the fitting copy algorithm for a specific source and target format.

    if (rdbImage.imageHeader.pixelFormat == RDB_PIX_FORMAT_RGB8 &&
        avImage.format == AV_PIX_FMT_RGB0)
    {
        convertRGB8ToRGB0(rdbImageData, avImage);
    }
    else
    {
        std::stringstream message;
        message << "The conversion combination for rdbImage.pixelformat="
                << (int)rdbImage.imageHeader.pixelFormat
                << "and avframe.format="
                << (int)avImage.format
                << ", is not supported.";
        VTD_LOG_ERR(message.str());
        throw std::runtime_error(message.str());
    }

    return true;
}
