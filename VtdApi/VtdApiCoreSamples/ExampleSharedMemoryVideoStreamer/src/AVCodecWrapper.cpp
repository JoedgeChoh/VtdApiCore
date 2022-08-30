#include "AVCodecWrapper.h"

#include <sstream>
#include <stdexcept>

using namespace SharedMemoryStreaming;

AVCodecWrapper::AVCodecWrapper(const AVCodecID &codecId)
    : codecHandle_(avcodec_find_encoder(codecId))
{
    if (codecHandle_ == NULL)
    {
        std::stringstream message;
        message << "Could not find encoder for '"
                << avcodec_get_name(codecId) << "'";
        throw std::runtime_error(message.str());
    }
}
