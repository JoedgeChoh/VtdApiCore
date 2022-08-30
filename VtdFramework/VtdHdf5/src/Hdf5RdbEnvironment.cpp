#include <VtdHdf5/Hdf5RdbEnvironment.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbEnvironment::Hdf5RdbEnvironment () : tableSize_(RDB_ENVIRONMENT_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbEnvironment::~Hdf5RdbEnvironment()
        {
            // have to be close memory leak
            H5Tclose(uintArray32_);
        }

        void Hdf5RdbEnvironment::initData()
        {
           dimsUInt32_[0] = sizeof(ENRICHED_RDB_ENVIRONMENT::spare1) / sizeof(uint32_t);
           uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);
            
           
           dstSize_ = sizeof(ENRICHED_RDB_ENVIRONMENT);

           dstOffset_[RDB_ENVIRONMENT_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, frameNumber);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_ENVIRONMENT::frameNumber);
           fieldType_[RDB_ENVIRONMENT_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_ENVIRONMENT_HDF5_FRAME_NUMBER] = "frameNumber";

           dstOffset_[RDB_ENVIRONMENT_HDF5_VISIBILITY] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, visibility);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_VISIBILITY] = sizeof(ENRICHED_RDB_ENVIRONMENT::visibility);
           fieldType_[RDB_ENVIRONMENT_HDF5_VISIBILITY] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_ENVIRONMENT_HDF5_VISIBILITY] = "visibility";

           dstOffset_[RDB_ENVIRONMENT_HDF5_TIME_OF_DATA] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, timeOfDay);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_TIME_OF_DATA] = sizeof(ENRICHED_RDB_ENVIRONMENT::timeOfDay);
           fieldType_[RDB_ENVIRONMENT_HDF5_TIME_OF_DATA] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_ENVIRONMENT_HDF5_TIME_OF_DATA] = "timeOfDay";

           dstOffset_[RDB_ENVIRONMENT_HDF5_BRIGHTNESS] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, brightness);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_BRIGHTNESS] = sizeof(ENRICHED_RDB_ENVIRONMENT::brightness);
           fieldType_[RDB_ENVIRONMENT_HDF5_BRIGHTNESS] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_ENVIRONMENT_HDF5_BRIGHTNESS] = "brightness";

           dstOffset_[RDB_ENVIRONMENT_HDF5_PRECIPITATION] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, precipitation);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_PRECIPITATION] = sizeof(ENRICHED_RDB_ENVIRONMENT::precipitation );
           fieldType_[RDB_ENVIRONMENT_HDF5_PRECIPITATION] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_ENVIRONMENT_HDF5_PRECIPITATION] = "precipitation";

           dstOffset_[RDB_ENVIRONMENT_HDF5_CLOUD_STATE] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, cloudState);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_CLOUD_STATE] = sizeof(ENRICHED_RDB_ENVIRONMENT::cloudState);
           fieldType_[RDB_ENVIRONMENT_HDF5_CLOUD_STATE] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_ENVIRONMENT_HDF5_CLOUD_STATE] = "cloudState";

           dstOffset_[RDB_ENVIRONMENT_HDF5_FLAGS] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, flags);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_FLAGS] = sizeof(ENRICHED_RDB_ENVIRONMENT::flags);
           fieldType_[RDB_ENVIRONMENT_HDF5_FLAGS] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_ENVIRONMENT_HDF5_FLAGS] = "flags";

           dstOffset_[RDB_ENVIRONMENT_HDF5_TEMPERATURE] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, temperature);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_TEMPERATURE] = sizeof(ENRICHED_RDB_ENVIRONMENT::temperature);
           fieldType_[RDB_ENVIRONMENT_HDF5_TEMPERATURE] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_ENVIRONMENT_HDF5_TEMPERATURE] = "temperature";

           dstOffset_[RDB_ENVIRONMENT_HDF5_DAY] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, day);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_DAY] = sizeof(ENRICHED_RDB_ENVIRONMENT::day);
           fieldType_[RDB_ENVIRONMENT_HDF5_DAY] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_ENVIRONMENT_HDF5_DAY] = "day";

           dstOffset_[RDB_ENVIRONMENT_HDF5_MONTH] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, month);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_MONTH] = sizeof(ENRICHED_RDB_ENVIRONMENT::month);
           fieldType_[RDB_ENVIRONMENT_HDF5_MONTH] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_ENVIRONMENT_HDF5_MONTH] = "month";

           dstOffset_[RDB_ENVIRONMENT_HDF5_YEAR] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, year);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_YEAR] = sizeof(ENRICHED_RDB_ENVIRONMENT::year);
           fieldType_[RDB_ENVIRONMENT_HDF5_YEAR] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_ENVIRONMENT_HDF5_YEAR] = "year";

           dstOffset_[RDB_ENVIRONMENT_HDF5_TIME_ZONE_MINUTE_WEST] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, timeZoneMinutesWest);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_TIME_ZONE_MINUTE_WEST] = sizeof(ENRICHED_RDB_ENVIRONMENT::timeZoneMinutesWest);
           fieldType_[RDB_ENVIRONMENT_HDF5_TIME_ZONE_MINUTE_WEST] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_ENVIRONMENT_HDF5_TIME_ZONE_MINUTE_WEST] = "timeZoneMinutesWest";

           dstOffset_[RDB_ENVIRONMENT_HDF5_SPARE2] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, spare2);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_SPARE2] = sizeof(ENRICHED_RDB_ENVIRONMENT::spare2);
           fieldType_[RDB_ENVIRONMENT_HDF5_SPARE2] = H5T_NATIVE_UINT16;
           fieldNames_[RDB_ENVIRONMENT_HDF5_SPARE2] = "spare2";

           dstOffset_[RDB_ENVIRONMENT_HDF5_SPARE1] = HOFFSET(ENRICHED_RDB_ENVIRONMENT, spare1);
           dstSizes_ [RDB_ENVIRONMENT_HDF5_SPARE1] = sizeof(ENRICHED_RDB_ENVIRONMENT::spare1);
           fieldType_[RDB_ENVIRONMENT_HDF5_SPARE1] = uintArray32_;
           fieldNames_[RDB_ENVIRONMENT_HDF5_SPARE1] = "spare1";
        }

        void Hdf5RdbEnvironment::convertToModifiedStructure(const RDB_ENVIRONMENT_t &data, const uint32_t frameNumber, Hdf5RdbEnvironment::ENRICHED_RDB_ENVIRONMENT &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.visibility = data.visibility;
            modifiedData.timeOfDay = data.timeOfDay;
            modifiedData.brightness = data.brightness;
            modifiedData.precipitation = data.precipitation;
            modifiedData.cloudState = data.cloudState;
            modifiedData.flags = data.flags;
            modifiedData.temperature = data.temperature;
            modifiedData.day = data.day;
            modifiedData.month = data.month;
            modifiedData.year = data.year;
            modifiedData.timeZoneMinutesWest = data.timeZoneMinutesWest;
            modifiedData.spare2 = data.spare2;
            modifiedData.frictionScale = data.frictionScale;
            modifiedData.spare1[0] = data.spare1[0];
            modifiedData.spare1[1] = data.spare1[1];
            modifiedData.spare1[2] = data.spare1[2];
            modifiedData.spare1[3] = data.spare1[3];
        }

 }

