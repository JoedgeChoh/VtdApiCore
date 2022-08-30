#include "AVOutputFormatWrapper.h"

#include "StreamingOptions.h"

#include <sstream>
#include <stdexcept>

using namespace SharedMemoryStreaming;

namespace {

///
/// \brief Create an output format according to the streaming options.
/// \param options The options to use.
/// \return The created output format.
///
AVOutputFormat getOutputFormat(const StreamingOptions& options)
{
    // Make an initial guess for the output format
    const AVOutputFormat* guessedFormat = av_guess_format(
        options.outputShortname_.c_str()
        , options.outputFilename_.c_str()
        , options.outputMimeType_.c_str());

    if (guessedFormat == NULL)
    {
        std::stringstream ss;
        ss << "Failed to guess the output format with av_guess_format("
           << "shortname = \"" << options.outputShortname_ << "\", "
           << "filename = \"" << options.outputFilename_ << "\", "
           << "mimeType = \"" << options.outputMimeType_ << "\""
           << ")" << std::endl;
        throw std::runtime_error(ss.str());
    }

    // Create a copy of this format so that additional changes to this struct,
    // do not affect the default values for this output format.
    AVOutputFormat outputFormatCopy = *guessedFormat;

    // Assign codec id if parsed from options.
    // This allows to choose a video codec that differs from the default
    // the output format suggests.
    if (options.videoCodecId_ != AV_CODEC_ID_NONE)
    {
        outputFormatCopy.video_codec = options.videoCodecId_;
    }

    return outputFormatCopy;
}

} // namespace {

AVOutputFormatWrapper::AVOutputFormatWrapper(const StreamingOptions &options)
    : outputFormat_(getOutputFormat(options))
{
}

