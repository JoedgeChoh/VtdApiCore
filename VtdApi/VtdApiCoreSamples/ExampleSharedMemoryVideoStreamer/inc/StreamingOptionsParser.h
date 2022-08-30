#ifndef STREAMINGOPTIONSPARSER_H
#define STREAMINGOPTIONSPARSER_H

#include "StreamingOptions.h"

namespace SharedMemoryStreaming {

///
/// \brief Class for parsing arguments from the command line, for the shared memory streaming.
///
class StreamingOptionsParser {
public:
    ///
    /// \brief Parses the command line arguments and creates a struct containing the results.
    /// \param argc
    /// \param argv
    /// \return The parsed options.
    ///
    static StreamingOptions parseOptions(
        const int argc
        , const char* const* const argv);
};

} // namespace SharedMemoryStreaming
#endif
