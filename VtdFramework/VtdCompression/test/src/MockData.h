#ifndef VtdCompression_Test_MOCK_DATA_H
#define VtdCompression_Test_MOCK_DATA_H

#include <cstdlib>

namespace
{
    const unsigned char* NULLPTR = NULL; //for gtest comparison only

    // constant test input data
    const size_t DATA_SIZE = 256;
    const unsigned char DATA[DATA_SIZE] =
        {
                0x09, 0x94, 0xe0, 0xcc, 0x2f, 0xcf, 0xc6, 0x97, 0x6f, 0x80, 0x4e, 0x72, 0x94, 0xa1, 0xe0, 0x2b,
                0x5c, 0x7e, 0xa6, 0x13, 0x71, 0x99, 0x87, 0xde, 0xf1, 0xab, 0x89, 0x6e, 0x2a, 0x4a, 0x3e, 0xb9,
                0x0a, 0xde, 0x8d, 0x0b, 0x51, 0x43, 0x06, 0xb7, 0x5f, 0x61, 0x46, 0x5a, 0xab, 0xa9, 0x72, 0x9c,
                0x41, 0x92, 0x5e, 0x84, 0xce, 0x41, 0xb8, 0x4f, 0x94, 0x1d, 0x52, 0x2e, 0x3e, 0x63, 0x4a, 0x54,
                0x8a, 0x5d, 0x10, 0x9d, 0xa4, 0x3c, 0x56, 0x6f, 0x82, 0x48, 0xba, 0x27, 0x5d, 0xde, 0x49, 0x0a,
                0x42, 0x5c, 0xf3, 0xe8, 0x50, 0xa1, 0xf6, 0xa2, 0x08, 0x26, 0xe1, 0x48, 0x14, 0xd6, 0xe3, 0x56,
                0xfb, 0xc8, 0x46, 0x26, 0xbb, 0x5c, 0xc6, 0xa7, 0xd6, 0x9f, 0xe3, 0x7e, 0x94, 0xaa, 0xff, 0xb7,
                0xe8, 0xf4, 0x00, 0x56, 0x1d, 0x5a, 0xb6, 0x8b, 0x8f, 0x9a, 0xed, 0x7c, 0x92, 0x51, 0xd6, 0x40,
                0xd9, 0xc3, 0xdc, 0x8f, 0x05, 0x00, 0xb8, 0xff, 0x24, 0x7a, 0x1d, 0xa3, 0xa7, 0xc3, 0x1a, 0x60,
                0xe0, 0xba, 0x7f, 0x78, 0x80, 0x00, 0x1d, 0x6a, 0x72, 0xcd, 0xcf, 0xcb, 0x01, 0x40, 0x53, 0x46,
                0x0d, 0x7a, 0x74, 0x9d, 0x6a, 0x05, 0x8f, 0xf8, 0x05, 0x13, 0xe3, 0x69, 0xe1, 0xc0, 0xca, 0x2e,
                0x5e, 0xef, 0x2b, 0x3a, 0xbd, 0x7c, 0xff, 0xa2, 0xd1, 0xdc, 0x99, 0x6d, 0x9d, 0xb1, 0x3c, 0x2e,
                0x66, 0xdf, 0x88, 0x43, 0xc7, 0xc3, 0x2d, 0x58, 0xd8, 0xa0, 0x63, 0xdf, 0x2f, 0xff, 0x3c, 0x97,
                0x33, 0x85, 0x3f, 0xa8, 0x95, 0xb2, 0x33, 0x0f, 0x55, 0xa8, 0x27, 0x8f, 0xe8, 0x2b, 0xa0, 0x2c,
                0x47, 0xad, 0xac, 0x8f, 0xbf, 0xd8, 0x18, 0x29, 0xcc, 0xbb, 0xef, 0x2e, 0x6b, 0x85, 0xde, 0x72,
                0x0f, 0x89, 0x4b, 0xc3, 0x58, 0x72, 0x1e, 0xd4, 0x22, 0xaf, 0xea, 0xb8, 0x35, 0x4a, 0x68, 0x4c
        };
    const unsigned char& DATA_REF = DATA[0];

    namespace BITMAP {
        const size_t SIZE = 256;
        const size_t STRIDE = 4;
        const unsigned char DATA[256] =
        {
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02,
            0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02,
            0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
            0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
            0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
            0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01,
            0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
            0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00,
            0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02,
            0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03,
            0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
        };
        const unsigned char& REF = DATA[0];
    } //namespace BITMAP

    class BmpData
    {
    public:
        BmpData()
                : data_(NULL)
                , size_(0)
                , stride_(0)
        {}

        BmpData(size_t size, size_t bytesPerPixel, unsigned int seed, unsigned int variation)
                : data_(NULL)
                , size_(0)
                , stride_(0)
        {
            generateData(size, bytesPerPixel, seed, variation);
        }

        ~BmpData()
        {
            delete[] data_;
            data_ = NULL;
            size_ = 0;
        }

        /**
         * Fill this Bitmap with random values.
         * @param size the size of data to generate.
         * @param bytesPerPixel the bytes per pixel.
         * @param seed the seed with which to initialize the random number generator.
         * @param variation specifies the range for the random number generator [0, variation].
         */
        void generateData(size_t size, size_t bytesPerPixel, unsigned int seed, unsigned int variation)
        {
            assert(size % bytesPerPixel == 0 && size > 0);

            delete[] data_;
            data_ = new unsigned char[size];
            size_ = size;
            stride_ = bytesPerPixel;

            srand(seed);
            for(size_t i = 0; i < size; i += bytesPerPixel)
            {
                memset(data_+i, rand() % variation, bytesPerPixel);
            }
        }

        /**
         * generate anonymous struct with contents of this bitmap
         * @return a string containing the code for the struct.
         */
        std::string toCxxCode(const std::string& symbolName, size_t columns = 16) const
        {
            std::stringstream ss;
            ss << "const struct {\n" \
               << "    const size_t SIZE = " << size_ << ";\n" \
               << "    const size_t STRIDE = " << stride_ << ";\n" \
               << "    const unsigned char DATA[" << size_ << "] = \n" \
               << "    {\n";

            for(size_t i = 0; i < size_/columns; ++i)
            {
                ss << "   ";
                for(size_t j = 0; j < columns; ++j)
                {
                    ss << " " << "0x" << std::nouppercase << std::setfill('0') << std::setw(2) << std::hex << static_cast<short>(data_[i*columns+j]) << ((i*columns+j != size_-1) ? "," : "");
                }
                ss << "\n";
            }

            ss << "    };\n" \
               << "    const unsigned char& REF = DATA[0];}\n" \
               << "} " << symbolName << ";";

            return ss.str();
        }

        const unsigned char* getData() const { return data_; }
        const unsigned char& getDataRef() const { return *data_; }
        size_t getSize() const { return size_; }
        size_t getStride() const { return stride_; }

    private:
        unsigned char* data_;
        size_t size_;
        size_t stride_;
    };
}


#endif //VtdCompression_Test_MOCK_DATA_H