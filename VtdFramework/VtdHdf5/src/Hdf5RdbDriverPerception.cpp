#include <VtdHdf5/Hdf5RdbDriverPerception.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbDriverPerception::Hdf5RdbDriverPerception () : tableSize_(RDB_DRIVER_PERCEPTION_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbDriverPerception::~Hdf5RdbDriverPerception()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
            H5Tclose(floatArray_);
        }

        void Hdf5RdbDriverPerception::initData()
        {
           dimsUInt32_[0] = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION::spare) / sizeof(uint32_t);
           uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);
           
           dimsFloat_[0] = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION::spare0) / sizeof(float);
           floatArray_ = H5Tarray_create(H5T_NATIVE_FLOAT, 1, dimsFloat_);
   
           dstSize_ = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION);

           dstOffset_[RDB_DRIVER_PERCEPTION_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_DRIVER_PERCEPTION, frameNumber);
           dstSizes_ [RDB_DRIVER_PERCEPTION_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION::frameNumber);
           fieldType_[RDB_DRIVER_PERCEPTION_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_PERCEPTION_HDF5_FRAME_NUMBER] = "frameNumber";

           dstOffset_[RDB_DRIVER_PERCEPTION_HDF5_PLAYER_ID] = HOFFSET(ENRICHED_RDB_DRIVER_PERCEPTION, playerId);
           dstSizes_ [RDB_DRIVER_PERCEPTION_HDF5_PLAYER_ID] = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION::playerId);
           fieldType_[RDB_DRIVER_PERCEPTION_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_PERCEPTION_HDF5_PLAYER_ID] = "playerId";

           dstOffset_[RDB_DRIVER_PERCEPTION_HDF5_SPEED_FROM_RULES] = HOFFSET(ENRICHED_RDB_DRIVER_PERCEPTION, speedFromRules);
           dstSizes_ [RDB_DRIVER_PERCEPTION_HDF5_SPEED_FROM_RULES] = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION::speedFromRules);
           fieldType_[RDB_DRIVER_PERCEPTION_HDF5_SPEED_FROM_RULES] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_PERCEPTION_HDF5_SPEED_FROM_RULES] = "speedFromRules";

           dstOffset_[RDB_DRIVER_PERCEPTION_HDF5_DIST_TO_SPEED] = HOFFSET(ENRICHED_RDB_DRIVER_PERCEPTION, distToSpeed);
           dstSizes_ [RDB_DRIVER_PERCEPTION_HDF5_DIST_TO_SPEED] = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION::distToSpeed);
           fieldType_[RDB_DRIVER_PERCEPTION_HDF5_DIST_TO_SPEED] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_PERCEPTION_HDF5_DIST_TO_SPEED] = "distToSpeed";

           dstOffset_[RDB_DRIVER_PERCEPTION_HDF5_SPARE0] = HOFFSET(ENRICHED_RDB_DRIVER_PERCEPTION, spare0);
           dstSizes_ [RDB_DRIVER_PERCEPTION_HDF5_SPARE0] = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION::spare0);
           fieldType_[RDB_DRIVER_PERCEPTION_HDF5_SPARE0] = floatArray_;
           fieldNames_[RDB_DRIVER_PERCEPTION_HDF5_SPARE0] = "spare0";

           dstOffset_[RDB_DRIVER_PERCEPTION_HDF5_FLAGS] = HOFFSET(ENRICHED_RDB_DRIVER_PERCEPTION, flags);
           dstSizes_ [RDB_DRIVER_PERCEPTION_HDF5_FLAGS] = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION::flags);
           fieldType_[RDB_DRIVER_PERCEPTION_HDF5_FLAGS] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_PERCEPTION_HDF5_FLAGS] = "flags";

           dstOffset_[RDB_DRIVER_PERCEPTION_HDF5_SPARE] = HOFFSET(ENRICHED_RDB_DRIVER_PERCEPTION, spare);
           dstSizes_ [RDB_DRIVER_PERCEPTION_HDF5_SPARE] = sizeof(ENRICHED_RDB_DRIVER_PERCEPTION::spare);
           fieldType_[RDB_DRIVER_PERCEPTION_HDF5_SPARE] = uintArray32_;
           fieldNames_[RDB_DRIVER_PERCEPTION_HDF5_SPARE] = "spare";
        }

        void Hdf5RdbDriverPerception::convertToModifiedStructure(const RDB_DRIVER_PERCEPTION_t &data, const uint32_t frameNumber, Hdf5RdbDriverPerception::ENRICHED_RDB_DRIVER_PERCEPTION &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.playerId = data.playerId;
            modifiedData.speedFromRules = data.speedFromRules;
            modifiedData.distToSpeed = data.distToSpeed;
            modifiedData.spare0[0] = data.spare0[0];
            modifiedData.spare0[1] = data.spare0[1];
            modifiedData.spare0[2] = data.spare0[2];
            modifiedData.spare0[3] = data.spare0[3];
            modifiedData.flags = data.flags;
            modifiedData.spare[0] = data.spare[0];
            modifiedData.spare[1] = data.spare[1];
            modifiedData.spare[2] = data.spare[2];
            modifiedData.spare[3] = data.spare[3];
        }
}

