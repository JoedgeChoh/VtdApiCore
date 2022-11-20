#ifndef _RDB_HDF5_MESSAGE_RDB_OBJECT_CFG_H
#define _RDB_HDF5_MESSAGE_RDB_OBJECT_CFG_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>
#include <string>

namespace RdbToHdf5Writer
{

    class Hdf5RdbMessageObjectCfg
    {

    public:

        struct ENRICHED_RDB_OBJECT_CFG
        {
            uint32_t frameNumber;
            uint32_t id;                                    /**< unique object ID                                              @unit _                                  @version 0x0100 */
            uint8_t  category;                              /**< object category                                               @unit @link RDB_OBJECT_CATEGORY @endlink @version 0x0100 */
            uint8_t  type;                                  /**< object type                                                   @unit @link RDB_OBJECT_TYPE     @endlink @version 0x0100 */
            int16_t  modelId;                               /**< visual model ID                                               @unit _                                  @version 0x0100 */
            char     name[RDB_SIZE_OBJECT_NAME];            /**< symbolic name                                                 @unit _                                  @version 0x0100 */
            char     modelName[RDB_SIZE_OBJECT_NAME];       /**< model name associated to an object                            @unit _                                  @version 0x0100 */
            char     fileName[RDB_SIZE_FILENAME];           /**< filename associated to an object                              @unit _                                  @version 0x0100 */
            uint16_t flags;                                 /**< object configuration flags                                    @unit @link RDB_OBJECT_CFG_FLAG @endlink @version 0x0100 */
            uint16_t spare0;                                /**< reserved for future use                                       @unit _                                  @version 0x0100 */
            uint32_t spare1;                                /**< reserved for future use                                       @unit _                                  @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;
            
        enum RDB_OBJECT_CFG_HDF5 { RDB_OBJECT_CFG_HDF5_FRAME_NUMBER,
                                    RDB_OBJECT_CFG_HDF5_ID,
                                    RDB_OBJECT_CFG_HDF5_CATEGORY,
                                    RDB_OBJECT_CFG_HDF5_TYPE,
                                    RDB_OBJECT_CFG_HDF5_MODEL_ID,
                                    RDB_OBJECT_CFG_HDF5_NAME,
                                    RDB_OBJECT_CFG_HDF5_MODEL_NAME,
                                    RDB_OBJECT_CFG_HDF5_FILE_NAME,
                                    RDB_OBJECT_CFG_HDF5_FLAGS,
                                    RDB_OBJECT_CFG_HDF5_SPARE0,
                                    RDB_OBJECT_CFG_HDF5_SPARE1,
                                    RDB_OBJECT_CFG_HDF5_NDATA};
      
        Hdf5RdbMessageObjectCfg();

        virtual ~Hdf5RdbMessageObjectCfg();

        void initData();

        static void convertToModifiedStructure(const RDB_OBJECT_CFG_t& data, const uint32_t frameNumber, ENRICHED_RDB_OBJECT_CFG& modifiedData);

    public:

        size_t dstOffset_[RDB_OBJECT_CFG_HDF5_NDATA];
        size_t dstSizes_[RDB_OBJECT_CFG_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_OBJECT_CFG_HDF5_NDATA];
        hid_t fieldType_[RDB_OBJECT_CFG_HDF5_NDATA];
        // Initialize the field field_type
        hid_t stringType1_, stringType2_;
        size_t tableSize_;
        char tableName[32];
    };
}


#endif
