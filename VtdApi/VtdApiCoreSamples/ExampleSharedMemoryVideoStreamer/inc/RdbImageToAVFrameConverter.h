#ifndef RDBIMAGETOAVFRAMECONVERTER_H
#define RDBIMAGETOAVFRAMECONVERTER_H

struct AVFrame;

namespace SharedMemoryStreaming {

class RdbRawImage;

///
/// \brief Class for converting raw RDB images to AVFrames.
///
class RdbImageToAVFrameConverter
{
public:
    ///
    /// \brief Convert a RDB image into an AVFrame, for processing by libav*.
    /// \param rdbImage The RDB source image.
    /// \param avImage The AVFrame target image.
    /// \return True if a conversion was successful.
    ///
    static bool convert(const RdbRawImage& rdbImage, AVFrame& avImage);
};

} // namespace SharedMemoryStreaming
#endif
