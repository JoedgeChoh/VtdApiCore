#ifndef _RDB_HDF5_MESSAGE_RDB_VEHICLE_SETUP_H
#define _RDB_HDF5_MESSAGE_RDB_VEHICLE_SETUP_H

#include <VtdToolkit/viRDBIcd.h>

#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageVehicleSetup
    {
        
    public:

        struct ENRICHED_RDB_VEHICLE_SETUP
        {
            uint32_t frameNumber;
            uint32_t playerId;       /**< ID of the player to which the data belongs                                       @unit _                     @version 0x0100 */
            float    mass;           /**< vehicle mass                                                                     @unit kg                    @version 0x0100 */
            float    wheelBase;      /**< wheel base                                                                       @unit m                     @version 0x0100 */
            int32_t  spare[4];       /**< for future use                                                                   @unit _                     @version 0x0100 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_VEHICLE_SETUP_HDF5 {   RDB_VEHICLE_SETUP_HDF5_FRAME_NUMBER,
                                        RDB_VEHICLE_SETUP_HDF5_PLAYER_ID,
                                        RDB_VEHICLE_SETUP_HDF5_MASS,
                                        RDB_VEHICLE_SETUP_HDF5_WHEEL_BASE,
                                        RDB_VEHICLE_SETUP_HDF5_SPARE,
                                        RDB_VEHICLE_SETUP_HDF5_NDATA};

        Hdf5RdbMessageVehicleSetup();

        virtual ~Hdf5RdbMessageVehicleSetup();

        void initData();

        static void convertToModifiedStructure(const RDB_VEHICLE_SETUP_t& data, const uint32_t frameNumber, ENRICHED_RDB_VEHICLE_SETUP& modifiedData);

    public:
        
        hsize_t  dims_[1];
        size_t dstOffset_[RDB_VEHICLE_SETUP_HDF5_NDATA];
        size_t dstSizes_[RDB_VEHICLE_SETUP_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_VEHICLE_SETUP_HDF5_NDATA];
        hid_t fieldType_[RDB_VEHICLE_SETUP_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;
        hid_t intArray_;

    private:

        uint32_t positionFrameId;
        char tableName[TABLE_NAME_SIZE];

    };
}

#endif
