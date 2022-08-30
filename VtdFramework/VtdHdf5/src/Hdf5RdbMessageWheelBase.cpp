#include <VtdHdf5/Hdf5RdbMessageWheelBase.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageWheelBase::Hdf5RdbMessageWheelBase() : tableSize_(RDB_WHEEL_BASE_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageWheelBase::~Hdf5RdbMessageWheelBase()
        {
            // have to be close memory leak
            H5Tclose(uintArray8_);
            H5Tclose(uintArray32_);
        }

        void Hdf5RdbMessageWheelBase::initData()
        {
            dimsUInt8_[0] = sizeof(ENRICHED_RDB_WHEEL_BASE::spare0) / sizeof(uint8_t);
            dimsUInt32_[0] = sizeof(ENRICHED_RDB_WHEEL_BASE::spare1) / sizeof(uint32_t);
            
            uintArray8_ = H5Tarray_create(H5T_NATIVE_UINT8, 1, dimsUInt8_);
            uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);

            dstSize_ = sizeof(ENRICHED_RDB_WHEEL_BASE);

            dstOffset_[RDB_WHEEL_BASE_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, frameNumber);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_WHEEL_BASE::frameNumber);
            fieldType_[RDB_WHEEL_BASE_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_WHEEL_BASE_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_WHEEL_BASE_HDF5_PLAYER_ID] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, playerId);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_PLAYER_ID] = sizeof(ENRICHED_RDB_WHEEL_BASE::playerId);
            fieldType_[RDB_WHEEL_BASE_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_WHEEL_BASE_HDF5_PLAYER_ID] = "playerId";

            dstOffset_[RDB_WHEEL_BASE_HDF5_ID] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, id);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_ID] = sizeof(ENRICHED_RDB_WHEEL_BASE::id);
            fieldType_[RDB_WHEEL_BASE_HDF5_ID] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_WHEEL_BASE_HDF5_ID] = "id";

            dstOffset_[RDB_WHEEL_BASE_HDF5_FLAGS] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, flags);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_FLAGS] = sizeof(ENRICHED_RDB_WHEEL_BASE::flags);
            fieldType_[RDB_WHEEL_BASE_HDF5_FLAGS] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_WHEEL_BASE_HDF5_FLAGS] = "flags";

            dstOffset_[RDB_WHEEL_BASE_HDF5_SPARE0] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, spare0);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_SPARE0] = sizeof(ENRICHED_RDB_WHEEL_BASE::spare0);
            fieldType_[RDB_WHEEL_BASE_HDF5_SPARE0] = uintArray8_;
            fieldNames_[RDB_WHEEL_BASE_HDF5_SPARE0] = "spare0";

            dstOffset_[RDB_WHEEL_BASE_HDF5_RADIUS_STATIC] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, radiusStatic);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_RADIUS_STATIC] = sizeof(ENRICHED_RDB_WHEEL_BASE::radiusStatic);
            fieldType_[RDB_WHEEL_BASE_HDF5_RADIUS_STATIC] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_BASE_HDF5_RADIUS_STATIC] = "radiusStatic";

            dstOffset_[RDB_WHEEL_BASE_HDF5_SPRING_COMPRESSION] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, springCompression);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_SPRING_COMPRESSION] = sizeof(ENRICHED_RDB_WHEEL_BASE::springCompression);
            fieldType_[RDB_WHEEL_BASE_HDF5_SPRING_COMPRESSION] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_BASE_HDF5_SPRING_COMPRESSION] = "springCompression";

            dstOffset_[RDB_WHEEL_BASE_HDF5_ROT_ANGLE] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, rotAngle);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_ROT_ANGLE] = sizeof(ENRICHED_RDB_WHEEL_BASE::rotAngle);
            fieldType_[RDB_WHEEL_BASE_HDF5_ROT_ANGLE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_BASE_HDF5_ROT_ANGLE] = "rotAngle";

            dstOffset_[RDB_WHEEL_BASE_HDF5_SLIP] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, slip);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_SLIP] = sizeof(ENRICHED_RDB_WHEEL_BASE::slip);
            fieldType_[RDB_WHEEL_BASE_HDF5_SLIP] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_BASE_HDF5_SLIP] = "slip";

            dstOffset_[RDB_WHEEL_BASE_HDF5_STEERING_ANGLE] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, steeringAngle);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_STEERING_ANGLE] = sizeof(ENRICHED_RDB_WHEEL_BASE::steeringAngle);
            fieldType_[RDB_WHEEL_BASE_HDF5_STEERING_ANGLE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_BASE_HDF5_STEERING_ANGLE] = "steeringAngle";

            dstOffset_[RDB_WHEEL_BASE_HDF5_SPARE1] = HOFFSET(ENRICHED_RDB_WHEEL_BASE, spare1);
            dstSizes_ [RDB_WHEEL_BASE_HDF5_SPARE1] = sizeof(ENRICHED_RDB_WHEEL_BASE::spare1);
            fieldType_[RDB_WHEEL_BASE_HDF5_SPARE1] = uintArray32_;
            fieldNames_[RDB_WHEEL_BASE_HDF5_SPARE1] = "spare1";
        }

        void Hdf5RdbMessageWheelBase::convertToModifiedStructure(const RDB_WHEEL_BASE_t &data, const uint32_t frameNumber, Hdf5RdbMessageWheelBase::ENRICHED_RDB_WHEEL_BASE &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.playerId = data.playerId;
            modifiedData.id = data.id;
            modifiedData.flags = data.flags;
            modifiedData.spare0[0] = data.spare0[0];
            modifiedData.spare0[1] = data.spare0[1];
            modifiedData.radiusStatic = data.radiusStatic;
            modifiedData.springCompression = data.springCompression;
            modifiedData.rotAngle = data.rotAngle;
            modifiedData.slip = data.slip;
            modifiedData.steeringAngle = data.steeringAngle;
            modifiedData.spare1[0] = data.spare1[0];
            modifiedData.spare1[1] = data.spare1[1];
            modifiedData.spare1[2] = data.spare1[2];
            modifiedData.spare1[3] = data.spare1[3];
        }

}

