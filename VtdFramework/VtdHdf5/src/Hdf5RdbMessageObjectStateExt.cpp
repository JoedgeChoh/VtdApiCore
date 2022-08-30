#include <VtdHdf5/Hdf5RdbMessageObjectStateExt.h>
#include <cstring>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageObjectStateExt::Hdf5RdbMessageObjectStateExt() : tableSize_(RDB_OBJECT_STATE_EXT_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageObjectStateExt::~Hdf5RdbMessageObjectStateExt()
        {
            H5Tclose(unitArray_);
        }

        void Hdf5RdbMessageObjectStateExt::initData()
        {
            dims_[0] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::spare) / sizeof(uint32_t);
            
            unitArray_ = H5Tarray_create (H5T_NATIVE_UINT32, 1, dims_);

            dstSize_ = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED);

            dstOffset_[RDB_OBJECT_STATE_EXT_HDF5_FRAME_NUMBER] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, frameNumber);
            dstSizes_ [RDB_OBJECT_STATE_EXT_HDF5_FRAME_NUMBER] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::frameNumber);
            fieldType_[RDB_OBJECT_STATE_EXT_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_OBJECT_STATE_EXT_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_OBJECT_STATE_EXT_HDF5_TRAVEL_DIST] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, traveledDist);
            dstSizes_ [RDB_OBJECT_STATE_EXT_HDF5_TRAVEL_DIST] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::traveledDist);
            fieldType_[RDB_OBJECT_STATE_EXT_HDF5_TRAVEL_DIST] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_OBJECT_STATE_EXT_HDF5_TRAVEL_DIST] = "traveledDist";

            dstOffset_[RDB_OBJECT_STATE_EXT_HDF5_SPARE] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, spare);
            dstSizes_ [RDB_OBJECT_STATE_EXT_HDF5_SPARE] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::spare);
            fieldType_[RDB_OBJECT_STATE_EXT_HDF5_SPARE] = unitArray_;
            fieldNames_[RDB_OBJECT_STATE_EXT_HDF5_SPARE] = "spare";

            dstOffset_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_X] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, speed_x);
            dstSizes_ [RDB_OBJECT_STATE_EXT_SPEED_HDF5_X] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::speed_x);
            fieldType_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_X] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_X] = "speed_x";

            dstOffset_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_Y] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, speed_y);
            dstSizes_ [RDB_OBJECT_STATE_EXT_SPEED_HDF5_Y] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::speed_y);
            fieldType_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_Y] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_Y] = "speed_y";

            dstOffset_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_Z] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, speed_z);
            dstSizes_ [RDB_OBJECT_STATE_EXT_SPEED_HDF5_Z] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::speed_z);
            fieldType_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_Z] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_Z] = "speed_z";

            dstOffset_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_H] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, speed_h);
            dstSizes_ [RDB_OBJECT_STATE_EXT_SPEED_HDF5_H] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::speed_h);
            fieldType_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_H] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_H] = "speed_h";

            dstOffset_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_P] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, speed_p);
            dstSizes_ [RDB_OBJECT_STATE_EXT_SPEED_HDF5_P] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::speed_p);
            fieldType_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_P] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_P] = "speed_p";

            dstOffset_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_R] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, speed_r);
            dstSizes_ [RDB_OBJECT_STATE_EXT_SPEED_HDF5_R] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::speed_r);
            fieldType_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_R] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_R] = "speed_r";

            dstOffset_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_FLAGS] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, speed_flags);
            dstSizes_ [RDB_OBJECT_STATE_EXT_SPEED_HDF5_FLAGS] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::speed_flags);
            fieldType_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_FLAGS] = H5T_NATIVE_INT8;
            fieldNames_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_FLAGS] = "speed_flags";

            dstOffset_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_TYPE] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, speed_type);
            dstSizes_ [RDB_OBJECT_STATE_EXT_SPEED_HDF5_TYPE] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::speed_type);
            fieldType_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_TYPE] = H5T_NATIVE_INT8;
            fieldNames_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_TYPE] = "speed_type";

            dstOffset_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_SYSTEM] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, speed_system);
            dstSizes_ [RDB_OBJECT_STATE_EXT_SPEED_HDF5_SYSTEM] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::speed_system);
            fieldType_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_SYSTEM] = H5T_NATIVE_INT16;
            fieldNames_[RDB_OBJECT_STATE_EXT_SPEED_HDF5_SYSTEM] = "speed_system";

            dstOffset_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_X] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, accel_x);
            dstSizes_ [RDB_OBJECT_STATE_EXT_ACCEL_HDF5_X] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::accel_x);
            fieldType_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_X] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_X] = "accel_x";

            dstOffset_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Y] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, accel_y);
            dstSizes_ [RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Y] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::accel_y);
            fieldType_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Y] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Y] = "accel_y";

            dstOffset_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Z] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, accel_z);
            dstSizes_ [RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Z] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::accel_z);
            fieldType_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Z] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_Z] = "accel_z";

            dstOffset_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_H] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, accel_h);
            dstSizes_ [RDB_OBJECT_STATE_EXT_ACCEL_HDF5_H] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::accel_h);
            fieldType_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_H] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_H] = "accel_h";

            dstOffset_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_P] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, accel_p);
            dstSizes_ [RDB_OBJECT_STATE_EXT_ACCEL_HDF5_P] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::accel_p);
            fieldType_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_P] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_P] = "accel_p";

            dstOffset_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_R] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, accel_r);
            dstSizes_ [RDB_OBJECT_STATE_EXT_ACCEL_HDF5_R] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::accel_r);
            fieldType_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_R] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_R] = "accel_r";

            dstOffset_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_FLAGS] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, accel_flags);
            dstSizes_ [RDB_OBJECT_STATE_EXT_ACCEL_HDF5_FLAGS] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::accel_flags);
            fieldType_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_FLAGS] = H5T_NATIVE_INT8;
            fieldNames_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_FLAGS] = "accel_flags";

            dstOffset_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_TYPE] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, accel_type);
            dstSizes_ [RDB_OBJECT_STATE_EXT_ACCEL_HDF5_TYPE] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::accel_type);
            fieldType_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_TYPE] = H5T_NATIVE_INT8;
            fieldNames_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_TYPE] = "accel_type";

            dstOffset_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_SYSTEM] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_EXTENDED, accel_system);
            dstSizes_ [RDB_OBJECT_STATE_EXT_ACCEL_HDF5_SYSTEM] = sizeof(SIMPLE_RDB_OBJECT_STATE_EXTENDED::accel_system);
            fieldType_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_SYSTEM] = H5T_NATIVE_INT16;
            fieldNames_[RDB_OBJECT_STATE_EXT_ACCEL_HDF5_SYSTEM] = "accel_system";
        }

        void Hdf5RdbMessageObjectStateExt::convertToModifiedStructure(const RDB_OBJECT_STATE_EXT_t& data, const uint32_t frameNumber, Hdf5RdbMessageObjectStateExt::SIMPLE_RDB_OBJECT_STATE_EXTENDED& modifiedData)
        {
            // OBJECT STATE EXT
            modifiedData.frameNumber = frameNumber;
            modifiedData.traveledDist = data.traveledDist;
            std::memcpy(modifiedData.spare, data.spare, sizeof(Hdf5RdbMessageObjectStateExt::SIMPLE_RDB_OBJECT_STATE_EXTENDED::spare));

            // OBJECT STATE EXT SPEED
            const RDB_COORD_t* speed = &(data.speed);
            modifiedData.speed_x = speed->x;
            modifiedData.speed_y = speed->y;
            modifiedData.speed_z = speed->z;
            modifiedData.speed_h = speed->h;
            modifiedData.speed_p = speed->p;
            modifiedData.speed_r = speed->r;
            modifiedData.speed_flags = speed->flags;
            modifiedData.speed_type = speed->type;
            modifiedData.speed_system = speed->system;

            // OBJECT STATE EXT ACCEL
            const RDB_COORD_t* accel = &(data.accel);
            modifiedData.accel_x = accel->x;
            modifiedData.accel_y = accel->y;
            modifiedData.accel_z = accel->z;
            modifiedData.accel_h = accel->h;
            modifiedData.accel_p = accel->p;
            modifiedData.accel_r = accel->r;
            modifiedData.accel_flags = accel->flags;
            modifiedData.accel_type = accel->type;
            modifiedData.accel_system = accel->system;
        }
}

