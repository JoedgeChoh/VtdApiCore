#include <VtdHdf5/Hdf5RdbMessageObjectCfg.h>

#include <cstring>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageObjectCfg::Hdf5RdbMessageObjectCfg() : tableSize_(RDB_OBJECT_CFG_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageObjectCfg::~Hdf5RdbMessageObjectCfg()
        {
            H5Tclose(stringType1_);
            H5Tclose(stringType2_);
        }

        void Hdf5RdbMessageObjectCfg::initData()
        {
            
            stringType1_ = H5Tcopy(H5T_C_S1);
            stringType2_ = H5Tcopy(H5T_C_S1);

            H5Tset_size(stringType1_, RDB_SIZE_OBJECT_NAME);
            H5Tset_size(stringType2_, RDB_SIZE_FILENAME);

            dstSize_ = sizeof(ENRICHED_RDB_OBJECT_CFG);

            dstOffset_[RDB_OBJECT_CFG_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, frameNumber);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_OBJECT_CFG::frameNumber);
            fieldType_[RDB_OBJECT_CFG_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_OBJECT_CFG_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_OBJECT_CFG_HDF5_ID] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, id);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_ID] = sizeof(ENRICHED_RDB_OBJECT_CFG::id);
            fieldType_[RDB_OBJECT_CFG_HDF5_ID] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_OBJECT_CFG_HDF5_ID] = "id";

            dstOffset_[RDB_OBJECT_CFG_HDF5_CATEGORY] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, category);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_CATEGORY] = sizeof(ENRICHED_RDB_OBJECT_CFG::category);
            fieldType_[RDB_OBJECT_CFG_HDF5_CATEGORY] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_OBJECT_CFG_HDF5_CATEGORY] = "category";

            dstOffset_[RDB_OBJECT_CFG_HDF5_TYPE] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, type);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_TYPE] = sizeof(ENRICHED_RDB_OBJECT_CFG::type);
            fieldType_[RDB_OBJECT_CFG_HDF5_TYPE] = H5T_NATIVE_UINT8;
            fieldNames_[RDB_OBJECT_CFG_HDF5_TYPE] = "type";

            dstOffset_[RDB_OBJECT_CFG_HDF5_MODEL_ID] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, modelId);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_MODEL_ID] = sizeof(ENRICHED_RDB_OBJECT_CFG::modelId);
            fieldType_[RDB_OBJECT_CFG_HDF5_MODEL_ID] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_OBJECT_CFG_HDF5_MODEL_ID] = "modelId";

            dstOffset_[RDB_OBJECT_CFG_HDF5_NAME] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, name);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_NAME] = sizeof(ENRICHED_RDB_OBJECT_CFG::name);
            fieldType_[RDB_OBJECT_CFG_HDF5_NAME] = stringType1_;
            fieldNames_[RDB_OBJECT_CFG_HDF5_NAME] = "name";

            dstOffset_[RDB_OBJECT_CFG_HDF5_MODEL_NAME] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, modelName);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_MODEL_NAME] = sizeof(ENRICHED_RDB_OBJECT_CFG::modelName);
            fieldType_[RDB_OBJECT_CFG_HDF5_MODEL_NAME] = stringType1_;
            fieldNames_[RDB_OBJECT_CFG_HDF5_MODEL_NAME] = "modelName";

            dstOffset_[RDB_OBJECT_CFG_HDF5_FILE_NAME] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, fileName);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_FILE_NAME] = sizeof(ENRICHED_RDB_OBJECT_CFG::fileName);
            fieldType_[RDB_OBJECT_CFG_HDF5_FILE_NAME] = stringType2_;
            fieldNames_[RDB_OBJECT_CFG_HDF5_FILE_NAME] = "fileName";

            dstOffset_[RDB_OBJECT_CFG_HDF5_FLAGS] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, flags);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_FLAGS] = sizeof(ENRICHED_RDB_OBJECT_CFG::flags);
            fieldType_[RDB_OBJECT_CFG_HDF5_FLAGS] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_OBJECT_CFG_HDF5_FLAGS] = "flags";

            dstOffset_[RDB_OBJECT_CFG_HDF5_SPARE0] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, spare0);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_SPARE0] = sizeof(ENRICHED_RDB_OBJECT_CFG::spare0);
            fieldType_[RDB_OBJECT_CFG_HDF5_SPARE0] = H5T_NATIVE_UINT16;
            fieldNames_[RDB_OBJECT_CFG_HDF5_SPARE0] = "spare0";

            dstOffset_[RDB_OBJECT_CFG_HDF5_SPARE1] = HOFFSET(ENRICHED_RDB_OBJECT_CFG, spare1);
            dstSizes_ [RDB_OBJECT_CFG_HDF5_SPARE1] = sizeof(ENRICHED_RDB_OBJECT_CFG::spare1);
            fieldType_[RDB_OBJECT_CFG_HDF5_SPARE1] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_OBJECT_CFG_HDF5_SPARE1] = "spare1";
        }

        void Hdf5RdbMessageObjectCfg::convertToModifiedStructure(const RDB_OBJECT_CFG_t &data, const uint32_t frameNumber, Hdf5RdbMessageObjectCfg::ENRICHED_RDB_OBJECT_CFG &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.id = data.id;
            modifiedData.category = data.category;
            modifiedData.type = data.type;
            modifiedData.modelId = data.modelId;
            modifiedData.flags = data.flags;
            modifiedData.spare0 = data.spare0;
            modifiedData.spare1 = data.spare1;
            std::memcpy(modifiedData.name, data.name, sizeof(Hdf5RdbMessageObjectCfg::ENRICHED_RDB_OBJECT_CFG::name));
            std::memcpy(modifiedData.modelName, data.modelName, sizeof(Hdf5RdbMessageObjectCfg::ENRICHED_RDB_OBJECT_CFG::modelName));
            std::memcpy(modifiedData.fileName, data.fileName, sizeof(Hdf5RdbMessageObjectCfg::ENRICHED_RDB_OBJECT_CFG::fileName));
        }
}

