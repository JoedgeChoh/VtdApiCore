#include <VtdHdf5/Hdf5RdbMessageWheelExt.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbMessageWheelExt::Hdf5RdbMessageWheelExt() : tableSize_(RDB_WHEEL_EXT_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbMessageWheelExt::~Hdf5RdbMessageWheelExt()
        {
            // have to be close memory leak
            H5Tclose(floatArray_);
            H5Tclose(uintArray32_);
        }

        void Hdf5RdbMessageWheelExt::initData()
        {
            dimsFloat_[0] = sizeof(ENRICHED_RDB_WHEEL_EXT::forceTireWheelXYZ) / sizeof(float);
            dimsUInt32_[0] = sizeof(ENRICHED_RDB_WHEEL_EXT::spare2) / sizeof(uint32_t);
            
            floatArray_ = H5Tarray_create(H5T_NATIVE_FLOAT, 1, dimsFloat_);
            uintArray32_ = H5Tarray_create(H5T_NATIVE_UINT32, 1, dimsUInt32_);

            dstSize_ = sizeof(ENRICHED_RDB_WHEEL_EXT);

            dstOffset_[RDB_WHEEL_EXT_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, frameNumber);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_WHEEL_EXT::frameNumber);
            fieldType_[RDB_WHEEL_EXT_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
            fieldNames_[RDB_WHEEL_EXT_HDF5_FRAME_NUMBER] = "frameNumber";

            dstOffset_[RDB_WHEEL_EXT_HDF5_V_ANGULAR] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, vAngular);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_V_ANGULAR] = sizeof(ENRICHED_RDB_WHEEL_EXT::vAngular);
            fieldType_[RDB_WHEEL_EXT_HDF5_V_ANGULAR] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_EXT_HDF5_V_ANGULAR] = "vAngular";

            dstOffset_[RDB_WHEEL_EXT_HDF5_FORCE_Z] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, forceZ);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_FORCE_Z] = sizeof(ENRICHED_RDB_WHEEL_EXT::forceZ);
            fieldType_[RDB_WHEEL_EXT_HDF5_FORCE_Z] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_EXT_HDF5_FORCE_Z] = "forceZ";

            dstOffset_[RDB_WHEEL_EXT_HDF5_FORCE_LAT] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, forceLat);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_FORCE_LAT] = sizeof(ENRICHED_RDB_WHEEL_EXT::forceLat);
            fieldType_[RDB_WHEEL_EXT_HDF5_FORCE_LAT] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_EXT_HDF5_FORCE_LAT] = "forceLat";

            dstOffset_[RDB_WHEEL_EXT_HDF5_FORCE_LONG] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, forceLong);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_FORCE_LONG] = sizeof(ENRICHED_RDB_WHEEL_EXT::forceLong);
            fieldType_[RDB_WHEEL_EXT_HDF5_FORCE_LONG] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_EXT_HDF5_FORCE_LONG] = "forceLong";

            dstOffset_[RDB_WHEEL_EXT_HDF5_FORCE_TIRE_WHEEL_XYZ] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, forceTireWheelXYZ);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_FORCE_TIRE_WHEEL_XYZ] = sizeof(ENRICHED_RDB_WHEEL_EXT::forceTireWheelXYZ);
            fieldType_[RDB_WHEEL_EXT_HDF5_FORCE_TIRE_WHEEL_XYZ] = floatArray_;
            fieldNames_[RDB_WHEEL_EXT_HDF5_FORCE_TIRE_WHEEL_XYZ] = "forceTireWheelXYZ";

            dstOffset_[RDB_WHEEL_EXT_HDF5_RADIUS_DYNAMIC] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, radiusDynamic);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_RADIUS_DYNAMIC] = sizeof(ENRICHED_RDB_WHEEL_EXT::radiusDynamic);
            fieldType_[RDB_WHEEL_EXT_HDF5_RADIUS_DYNAMIC] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_EXT_HDF5_RADIUS_DYNAMIC] = "radiusDynamic";

            dstOffset_[RDB_WHEEL_EXT_HDF5_BRAKE_PRESSURE] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, brakePressure);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_BRAKE_PRESSURE] = sizeof(ENRICHED_RDB_WHEEL_EXT::brakePressure);
            fieldType_[RDB_WHEEL_EXT_HDF5_BRAKE_PRESSURE] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_EXT_HDF5_BRAKE_PRESSURE] = "brakePressure";

            dstOffset_[RDB_WHEEL_EXT_HDF5_TORQUE_DRIVE_SHARF] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, torqueDriveShaft);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_TORQUE_DRIVE_SHARF] = sizeof(ENRICHED_RDB_WHEEL_EXT::torqueDriveShaft);
            fieldType_[RDB_WHEEL_EXT_HDF5_TORQUE_DRIVE_SHARF] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_EXT_HDF5_TORQUE_DRIVE_SHARF] = "torqueDriveShaft";

            dstOffset_[RDB_WHEEL_EXT_HDF5_DAMPER_SPEED] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, damperSpeed);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_DAMPER_SPEED] = sizeof(ENRICHED_RDB_WHEEL_EXT::damperSpeed);
            fieldType_[RDB_WHEEL_EXT_HDF5_DAMPER_SPEED] = H5T_NATIVE_FLOAT;
            fieldNames_[RDB_WHEEL_EXT_HDF5_DAMPER_SPEED] = "damperSpeed";

            dstOffset_[RDB_WHEEL_EXT_HDF5_FORCE_TIRE_WHEEL_XYZ] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, forceTireWheelXYZ);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_FORCE_TIRE_WHEEL_XYZ] = sizeof(ENRICHED_RDB_WHEEL_EXT::forceTireWheelXYZ);
            fieldType_[RDB_WHEEL_EXT_HDF5_FORCE_TIRE_WHEEL_XYZ] = floatArray_;
            fieldNames_[RDB_WHEEL_EXT_HDF5_FORCE_TIRE_WHEEL_XYZ] = "forceTireWheelXYZ";

            dstOffset_[RDB_WHEEL_EXT_HDF5_SPARE2] = HOFFSET(ENRICHED_RDB_WHEEL_EXT, spare2);
            dstSizes_ [RDB_WHEEL_EXT_HDF5_SPARE2] = sizeof(ENRICHED_RDB_WHEEL_EXT::spare2);
            fieldType_[RDB_WHEEL_EXT_HDF5_SPARE2] = uintArray32_;
            fieldNames_[RDB_WHEEL_EXT_HDF5_SPARE2] = "spare2";
        }

        void Hdf5RdbMessageWheelExt::convertToModifiedStructure(const RDB_WHEEL_EXT_t &data, const uint32_t frameNumber, Hdf5RdbMessageWheelExt::ENRICHED_RDB_WHEEL_EXT &modifiedData)
        {
            modifiedData.frameNumber = frameNumber;
            modifiedData.vAngular = data.vAngular;
            modifiedData.forceZ = data.forceZ;
            modifiedData.forceLat = data.forceLat;
            modifiedData.forceLong = data.forceLong;
            modifiedData.forceTireWheelXYZ[0] = data.forceTireWheelXYZ[0];
            modifiedData.forceTireWheelXYZ[1] = data.forceTireWheelXYZ[1];
            modifiedData.forceTireWheelXYZ[2] = data.forceTireWheelXYZ[2];
            modifiedData.radiusDynamic = data.radiusDynamic;
            modifiedData.brakePressure = data.brakePressure;
            modifiedData.torqueDriveShaft = data.torqueDriveShaft;
            modifiedData.damperSpeed = data.damperSpeed;
            modifiedData.spare2[0] = data.spare2[0];
            modifiedData.spare2[1] = data.spare2[1];
            modifiedData.spare2[2] = data.spare2[2];
            modifiedData.spare2[3] = data.spare2[3];
        }
}

