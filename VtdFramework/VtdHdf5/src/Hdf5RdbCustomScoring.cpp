#include <VtdHdf5/Hdf5RdbCustomScoring.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbCustomScoring::Hdf5RdbCustomScoring () : tableSize_(RDB_CUSTOM_SCORING_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbCustomScoring::~Hdf5RdbCustomScoring()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
        }

        void Hdf5RdbCustomScoring::initData()
        {
           dimsUInt32_[0] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::spare) / sizeof(uint32_t);
           uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);
            
           dstSize_ = sizeof(ENRICHED_RDB_CUSTOM_SCORING);

           dstOffset_[RDB_CUSTOM_SCORING_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_CUSTOM_SCORING, frameNumber);
           dstSizes_ [RDB_CUSTOM_SCORING_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::frameNumber);
           fieldType_[RDB_CUSTOM_SCORING_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_CUSTOM_SCORING_HDF5_FRAME_NUMBER] = "frameNumber";

           dstOffset_[RDB_CUSTOM_SCORING_HDF5_PLAYER_ID] = HOFFSET(ENRICHED_RDB_CUSTOM_SCORING, playerId);
           dstSizes_ [RDB_CUSTOM_SCORING_HDF5_PLAYER_ID] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::playerId);
           fieldType_[RDB_CUSTOM_SCORING_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_CUSTOM_SCORING_HDF5_PLAYER_ID] = "playerId";

           dstOffset_[RDB_CUSTOM_SCORING_HDF5_PATH_S] = HOFFSET(ENRICHED_RDB_CUSTOM_SCORING, pathS);
           dstSizes_ [RDB_CUSTOM_SCORING_HDF5_PATH_S] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::pathS);
           fieldType_[RDB_CUSTOM_SCORING_HDF5_PATH_S] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CUSTOM_SCORING_HDF5_PATH_S] = "pathS";

           dstOffset_[RDB_CUSTOM_SCORING_HDF5_ROAD_S] = HOFFSET(ENRICHED_RDB_CUSTOM_SCORING, roadS);
           dstSizes_ [RDB_CUSTOM_SCORING_HDF5_ROAD_S] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::roadS);
           fieldType_[RDB_CUSTOM_SCORING_HDF5_ROAD_S] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CUSTOM_SCORING_HDF5_ROAD_S] = "roadS";

           dstOffset_[RDB_CUSTOM_SCORING_HDF5_FUEL_CURRENT] = HOFFSET(ENRICHED_RDB_CUSTOM_SCORING, fuelCurrent);
           dstSizes_ [RDB_CUSTOM_SCORING_HDF5_FUEL_CURRENT] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::fuelCurrent);
           fieldType_[RDB_CUSTOM_SCORING_HDF5_FUEL_CURRENT] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CUSTOM_SCORING_HDF5_FUEL_CURRENT] = "fuelCurrent";

           dstOffset_[RDB_CUSTOM_SCORING_HDF5_FUEL_AVERAGE] = HOFFSET(ENRICHED_RDB_CUSTOM_SCORING, fuelAverage);
           dstSizes_ [RDB_CUSTOM_SCORING_HDF5_FUEL_AVERAGE] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::fuelAverage);
           fieldType_[RDB_CUSTOM_SCORING_HDF5_FUEL_AVERAGE] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CUSTOM_SCORING_HDF5_FUEL_AVERAGE] = "fuelAverage";

           dstOffset_[RDB_CUSTOM_SCORING_HDF5_STATE_FLAGS] = HOFFSET(ENRICHED_RDB_CUSTOM_SCORING, stateFlags);
           dstSizes_ [RDB_CUSTOM_SCORING_HDF5_STATE_FLAGS] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::stateFlags);
           fieldType_[RDB_CUSTOM_SCORING_HDF5_STATE_FLAGS] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_CUSTOM_SCORING_HDF5_STATE_FLAGS] = "stateFlags";

           dstOffset_[RDB_CUSTOM_SCORING_HDF5_SLIP] = HOFFSET(ENRICHED_RDB_CUSTOM_SCORING, slip);
           dstSizes_ [RDB_CUSTOM_SCORING_HDF5_SLIP] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::slip);
           fieldType_[RDB_CUSTOM_SCORING_HDF5_SLIP] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_CUSTOM_SCORING_HDF5_SLIP] = "slip";

           dstOffset_[RDB_CUSTOM_SCORING_HDF5_SPARE] = HOFFSET(ENRICHED_RDB_CUSTOM_SCORING, spare);
           dstSizes_ [RDB_CUSTOM_SCORING_HDF5_SPARE] = sizeof(ENRICHED_RDB_CUSTOM_SCORING::spare);
           fieldType_[RDB_CUSTOM_SCORING_HDF5_SPARE] = uintArray32_;
           fieldNames_[RDB_CUSTOM_SCORING_HDF5_SPARE] = "spare";
        }

        void Hdf5RdbCustomScoring::convertToModifiedStructure(const RDB_CUSTOM_SCORING_t &data, const uint32_t frameNumber, Hdf5RdbCustomScoring::ENRICHED_RDB_CUSTOM_SCORING &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.playerId = data.playerId;
            modifiedData.pathS = data.pathS;
            modifiedData.roadS = data.roadS;
            modifiedData.fuelCurrent = data.fuelCurrent;
            modifiedData.fuelAverage = data.fuelAverage;
            modifiedData.stateFlags = data.stateFlags;
            modifiedData.slip = data.slip;
            modifiedData.spare[0] = data.spare[0];
            modifiedData.spare[1] = data.spare[1];
            modifiedData.spare[2] = data.spare[2];
            modifiedData.spare[3] = data.spare[3];
        }
}

