#include <VtdHdf5/Hdf5RdbSensorState.h>

#include <cstring>

namespace RdbToHdf5Writer
{
        Hdf5RdbSensorState::Hdf5RdbSensorState() : tableSize_(RDB_SENSOR_STATE_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbSensorState::~Hdf5RdbSensorState()
        {
            // have to be close memory leak
            H5Tclose(floatArray_);
            H5Tclose(intArray32_);
            H5Tclose(stringType_);
        }

        void Hdf5RdbSensorState::initData()
        {
            dimsInt32_[0] = sizeof(SIMPLE_RDB_SENSOR_STATE::spare) / sizeof(int32_t);
            intArray32_ = H5Tarray_create(H5T_NATIVE_INT32, 1, dimsInt32_);
            
            dimsFloat_[0] = sizeof(SIMPLE_RDB_SENSOR_STATE::fovOffHV) / sizeof(float);
            floatArray_ = H5Tarray_create(H5T_NATIVE_FLOAT, 1, dimsFloat_);
            
            stringType_ = H5Tcopy(H5T_C_S1);
            H5Tset_size(stringType_, RDB_SIZE_OBJECT_NAME);

            dstSize_ = sizeof(SIMPLE_RDB_SENSOR_STATE);

            dstOffset_[RDB_SENSOR_STATE_HDF5_FRAME_NUMBER] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, frameNumber);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_FRAME_NUMBER] = sizeof(SIMPLE_RDB_SENSOR_STATE::frameNumber);
            fieldType_[RDB_SENSOR_STATE_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_SENSOR_STATE_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_SENSOR_STATE_HDF5_ID] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, id);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_ID] = sizeof(SIMPLE_RDB_SENSOR_STATE::id);
            fieldType_[RDB_SENSOR_STATE_HDF5_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_SENSOR_STATE_HDF5_ID] = "id";

            dstOffset_[RDB_SENSOR_STATE_HDF5_TYPE] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, type);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_TYPE] = sizeof(SIMPLE_RDB_SENSOR_STATE::type);
            fieldType_[RDB_SENSOR_STATE_HDF5_TYPE] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_SENSOR_STATE_HDF5_TYPE] = "type";

            dstOffset_[RDB_SENSOR_STATE_HDF5_HOST_CATEGORY] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, hostCategory);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_HOST_CATEGORY] = sizeof(SIMPLE_RDB_SENSOR_STATE::hostCategory);
            fieldType_[RDB_SENSOR_STATE_HDF5_HOST_CATEGORY] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_SENSOR_STATE_HDF5_HOST_CATEGORY] = "hostCategory";

            dstOffset_[RDB_SENSOR_STATE_HDF5_SPARE0] = HOFFSET(SIMPLE_RDB_SENSOR_STATE,spare0);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_SPARE0] = sizeof(SIMPLE_RDB_SENSOR_STATE::spare0);
            fieldType_[RDB_SENSOR_STATE_HDF5_SPARE0] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_SENSOR_STATE_HDF5_SPARE0] = "spare0";

            dstOffset_[RDB_SENSOR_STATE_HDF5_HOST_ID] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, hostId);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_HOST_ID] = sizeof(SIMPLE_RDB_SENSOR_STATE::hostId);
            fieldType_[RDB_SENSOR_STATE_HDF5_HOST_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_SENSOR_STATE_HDF5_HOST_ID] = "hostId";

            dstOffset_[RDB_SENSOR_STATE_HDF5_NAME] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, name);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_NAME] = sizeof(SIMPLE_RDB_SENSOR_STATE::name);
            fieldType_[RDB_SENSOR_STATE_HDF5_NAME] = stringType_;
            fieldNames_[RDB_SENSOR_STATE_HDF5_NAME] = "name";

            dstOffset_[RDB_SENSOR_STATE_HDF5_FOV_HV] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, fovHV);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_FOV_HV] = sizeof(SIMPLE_RDB_SENSOR_STATE::fovHV);
            fieldType_[RDB_SENSOR_STATE_HDF5_FOV_HV] = floatArray_;
            fieldNames_[RDB_SENSOR_STATE_HDF5_FOV_HV] = "fovHV";

            dstOffset_[RDB_SENSOR_STATE_HDF5_CLIP_NF] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, clipNF);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_CLIP_NF] = sizeof(SIMPLE_RDB_SENSOR_STATE::clipNF);
            fieldType_[RDB_SENSOR_STATE_HDF5_CLIP_NF] = floatArray_;
            fieldNames_[RDB_SENSOR_STATE_HDF5_CLIP_NF] = "clipNF";

            dstOffset_[RDB_SENSOR_STATE_HDF5_FOV_OFF_HV] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, fovOffHV);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_FOV_OFF_HV] = sizeof(SIMPLE_RDB_SENSOR_STATE::fovOffHV);
            fieldType_[RDB_SENSOR_STATE_HDF5_FOV_OFF_HV] = floatArray_;
            fieldNames_[RDB_SENSOR_STATE_HDF5_FOV_OFF_HV] = "fovOffHV";

            dstOffset_[RDB_SENSOR_STATE_HDF5_SPARE] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, spare);
            dstSizes_ [RDB_SENSOR_STATE_HDF5_SPARE] = sizeof(SIMPLE_RDB_SENSOR_STATE::spare);
            fieldType_[RDB_SENSOR_STATE_HDF5_SPARE] = intArray32_;
            fieldNames_[RDB_SENSOR_STATE_HDF5_SPARE] = "spare";

            dstOffset_[RDB_SENSOR_STATE_POS_HDF5_X] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, pos_x);
            dstSizes_ [RDB_SENSOR_STATE_POS_HDF5_X] = sizeof(SIMPLE_RDB_SENSOR_STATE::pos_x);
            fieldType_[RDB_SENSOR_STATE_POS_HDF5_X] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_SENSOR_STATE_POS_HDF5_X] = "pos_x";

            dstOffset_[RDB_SENSOR_STATE_POS_HDF5_Y] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, pos_y);
            dstSizes_ [RDB_SENSOR_STATE_POS_HDF5_Y] = sizeof(SIMPLE_RDB_SENSOR_STATE::pos_y);
            fieldType_[RDB_SENSOR_STATE_POS_HDF5_Y] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_SENSOR_STATE_POS_HDF5_Y] = "pos_y";

            dstOffset_[RDB_SENSOR_STATE_POS_HDF5_Z] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, pos_z);
            dstSizes_ [RDB_SENSOR_STATE_POS_HDF5_Z] = sizeof(SIMPLE_RDB_SENSOR_STATE::pos_z);
            fieldType_[RDB_SENSOR_STATE_POS_HDF5_Z] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_SENSOR_STATE_POS_HDF5_Z] = "pos_z";

            dstOffset_[RDB_SENSOR_STATE_POS_HDF5_H] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, pos_h);
            dstSizes_ [RDB_SENSOR_STATE_POS_HDF5_H] = sizeof(SIMPLE_RDB_SENSOR_STATE::pos_h);
            fieldType_[RDB_SENSOR_STATE_POS_HDF5_H] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_SENSOR_STATE_POS_HDF5_H] = "pos_h";

            dstOffset_[RDB_SENSOR_STATE_POS_HDF5_P] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, pos_p);
            dstSizes_ [RDB_SENSOR_STATE_POS_HDF5_P] = sizeof(SIMPLE_RDB_SENSOR_STATE::pos_p);
            fieldType_[RDB_SENSOR_STATE_POS_HDF5_P] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_SENSOR_STATE_POS_HDF5_P] = "pos_p";

            dstOffset_[RDB_SENSOR_STATE_POS_HDF5_R] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, pos_r);
            dstSizes_ [RDB_SENSOR_STATE_POS_HDF5_R] = sizeof(SIMPLE_RDB_SENSOR_STATE::pos_r);
            fieldType_[RDB_SENSOR_STATE_POS_HDF5_R] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_SENSOR_STATE_POS_HDF5_R] = "pos_r";

            dstOffset_[RDB_SENSOR_STATE_POS_HDF5_FLAGS] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, pos_flags);
            dstSizes_ [RDB_SENSOR_STATE_POS_HDF5_FLAGS] = sizeof(SIMPLE_RDB_SENSOR_STATE::pos_flags);
            fieldType_[RDB_SENSOR_STATE_POS_HDF5_FLAGS] = H5T_NATIVE_INT8;
            fieldNames_[RDB_SENSOR_STATE_POS_HDF5_FLAGS] = "pos_flags";

            dstOffset_[RDB_SENSOR_STATE_POS_HDF5_TYPE] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, pos_type);
            dstSizes_ [RDB_SENSOR_STATE_POS_HDF5_TYPE] = sizeof(SIMPLE_RDB_SENSOR_STATE::pos_type);
            fieldType_[RDB_SENSOR_STATE_POS_HDF5_TYPE] = H5T_NATIVE_INT8;
            fieldNames_[RDB_SENSOR_STATE_POS_HDF5_TYPE] = "pos_type";

            dstOffset_[RDB_SENSOR_STATE_POS_HDF5_SYSTEM] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, pos_system);
            dstSizes_ [RDB_SENSOR_STATE_POS_HDF5_SYSTEM] = sizeof(SIMPLE_RDB_SENSOR_STATE::pos_system);
            fieldType_[RDB_SENSOR_STATE_POS_HDF5_SYSTEM] = H5T_NATIVE_INT16;
            fieldNames_[RDB_SENSOR_STATE_POS_HDF5_SYSTEM] = "pos_system";

            dstOffset_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_X] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, originCoordSys_x);
            dstSizes_ [RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_X] = sizeof(SIMPLE_RDB_SENSOR_STATE::originCoordSys_x);
            fieldType_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_X] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_X] = "originCoordSys_x";

            dstOffset_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Y] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, originCoordSys_y);
            dstSizes_ [RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Y] = sizeof(SIMPLE_RDB_SENSOR_STATE::originCoordSys_y);
            fieldType_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Y] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Y] = "originCoordSys_y";

            dstOffset_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Z] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, originCoordSys_z);
            dstSizes_ [RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Z] = sizeof(SIMPLE_RDB_SENSOR_STATE::originCoordSys_z);
            fieldType_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Z] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_Z] = "originCoordSys_z";

            dstOffset_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_H] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, originCoordSys_h);
            dstSizes_ [RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_H] = sizeof(SIMPLE_RDB_SENSOR_STATE::originCoordSys_h);
            fieldType_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_H] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_H] = "originCoordSys_h";

            dstOffset_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_P] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, originCoordSys_p);
            dstSizes_ [RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_P] = sizeof(SIMPLE_RDB_SENSOR_STATE::originCoordSys_p);
            fieldType_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_P] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_P] = "originCoordSys_p";

            dstOffset_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_R] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, originCoordSys_r);
            dstSizes_ [RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_R] = sizeof(SIMPLE_RDB_SENSOR_STATE::originCoordSys_r);
            fieldType_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_R] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_R] = "originCoordSys_r";

            dstOffset_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_FLAGS] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, originCoordSys_flags);
            dstSizes_ [RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_FLAGS] = sizeof(SIMPLE_RDB_SENSOR_STATE::originCoordSys_flags);
            fieldType_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_FLAGS] = H5T_NATIVE_INT8;
            fieldNames_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_FLAGS] = "originCoordSys_flags";

            dstOffset_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_TYPE] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, originCoordSys_type);
            dstSizes_ [RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_TYPE] = sizeof(SIMPLE_RDB_SENSOR_STATE::originCoordSys_type);
            fieldType_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_TYPE] = H5T_NATIVE_INT8;
            fieldNames_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_TYPE] = "originCoordSys_type";

            dstOffset_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_SYSTEM] = HOFFSET(SIMPLE_RDB_SENSOR_STATE, originCoordSys_system);
            dstSizes_ [RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_SYSTEM] = sizeof(SIMPLE_RDB_SENSOR_STATE::originCoordSys_system);
            fieldType_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_SYSTEM] = H5T_NATIVE_INT16;
            fieldNames_[RDB_SENSOR_STATE_ORIGIN_COORD_SYS_HDF5_SYSTEM] = "originCoordSys_system";

        }

        void Hdf5RdbSensorState::convertToModifiedStructure(const RDB_SENSOR_STATE_t &data, const uint32_t frameNumber, Hdf5RdbSensorState::SIMPLE_RDB_SENSOR_STATE &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.id = data.id;
            modifiedData.type = data.type;
            modifiedData.hostCategory = data.hostCategory;
            modifiedData.hostId = data.hostId;
            modifiedData.spare0 = data.spare0;
            std::memcpy(modifiedData.clipNF, data.clipNF, sizeof(Hdf5RdbSensorState::SIMPLE_RDB_SENSOR_STATE::clipNF));
            std::memcpy(modifiedData.fovHV, data.fovHV, sizeof(Hdf5RdbSensorState::SIMPLE_RDB_SENSOR_STATE::fovHV));
            std::memcpy(modifiedData.fovOffHV, data.fovOffHV, sizeof(Hdf5RdbSensorState::SIMPLE_RDB_SENSOR_STATE::fovOffHV));
            std::memcpy(modifiedData.spare, data.spare, sizeof(Hdf5RdbSensorState::SIMPLE_RDB_SENSOR_STATE::spare));
            std::memcpy(modifiedData.name, data.name, sizeof(Hdf5RdbSensorState::SIMPLE_RDB_SENSOR_STATE::name));

            // POSITION
            const RDB_COORD_t* pos = &(data.pos);
            modifiedData.pos_x = pos->x;
            modifiedData.pos_y = pos->y;
            modifiedData.pos_z = pos->z;
            modifiedData.pos_h = pos->h;
            modifiedData.pos_p = pos->p;
            modifiedData.pos_r = pos->r;
            modifiedData.pos_flags = pos->flags;
            modifiedData.pos_type = pos->type;
            modifiedData.pos_system = pos->system;

            // COORD ORIGIN
            const RDB_COORD_t* originCoord = &(data.originCoordSys);
            modifiedData.originCoordSys_x = originCoord->x;
            modifiedData.originCoordSys_y = originCoord->y;
            modifiedData.originCoordSys_z = originCoord->z;
            modifiedData.originCoordSys_h = originCoord->h;
            modifiedData.originCoordSys_p = originCoord->p;
            modifiedData.originCoordSys_r = originCoord->r;
            modifiedData.originCoordSys_flags = originCoord->flags;
            modifiedData.originCoordSys_type = originCoord->type;
            modifiedData.originCoordSys_system = originCoord->system;
        }

}

