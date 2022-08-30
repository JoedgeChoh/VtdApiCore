#include "StreamingOptionsParser.h"

#include "ExampleSharedMemoryVideoStreamer/Version.h"

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <iostream>

extern "C" {
#include <libavutil/pixdesc.h>
}

#include <VtdToolkit/viRDBIcd.h>

namespace po = boost::program_options;

///
/// \brief Check if the commandline option value is a valid AVRational
/// \param v The parsed AVRational is returned here.
/// \param values The list of strings to be parsed as an AVRational.
///
void validate(
    boost::any& v
    , const std::vector<std::string>& values
    , AVRational*, int)
{
    AVRational parsedRational;
    std::vector<int> tokens;
    for (std::vector<std::string>::const_iterator it = values.begin();
         it != values.end();
         ++it)
    {
        std::stringstream ss(*it);
        std::copy(std::istream_iterator<int>(ss), std::istream_iterator<int>()
                  , std::back_inserter(tokens));
        if (!ss.eof())
        {
            throw po::invalid_option_value("Invalid framerate specification.");
        }
    }
    if (tokens.size() != 2)
    {
        throw po::invalid_option_value("Invalid framerate specification.");
    }
    parsedRational.num = tokens[0];
    parsedRational.den = tokens[1];
    v = parsedRational;
}

///
/// \brief Allows outputing an AVRational to a stream.
/// Used for commandline handling with boost.
/// \param os The stream to output the AVRational to.
/// \param rational The AVRational to output.
/// \return The used stream.
///
std::ostream& operator<<(std::ostream& os, const AVRational& rational)
{
    os << rational.num << " " << rational.den;
    return os;
}

namespace {

///
/// \brief Convert the string name of the desired encoder pixel input format, into an ID.
/// \param options The converted ID ist stored here.
/// \param streamPixelFormatName The name of the pixel format.
///
void initializePixelFormatId(
    SharedMemoryStreaming::StreamingOptions& options
    , const std::string& streamPixelFormatName)
{
    options.streamPixelFormatId_ =
        av_get_pix_fmt(streamPixelFormatName.c_str());
    if (!streamPixelFormatName.empty() &&
        options.streamPixelFormatId_ == AV_PIX_FMT_NONE)
    {
        throw std::runtime_error(
                  "The pixel format of name \"" +
                  streamPixelFormatName + "\" is not known by ffmpeg.");
    }
}

///
/// \brief Convert the string name of the desired codec name, into an ID.
/// \param options The ID of the codec is stored here.
/// \param videoCodecName The name of the codec to search.
///
void initializeVideoCodecId(
    SharedMemoryStreaming::StreamingOptions& options
    , const std::string& videoCodecName)
{
    options.videoCodecId_ = AV_CODEC_ID_NONE;
    if (!videoCodecName.empty())
    {
        AVCodec* encoder = avcodec_find_encoder_by_name(videoCodecName.c_str());
        if (encoder == NULL)
        {
            throw std::runtime_error(
                      "The encoder with name \"" +
                      videoCodecName + "\" is not known by ffmpeg.");
        }
        options.videoCodecId_ = encoder->id;
    }
}

///
/// \brief Parse ffmpeg specific flags and store them in a dictionary.
/// \param options The streaming options with the dictionary.
/// \param tokens The list of tokens to initialize the dictionary with.
///
void initializeAvDictionary(
    SharedMemoryStreaming::StreamingOptions &options
    , const std::vector<std::string> &tokens)
{
    typedef boost::char_separator<char> char_separator;
    char_separator separator("=");

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        boost::tokenizer<char_separator> tokenizedKeyValues(tokens[i], separator);

        // Search the key
        boost::tokenizer<char_separator>::iterator keyValueIterator =
            tokenizedKeyValues.begin();
        if (keyValueIterator == tokenizedKeyValues.end())
        {
            throw std::runtime_error(
                      "The token \"" + tokens[i] +
                      "\" does not contain a valid key value pair.");
        }
        const std::string key = *keyValueIterator;

        // Search the value
        ++keyValueIterator;
        if (keyValueIterator == tokenizedKeyValues.end())
        {
            throw std::runtime_error(
                      "The token \"" + tokens[i] +
                      "\" does not contain a value for the key \"" + key + "\".");
        }
        const std::string value = *keyValueIterator;

        // Assert that only key and value are present
        ++keyValueIterator;
        if (keyValueIterator != tokenizedKeyValues.end())
        {
            throw std::runtime_error(
                      "The token \"" + tokens[i] +
                      "\" does contain more than two entries. "
                      "Ony a key and a value are required.");
        }

        const int setDictionaryResult =
            av_dict_set(&options.avDictionary_, key.c_str(), value.c_str(), 0);
        if (setDictionaryResult < 0)
        {
            throw std::runtime_error(
                      "Failed to a dictionary entry with key=value: " +
                      key + "=" + value + ".");
        }
    }
}

} // namespace {

namespace SharedMemoryStreaming {

void validate(boost::any& v
              , const std::vector<std::string>& values
              , SharedMemoryStreaming::Resolution*, int)
{
    SharedMemoryStreaming::Resolution parsedResolution;
    std::vector<int> tokens;
    for (std::vector<std::string>::const_iterator it = values.begin();
         it != values.end();
         ++it)
    {
        std::stringstream ss(*it);
        std::copy(std::istream_iterator<int>(ss), std::istream_iterator<int>()
                  , std::back_inserter(tokens));
        if (!ss.eof())
        {
            throw po::invalid_option_value("Invalid resolution specification.");
        }
    }
    if (tokens.size() != 2)
    {
        throw po::invalid_option_value("Invalid resolution specification.");
    }
    parsedResolution.width = tokens[0];
    parsedResolution.height = tokens[1];
    v = parsedResolution;
}

StreamingOptions StreamingOptionsParser::parseOptions(
    const int argc, const char* const* const argv)
{
    StreamingOptions options;

    po::options_description desc(
        "This program reads frame data from shared memory, that has previously been "
        "written by the IG. Then the read uncompressed video stream is encoded and "
        "send to a local file or any other output target supported by "
        "avformat_alloc_output_context2 (See FFmpeg documentation).");

    std::vector<std::string> avDictionaryTokens;

    std::string streamPixelFormatName, videoCodecName;

    desc.add_options()
        ("help,h"
        , "List posible options and their use.")

        ("output-shortname"
        , po::value<std::string>(&options.outputShortname_)->default_value("")
        , "Passed as \"short_name\" to avformat_alloc_output_context2.")

        ("output-filename"
        , po::value<std::string>(&options.outputFilename_)->required()
        , "Passed as \"filename\" to avformat_alloc_output_context2.")

        ("output-mime_type"
        , po::value<std::string>(&options.outputMimeType_)->default_value("")
        , "Passed as \"mime_type\" to avformat_alloc_output_context2.")

        ("duration"
        , po::value<double>(&options.streamDuration_)->default_value(0)
        , "The length of time the stream should be active in seconds. "
        "Values <= 0 are interpreted as never ending streams.")

        ("output-framerate"
        , po::value<AVRational>(&options.outputFrameRate_)->default_value(av_make_q(60, 1))->multitoken()
        , "The framerate of the outgoing video stream.")

        ("input-framerate"
        , po::value<AVRational>(&options.inputFrameRate_)->default_value(av_make_q(60, 1))->multitoken()
        , "The framerate of the target video stream.")

        ("output-resolution"
        , po::value<Resolution>(&options.outputResolution_)->required()->multitoken()
        , "The output resolution of the stream.")

        ("pixel-format"
        , po::value<std::string>(&streamPixelFormatName)->required()
        , "The pixelformat of uncompresed image data that the encoder should try to encode. "
        "Must be a format that is supported by the encoder. "
        "To get a list of formats supported by an encoder call: ffmpeg -h encoder=NAME_OF_ENCODER. "
        "Where NAME_OF_ENCODER is equal to the \"encoder\" option.")

        ("encoder"
        , po::value<std::string>(&videoCodecName)->default_value("")
        , "The encoder that should be used for encoding. Must be an encoder for videos. "
        "To get a list of all encoders that are supported by ffmpeg call: ffmpeg -encoders")

        ("bitrate"
        , po::value<int64_t>(&options.bitRate_)->required()
        , "The bitrate of the encoded stream.")

        ("shm-key"
        , po::value<int>(&options.sharedMemoryKey_)->default_value(RDB_SHM_ID_IMG_GENERATOR_OUT)
        , "The key of the shared memory to be be used for reading.")

        ("version", "Display the version and revision number.")

        ("av-dictionary"
        , po::value<std::vector<std::string> > (&avDictionaryTokens)->multitoken()
        , "A list of key=value pairs. "
        "The are used to setup an av dictionary with av_dict_set.");

    po::variables_map vm;

    po::store(po::command_line_parser(argc, argv)
              .options(desc)
              .style(po::command_line_style::unix_style)
              .run(), vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        exit(1);
    }
    if (vm.count("version"))
    {
        std::cout <<
            "Version: " << ExampleSharedMemoryVideoStreamer_VERSION_STRING <<
            ", Revision: " << ExampleSharedMemoryVideoStreamer_VERSION_REVISION << "\n";
        exit(1);
    }

    po::notify(vm);

    initializePixelFormatId(options, streamPixelFormatName);
    initializeVideoCodecId(options, videoCodecName);
    initializeAvDictionary(options, avDictionaryTokens);

    return options;
}

} // namespace
