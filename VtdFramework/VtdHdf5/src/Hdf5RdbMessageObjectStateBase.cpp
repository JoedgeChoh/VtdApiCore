#include <VtdHdf5/Hdf5RdbMessageObjectStateBase.h>
#include <cstring>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageObjectStateBase::Hdf5RdbMessageObjectStateBase() : tableSize_(RDB_OBJECT_STATE_BASE_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageObjectStateBase::~Hdf5RdbMessageObjectStateBase()
        {
            H5Tclose(stringType1_);
        }

        void Hdf5RdbMessageObjectStateBase::initData()
        {
            stringType1_ = H5Tcopy(H5T_C_S1);

            H5Tset_size(stringType1_, RDB_SIZE_OBJECT_NAME);

            dstSize_ = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE);

            dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_FRAME_NUMBER] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, frameNumber);
            dstSizes_ [RDB_OBJECT_STATE_BASE_HDF5_FRAME_NUMBER] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::frameNumber);
            fieldType_[RDB_OBJECT_STATE_BASE_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_ID] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, id);
            dstSizes_ [RDB_OBJECT_STATE_BASE_HDF5_ID] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::id);
            fieldType_[RDB_OBJECT_STATE_BASE_HDF5_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_ID] = "id";

            dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_CATEGORY] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, category);
            dstSizes_ [RDB_OBJECT_STATE_BASE_HDF5_CATEGORY] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::category);
            fieldType_[RDB_OBJECT_STATE_BASE_HDF5_CATEGORY] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_CATEGORY] = "category";

            dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_TYPE] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, type);
            dstSizes_ [RDB_OBJECT_STATE_BASE_HDF5_TYPE] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::type);
            fieldType_[RDB_OBJECT_STATE_BASE_HDF5_TYPE] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_TYPE] = "type";

            dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_VIS_MASK] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, visMask);
            dstSizes_ [RDB_OBJECT_STATE_BASE_HDF5_VIS_MASK] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::visMask);
            fieldType_[RDB_OBJECT_STATE_BASE_HDF5_VIS_MASK] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_VIS_MASK] = "visMask";

            dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_NAME] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, name);
            dstSizes_ [RDB_OBJECT_STATE_BASE_HDF5_NAME] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::name);
            fieldType_[RDB_OBJECT_STATE_BASE_HDF5_NAME] = stringType1_;
            fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_NAME] = "name";

            dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_PARENT] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, parent);
            dstSizes_ [RDB_OBJECT_STATE_BASE_HDF5_PARENT] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::parent);
            fieldType_[RDB_OBJECT_STATE_BASE_HDF5_PARENT] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_PARENT] = "parent";

            dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_CFG_FLAGS] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, cfgFlags);
            dstSizes_ [RDB_OBJECT_STATE_BASE_HDF5_CFG_FLAGS] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::cfgFlags);
            fieldType_[RDB_OBJECT_STATE_BASE_HDF5_CFG_FLAGS] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_CFG_FLAGS] = "cfgFlags";

            dstOffset_[RDB_OBJECT_STATE_BASE_HDF5_CFG_MODEL_ID] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, cfgModelId);
            dstSizes_ [RDB_OBJECT_STATE_BASE_HDF5_CFG_MODEL_ID] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::cfgModelId);
            fieldType_[RDB_OBJECT_STATE_BASE_HDF5_CFG_MODEL_ID] = H5T_NATIVE_INT16;
            fieldNames_[RDB_OBJECT_STATE_BASE_HDF5_CFG_MODEL_ID] = "cfgModelId";

            dstOffset_[RDB_COORD_HDF5_X] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, pos_x);
            dstSizes_ [RDB_COORD_HDF5_X] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::pos_x);
            fieldType_[RDB_COORD_HDF5_X] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_COORD_HDF5_X] = "pos_x";

            dstOffset_[RDB_COORD_HDF5_Y] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, pos_y);
            dstSizes_ [RDB_COORD_HDF5_Y] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::pos_y);
            fieldType_[RDB_COORD_HDF5_Y] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_COORD_HDF5_Y] = "pos_y";

            dstOffset_[RDB_COORD_HDF5_Z] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, pos_z);
            dstSizes_ [RDB_COORD_HDF5_Z] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::pos_z);
            fieldType_[RDB_COORD_HDF5_Z] = H5T_NATIVE_DOUBLE;
            fieldNames_[RDB_COORD_HDF5_Z] = "pos_z";

            dstOffset_[RDB_COORD_HDF5_H] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, pos_h);
            dstSizes_ [RDB_COORD_HDF5_H] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::pos_h);
            fieldType_[RDB_COORD_HDF5_H] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_COORD_HDF5_H] = "pos_h";

            dstOffset_[RDB_COORD_HDF5_P] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, pos_p);
            dstSizes_ [RDB_COORD_HDF5_P] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::pos_p);
            fieldType_[RDB_COORD_HDF5_P] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_COORD_HDF5_P] = "pos_p";

            dstOffset_[RDB_COORD_HDF5_R] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, pos_r);
            dstSizes_ [RDB_COORD_HDF5_R] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::pos_r);
            fieldType_[RDB_COORD_HDF5_R] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_COORD_HDF5_R] = "pos_r";

            dstOffset_[RDB_COORD_HDF5_FLAGS] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, pos_flags);
            dstSizes_ [RDB_COORD_HDF5_FLAGS] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::pos_flags);
            fieldType_[RDB_COORD_HDF5_FLAGS] = H5T_NATIVE_INT8;
            fieldNames_[RDB_COORD_HDF5_FLAGS] = "pos_flags";

            dstOffset_[RDB_COORD_HDF5_TYPE] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, pos_type);
            dstSizes_ [RDB_COORD_HDF5_TYPE] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::pos_type);
            fieldType_[RDB_COORD_HDF5_TYPE] = H5T_NATIVE_INT8;
            fieldNames_[RDB_COORD_HDF5_TYPE] = "pos_type";

            dstOffset_[RDB_COORD_HDF5_SYSTEM] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, pos_system);
            dstSizes_ [RDB_COORD_HDF5_SYSTEM] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::pos_system);
            fieldType_[RDB_COORD_HDF5_SYSTEM] = H5T_NATIVE_INT16;
            fieldNames_[RDB_COORD_HDF5_SYSTEM] = "pos_system";

            dstOffset_[RDB_GEOMETRY_HDF5_DIM_X] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, geo_dimX);
            dstSizes_ [RDB_GEOMETRY_HDF5_DIM_X] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::geo_dimX);
            fieldType_[RDB_GEOMETRY_HDF5_DIM_X] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_DIM_X] = "geo_dimX";

            dstOffset_[RDB_GEOMETRY_HDF5_DIM_Y] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, geo_dimY);
            dstSizes_ [RDB_GEOMETRY_HDF5_DIM_Y] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::geo_dimY);
            fieldType_[RDB_GEOMETRY_HDF5_DIM_Y] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_DIM_Y] = "geo_dimY";

            dstOffset_[RDB_GEOMETRY_HDF5_DIM_Z] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, geo_dimZ);
            dstSizes_ [RDB_GEOMETRY_HDF5_DIM_Z] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::geo_dimZ);
            fieldType_[RDB_GEOMETRY_HDF5_DIM_Z] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_DIM_Z] = "geo_dimZ";

            dstOffset_[RDB_GEOMETRY_HDF5_OFF_X] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, geo_offX);
            dstSizes_ [RDB_GEOMETRY_HDF5_OFF_X] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::geo_offX);
            fieldType_[RDB_GEOMETRY_HDF5_OFF_X] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_OFF_X] = "geo_offX";

            dstOffset_[RDB_GEOMETRY_HDF5_OFF_Y] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, geo_offY);
            dstSizes_ [RDB_GEOMETRY_HDF5_OFF_Y] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::geo_offY);
            fieldType_[RDB_GEOMETRY_HDF5_OFF_Y] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_OFF_Y] = "geo_offY";

            dstOffset_[RDB_GEOMETRY_HDF5_OFF_Z] = HOFFSET(SIMPLE_RDB_OBJECT_STATE_BASE, geo_offZ);
            dstSizes_ [RDB_GEOMETRY_HDF5_OFF_Z] = sizeof(SIMPLE_RDB_OBJECT_STATE_BASE::geo_offZ);
            fieldType_[RDB_GEOMETRY_HDF5_OFF_Z] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_GEOMETRY_HDF5_OFF_Z] = "geo_offZ";
        }

        void Hdf5RdbMessageObjectStateBase::convertToModifiedStructure(const RDB_OBJECT_STATE_BASE_t& data, const uint32_t frameNumber, SIMPLE_RDB_OBJECT_STATE_BASE& modifiedData)
        {
            const RDB_COORD_t& pos = data.pos;
            const RDB_GEOMETRY_t& rdbGeometry = data.geo;

            // OBJECT STATE BASE
            modifiedData.frameNumber = frameNumber;
            modifiedData.id = data.id;
            modifiedData.category = data.category;
            modifiedData.type = data.type;
            modifiedData.visMask = data.visMask;
            modifiedData.parent = data.parent;
            modifiedData.cfgFlags = data.cfgFlags;
            modifiedData.cfgModelId = data.cfgModelId;
            std::memcpy(modifiedData.name, data.name, sizeof(Hdf5RdbMessageObjectStateBase::SIMPLE_RDB_OBJECT_STATE_BASE::name));

            // OBJECT STATE BASE POSITION
            modifiedData.pos_x = pos.x;
            modifiedData.pos_y = pos.y;
            modifiedData.pos_z = pos.z;
            modifiedData.pos_h = pos.h;
            modifiedData.pos_p = pos.p;
            modifiedData.pos_r = pos.r;
            modifiedData.pos_flags = pos.flags;
            modifiedData.pos_type = pos.type;
            modifiedData.pos_system = pos.system;

            // OBJECT STATE BASE GEOMETRY
            modifiedData.geo_dimX = rdbGeometry.dimX;
            modifiedData.geo_dimY = rdbGeometry.dimY;
            modifiedData.geo_dimZ = rdbGeometry.dimZ;
            modifiedData.geo_offX = rdbGeometry.offX;
            modifiedData.geo_offY = rdbGeometry.offY;
            modifiedData.geo_offZ = rdbGeometry.offZ;
        }
}

