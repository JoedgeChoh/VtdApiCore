#ifndef AVOUTPUTFORMATWRAPPER_H
#define AVOUTPUTFORMATWRAPPER_H

extern "C" {
#include <libavformat/avformat.h>
}

namespace SharedMemoryStreaming {

class StreamingOptions;

///
/// \brief This class creates an output format from output options of the stream.
///
class AVOutputFormatWrapper {
public:
    ///
    /// \brief Create an output format from the output options.
    /// \param options The set of options to use.
    ///
    AVOutputFormatWrapper(const StreamingOptions& options);

    ///
    /// \brief Getter for the created output format.
    /// This non const version exist because avformat_alloc_output_context2
    /// does not accept a non const AVOutputFormat. This changed in newer versions
    /// of FFmpeg.
    /// \return The created output format.
    ///
    AVOutputFormat* getOutputFormatHandle()
    {
        return &outputFormat_;
    }

    ///
    /// \brief Getter for the created output format.
    /// \return The created output format.
    ///
    const AVOutputFormat* getOutputFormatHandle() const
    {
        return &outputFormat_;
    }

private:
    /// The output format created from the streaming options.
    AVOutputFormat outputFormat_;
};

} // namespace SharedMemoryStreaming
#endif
