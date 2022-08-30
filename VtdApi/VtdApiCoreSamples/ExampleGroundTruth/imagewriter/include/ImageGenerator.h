#ifndef IMAGE_GENERATOR_H
#define IMAGE_GENERATOR_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdToolkit/Rdb/SharedMemoryIO.h>
#include <VtdToolkit/Rdb/RdbImageIO.h>
#include "Stoppable.h"

/**
 * Class ImageGenerator read shared and write images to files
 */

using namespace VTD;

class ImageGenerator : public Stoppable
{
public:

    /**
     * @brief ImageGenerator - constructor of Image Generator Class
     * @param shmKey - shared memory key
     * @param bufferFlag - buffer flag
     * @param fileName - PNG file names
     */
    explicit ImageGenerator(const std::vector<SharedMemoryHandle>& shmKey
                            , const unsigned int& bufferFlag
                            , const std::string& fileName);

    /**
     * @brief ~ImageGenerator - destuctor of Image generator class
     */
    virtual ~ImageGenerator();

    /**
     * @brief proccessSharedMemory - read shared memory buffer and writes data
     */
    void proccessSharedMemory();

    /**
     * @brief init - init parameters
     */
    void init();

    /**
     * @brief initSharedMemory - attached to shared memory
     * @return true if succes
     */
    bool initSharedMemory();

    /**
     * @brief setCamera - set camera position
     * @param vtdApi
     */
    void setCamera(VtdApi& vtdApi);

    /**
     * @brief deleteSharedeMemory - delete shared memory segment
     */
    void deleteSharedeMemory();

    /**
     * @brief run - run procces of image
     */
    void run();

    bool waitUntilAllSaved();

    //set file name
    void setFileName(const std::string& fileName){pictureFileName_ = fileName;}

    void write(std::string& fileName, RDB_IMAGE_t* image);

    inline void setPictureType(RdbImageIO::FileFormat::Enum pictureType){pictureType_ = pictureType;}

    bool getAllPictureWritten_ () const { return allPictureWritten_;}

private:

    /**
     * @brief fetchRdbImage - read shared memory and return pointer to image
     * @param msg
     * @return
     */
    RDB_IMAGE_t* fetchRdbImage(RDB_MSG_t* msg);

private:
    // is shared memory attached
    bool isAttached_;
    // simulation, end and delta time
    double simTime_, endTime_, deltaTime_;
    // shared memory regions handles
    std::vector <SharedMemoryHandle> shmKeys_;
    // vec of shared memories IO-s
    std::vector<SharedMemoryIO*> shmIoVec_;
    // buffer read flag
    unsigned int bufferFlag_;
    // frame numbers
    uint32_t lastFrameNo_, simFrameNo_, frameNo_;
    // picture file name
    std::string pictureFileName_;
    // first frame or not
    bool isThisFirstFrame_;
    // picture to write
    RdbImageIO::FileFormat::Enum pictureType_;

    std::map<SharedMemoryHandle, uint32_t> lastFrameNoMap_;

    bool allPictureWritten_;
};

#endif // IMAGE_GENERATOR
