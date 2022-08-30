#include "ImageGenerator.h"

#include <string>
#include <cmath>
#include <unistd.h>

#include <VtdCore/FileSystemIO.h>

namespace
{
    const static unsigned int START_FRAME = 0;

}

ImageGenerator::ImageGenerator(  const std::vector<SharedMemoryHandle>& shmKeys
                               , const unsigned int& bufferFlag
                               , const std::string& fileName)
    : shmKeys_(shmKeys)
    , bufferFlag_(bufferFlag)
    , pictureFileName_(fileName)
    , pictureType_(RdbImageIO::FileFormat::RawData)
{
    this->init();
}

ImageGenerator::~ImageGenerator()
{
    deleteSharedeMemory();
}

void ImageGenerator::init()
{
    isAttached_ = false;
    isThisFirstFrame_ = false;
    frameNo_ = 0;
    lastFrameNo_ = 0;
}

bool ImageGenerator::initSharedMemory()
{
    for (std::vector<SharedMemoryHandle>::const_iterator itr = shmKeys_.begin(); itr < shmKeys_.end(); ++itr)
    {
        std::cout << *itr << std::endl;
        shmIoVec_.push_back(new SharedMemoryIO (*itr));
        shmIoVec_.back()->attach();
        isAttached_ = shmIoVec_.back()->isAttached();
        if (!isAttached_)
        {
            return false;
        }
        lastFrameNoMap_.insert(std::pair<SharedMemoryHandle, uint32_t>(*itr, START_FRAME));
    }

    return true;
}

void ImageGenerator::deleteSharedeMemory()
{
    // Delete pointers to shared memory IO
    for (size_t i = 0; i < shmIoVec_.size(); i++)
    {
        delete shmIoVec_[i];
        shmIoVec_[i] = 0;
    }
    shmIoVec_.clear();
}

RDB_IMAGE_t* ImageGenerator::fetchRdbImage(RDB_MSG_t* msg)
{
    RDB_MSG_ENTRY_HDR_t* entry = reinterpret_cast<RDB_MSG_ENTRY_HDR_t*>(reinterpret_cast<unsigned char*>(msg) + msg->hdr.headerSize);
    int32_t remainingBytes = msg->hdr.dataSize;
    while (remainingBytes)
    {
        unsigned int noElements = entry->elementSize ? (entry->dataSize / entry->elementSize) : 0;
        unsigned char* dataPtr = reinterpret_cast<unsigned char*>(entry);
        dataPtr += entry->headerSize;
        while (noElements--)
        {
            switch(entry->pkgId)
            {
            case RDB_PKG_ID_IMAGE:
            {
                return reinterpret_cast<RDB_IMAGE_t*>(dataPtr);
            }
                default: /* not handled */ break;
            }
            dataPtr += entry->elementSize;
        }

        remainingBytes -= (entry->headerSize + entry->dataSize);
        if (remainingBytes)
        {
            entry = reinterpret_cast<RDB_MSG_ENTRY_HDR_t*>(reinterpret_cast<unsigned char*>(entry) + entry->headerSize + entry->dataSize);
        }
    }
}

void ImageGenerator::proccessSharedMemory()
{
        allPictureWritten_ = false;
        for (std::vector<SharedMemoryIO*>::iterator itr = shmIoVec_.begin(); itr < shmIoVec_.end(); ++itr)
        {
            SharedMemoryBuffer buffer = (*itr)->getNextBuffer(bufferFlag_);
            if (buffer.rdbMsg && buffer.info)
            {
              frameNo_ = buffer.rdbMsg->hdr.frameNo;
              (*itr)->lockBuffer(*buffer.info);
              if (lastFrameNoMap_.find((*itr)->getShmHandle())->second != frameNo_)
              {
                  RDB_IMAGE_t* image = fetchRdbImage(buffer.rdbMsg);
                  std::string fileName = pictureFileName_ + "frame_" + Internal::FileSystemIO::toString(frameNo_)
                          + "_" +  Internal::FileSystemIO::toString((*itr)->getShmHandle());

                  write(fileName, image);
                  boost::this_thread::sleep_for(boost::chrono::milliseconds(8));
              }
              buffer.info->flags &= ~bufferFlag_;
              (*itr)->releaseBuffer(*buffer.info);
            }

            if (!(*itr)->isAttached())
            {
               std::cout << "SHM::Segment " << (*itr)->getShmHandle() << " is not attached"<<std::endl;
               break;
            }
       }
       allPictureWritten_ = true;
}

void ImageGenerator::setCamera(VtdApi& vtdApi)
{
    std::string cameraCommand = "<Camera name=\"VIEW_CAMERA\" showOwner=\"false\"><Frustum far=\"1500.000000\" fovHor=\"40.000000\" fovVert=\"30.000000\" near=\"1.000000\" offsetHor=\"0.000000\" offsetVert=\"0.000000\" /><PosEyepoint player=\"Ego\" /><ViewRelative dh=\"0.000000\" dp=\"0.000000\" dr=\"0.000000\" /><Set /></Camera>";
    vtdApi.sendScpCommand(cameraCommand);
}

void ImageGenerator::write(std::string& fileName, RDB_IMAGE_t* image)
{
    if (!image)
        return;

    switch (pictureType_)
    {
#ifdef PNG_ENABLED
        case RdbImageIO::FileFormat::PNG:
        {
            fileName.append(".png");
            std::cout << "Write Image " << fileName << "\n";
            if(!RdbImageIO::writeRdbImgToFile(*image, fileName, RdbImageIO::FileFormat::PNG, 0, true))
            {
                std::cerr << "Error writing file " << fileName << std::endl;
            }
        }break;
#endif // PNG_ENABLED
        case RdbImageIO::FileFormat::RawData:
        {
            fileName.append(".data");
            std::cout << "Write Image " << fileName << "\n";
            if (!RdbImageIO::writeRdbImgToFile(*image, fileName, RdbImageIO::FileFormat::RawData, 0, true))
            {
                std::cerr << "Error writing file " << fileName << std::endl;
            }
        }break;

        case RdbImageIO::FileFormat::TGA:
        {
            fileName.append(".tga");
            std::cout << "Write Image " << fileName << "\n";
            if (!RdbImageIO::writeRdbImgToFile(*image, fileName, RdbImageIO::FileFormat::TGA, 0, false))
            {
                std::cerr << "Error writing file " << fileName << std::endl;
            }
        }break;

        case RdbImageIO::FileFormat::BMP:
        {
            fileName.append(".bmp");
            std::cout << "Write Image " << fileName << "\n";
            if (!RdbImageIO::writeRdbImgToFile(*image, fileName, RdbImageIO::FileFormat::BMP, 0 , false));
            {
                std::cerr << "Error writing file " << fileName << std::endl;
            }
        }break;

        case RdbImageIO::FileFormat::CSV:
        {
            fileName.append(".csv");
            std::cout << "Write Image " << fileName << "\n";
            if (!RdbImageIO::writeRdbImgToFile(*image, fileName, RdbImageIO::FileFormat::CSV, 0 , false))
            {
                std::cerr << "Error writing file " << fileName << std::endl;
            }
        }break;
#ifdef JPEG_ENABLED
        case RdbImageIO::FileFormat::JPG:
        {
            fileName.append(".jpg");
            std::cout << "Write Image " << fileName << "\n";
            if (!RdbImageIO::writeRdbImgToFile(*image, fileName, RdbImageIO::FileFormat::JPG, 80 , true))
            {
                std::cerr << "Error writing file " << fileName << std::endl;
            }
        }break;
#endif // JPEG_ENABLED
//TODO: Due to circular dependencies this is being deactivated for now, and will be replaced by a better solution later on.
//TODO: To write images into HDF files please use the WriteHdf5Image class from VtdHdf5 directly
//#ifdef HDF_ENABLED
//        case RdbImageIO::FileFormat::HDF5:
//        {
//             fileName.append(".h5");
//             std::cout << "Write Image " << fileName << "\n";
//             if (!RdbImageIO::writeRdbImgToFile(*image, fileName, RdbImageIO::FileFormat::HDF5, 0 , true))
//             {
//                 std::cerr << "Error writing file " << fileName << std::endl;
//             }

//        }break;
//#endif
        default:
            break;
    }
}

void ImageGenerator::run()
{
    while (stopRequested() == false)
    {
        proccessSharedMemory();
        boost::this_thread::sleep_for(boost::chrono::milliseconds(2));
    }

    std::cout << "Stop writing images..............\n";
}
