#include <VtdHdf5/Hdf5RdbSensorObject.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbSensorObject::Hdf5RdbSensorObject() : tableSize_(RDB_SENSOR_OBJECT_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbSensorObject::~Hdf5RdbSensorObject ()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
            H5Tclose(uintArray8_);
        }

        void Hdf5RdbSensorObject ::initData()
        {
           dimsUInt32_[0] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::spare) / sizeof(uint32_t);
           uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);
            
           dimsUInt8_[0] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::spare0) / sizeof(uint8_t);
           uintArray8_ = H5Tarray_create(H5T_NATIVE_UINT8, 1, dimsUInt8_);
            
           dstSize_ = sizeof(ENRICHED_RDB_SENSOR_OBJECT);

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, frameNumber);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::frameNumber);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_FRAME_NUMBER] = "frameNumber";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_CATEGORY] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, category);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_CATEGORY] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::category);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_CATEGORY] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_CATEGORY] = "category";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_TYPE] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, type);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_TYPE] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::type);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_TYPE] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_TYPE] = "type";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_FLAGS] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, flags);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_FLAGS] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::flags);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_FLAGS] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_FLAGS] = "flags";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_ID] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, id);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_ID] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::id);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_ID] = "id";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_ID] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorId);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_ID] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorId);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_ID] = "sensorId";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_DIST] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, dist);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_DIST] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::dist);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_DIST] = H5T_NATIVE_DOUBLE;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_DIST] = "dist";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_X] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorPos_x);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_X] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorPos_x);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_X] = H5T_NATIVE_DOUBLE;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_X] = "pos_x";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Y] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorPos_y);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Y] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorPos_y);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Y] = H5T_NATIVE_DOUBLE;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Y] = "pos_y";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Z] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorPos_z);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Z] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorPos_z);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Z] = H5T_NATIVE_DOUBLE;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_Z] = "pos_z";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_H] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorPos_h);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_H] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorPos_h);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_H] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_H] = "pos_h";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_P] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorPos_p);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_P] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorPos_p);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_P] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_P] = "pos_p";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_R] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorPos_r);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_R] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorPos_r);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_R] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_R] = "pos_r";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_FLAGS] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorPos_flags);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_FLAGS] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorPos_flags);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_FLAGS] = H5T_NATIVE_INT8;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_FLAGS] = "pos_flags";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_TYPE] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorPos_type);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_TYPE] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorPos_type);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_TYPE] = H5T_NATIVE_INT8;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_TYPE] = "pos_type";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_SYSTEM] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, sensorPos_system);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_SYSTEM] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::sensorPos_system);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_SYSTEM] = H5T_NATIVE_INT16;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SENSOR_POS_SYSTEM] = "pos_system";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_OCCLUSION] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, occlusion);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_OCCLUSION] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::occlusion);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_OCCLUSION] = H5T_NATIVE_INT8;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_OCCLUSION] = "occlusion";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_DELTA_LANE_POS] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, deltaLanePos);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_DELTA_LANE_POS] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::deltaLanePos);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_DELTA_LANE_POS] = H5T_NATIVE_INT8;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_DELTA_LANE_POS] = "deltaLanePos";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SPARE0] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, spare0);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SPARE0] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::spare0);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SPARE0] = uintArray8_;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SPARE0] = "spare0";

           dstOffset_[RDB_SENSOR_OBJECT_HDF5_SPARE] = HOFFSET(ENRICHED_RDB_SENSOR_OBJECT, spare);
           dstSizes_ [RDB_SENSOR_OBJECT_HDF5_SPARE] = sizeof(ENRICHED_RDB_SENSOR_OBJECT::spare);
           fieldType_[RDB_SENSOR_OBJECT_HDF5_SPARE] = uintArray32_;
           fieldNames_[RDB_SENSOR_OBJECT_HDF5_SPARE] = "spare";
        }

        void Hdf5RdbSensorObject::convertToModifiedStructure(const RDB_SENSOR_OBJECT_t &data, const uint32_t frameNumber, Hdf5RdbSensorObject::ENRICHED_RDB_SENSOR_OBJECT &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.category = data.category;
            modifiedData.type = data.type;
            modifiedData.flags = data.flags;
            modifiedData.id = data.id;
            modifiedData.sensorId = data.sensorId;
            modifiedData.dist = data.dist;
            modifiedData.sensorPos_x = data.sensorPos.x;
            modifiedData.sensorPos_y = data.sensorPos.y;
            modifiedData.sensorPos_z = data.sensorPos.z;
            modifiedData.sensorPos_h = data.sensorPos.h;
            modifiedData.sensorPos_p = data.sensorPos.p;
            modifiedData.sensorPos_r = data.sensorPos.r;
            modifiedData.sensorPos_flags = data.sensorPos.flags;
            modifiedData.sensorPos_type = data.sensorPos.type;
            modifiedData.sensorPos_system = data.sensorPos.system;
            modifiedData.occlusion = data.occlusion;
            modifiedData.deltaLanePos = data.deltaLanePos;
            modifiedData.spare0[0] = data.spare0[0];
            modifiedData.spare0[1] = data.spare0[1];
            modifiedData.spare[0] = data.spare[0];
            modifiedData.spare[1] = data.spare[1];
            modifiedData.spare[2] = data.spare[2];
        }


}

