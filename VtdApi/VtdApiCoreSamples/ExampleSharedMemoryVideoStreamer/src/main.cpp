#include "StreamingOptionsParser.h"
#include "RdbImageStreamer.h"
#include "AVFrameWrapper.h"
#include "AVOutputFormatWrapper.h"
#include "AVOutputFormatContextWrapper.h"
#include "AVCodecContextWrapper.h"
#include "AVStreamWrapper.h"
#include "AVCodecWrapper.h"
#include "OutputStream.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h>
}

#include "AVMacrosRedefined.h"

#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/chrono/system_clocks.hpp>

// Define timekeeping typedefs for berevity
typedef boost::chrono::system_clock system_clock;
typedef boost::chrono::system_clock::duration duration;
typedef boost::chrono::time_point<boost::chrono::system_clock> time_point;

// Constants
const duration pollingInterval = boost::chrono::milliseconds(1);

int main(int argc, char**argv)
{
    // Initialize libavformat and register all the muxers, demuxers and protocols
    av_register_all();
    // Register all codec
    avcodec_register_all();
    // Initialize network components
    avformat_network_init();

    // Parse the command line.
    SharedMemoryStreaming::StreamingOptions options =
        SharedMemoryStreaming::StreamingOptionsParser::parseOptions(argc, argv);

    // ////////////////////////////////////////////////////////////////////////
    // Setup the shared memory as the source of frames.
    boost::shared_ptr<SharedMemoryStreaming::AVFrameSource> frameSource(
        new SharedMemoryStreaming::RdbImageStreamer(options));
    // ////////////////////////////////////////////////////////////////////////

    SharedMemoryStreaming::OutputStream outputStream(options);

    system_clock clock;
    time_point frameStartTime = clock.now();
    time_point streamStartTime = frameStartTime;

    // Stop the stream after a certain amount of time
    for (; frameStartTime - streamStartTime < options.getStreamDuration();
         frameStartTime = clock.now())
    {
        // Try to get a new AVFrame from shared memory
        if (frameSource->getAvFrame(*outputStream.getFrame().getFrameHandle()))
        {
            outputStream.writeVideoFrame();
        }
        else
        {
            // Do a simple busy wait for this example.
            boost::this_thread::sleep_for(pollingInterval);
        }
    }

    return 0;
}
