#include <VtdHdf5/Hdf5RdbDriverCtrl.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbDriverCtrl::Hdf5RdbDriverCtrl() : tableSize_(RDB_DRIVER_CTRL_HDF5_NDATA)
        {
            this->initData();
        }

        Hdf5RdbDriverCtrl::~Hdf5RdbDriverCtrl()
        {
            // have to be close memory leak
            H5Tclose(uintArray8_);
        }

        void Hdf5RdbDriverCtrl::initData()
        {
           dimsUInt8_[0] = sizeof(ENRICHED_RDB_DRIVER_CTRL::spare0) / sizeof(uint8_t);
           uintArray8_ = H5Tarray_create(H5T_NATIVE_UINT8, 1, dimsUInt8_);
            
           dstSize_ = sizeof(ENRICHED_RDB_DRIVER_CTRL);

           dstOffset_[RDB_DRIVER_CTRL_HDF5_FRAME_NUMBER] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, frameNumber);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_FRAME_NUMBER] = sizeof(ENRICHED_RDB_DRIVER_CTRL::frameNumber);
           fieldType_[RDB_DRIVER_CTRL_HDF5_FRAME_NUMBER] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_FRAME_NUMBER] = "frameNumber";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_PLAYER_ID] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, playerId);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_PLAYER_ID] = sizeof(ENRICHED_RDB_DRIVER_CTRL::playerId);
           fieldType_[RDB_DRIVER_CTRL_HDF5_PLAYER_ID] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_PLAYER_ID] = "playerId";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_STEERING_WHEEL] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, steeringWheel);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_STEERING_WHEEL] = sizeof(ENRICHED_RDB_DRIVER_CTRL::steeringWheel);
           fieldType_[RDB_DRIVER_CTRL_HDF5_STEERING_WHEEL] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_STEERING_WHEEL] = "steeringWheel";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_STEERING_SPEED] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, steeringSpeed);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_STEERING_SPEED] = sizeof(ENRICHED_RDB_DRIVER_CTRL::steeringSpeed);
           fieldType_[RDB_DRIVER_CTRL_HDF5_STEERING_SPEED] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_STEERING_SPEED] = "steeringSpeed";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_THROTTLE_PEDAL] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, throttlePedal);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_THROTTLE_PEDAL] = sizeof(ENRICHED_RDB_DRIVER_CTRL::throttlePedal);
           fieldType_[RDB_DRIVER_CTRL_HDF5_THROTTLE_PEDAL] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_THROTTLE_PEDAL] = "throttlePedal";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_BRAKE_PEDAL] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, brakePedal);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_BRAKE_PEDAL] = sizeof(ENRICHED_RDB_DRIVER_CTRL::brakePedal);
           fieldType_[RDB_DRIVER_CTRL_HDF5_BRAKE_PEDAL] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_BRAKE_PEDAL] = "brakePedal";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_CLUTCH_PEDAL] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, clutchPedal);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_CLUTCH_PEDAL] = sizeof(ENRICHED_RDB_DRIVER_CTRL::clutchPedal);
           fieldType_[RDB_DRIVER_CTRL_HDF5_CLUTCH_PEDAL] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_CLUTCH_PEDAL] = "clutchPedal";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_ACCEL_TGT] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, accelTgt);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_ACCEL_TGT] = sizeof(ENRICHED_RDB_DRIVER_CTRL::accelTgt);
           fieldType_[RDB_DRIVER_CTRL_HDF5_ACCEL_TGT] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_ACCEL_TGT] = "accelTgt";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_STEERING_TGT] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, steeringTgt);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_STEERING_TGT] = sizeof(ENRICHED_RDB_DRIVER_CTRL::steeringTgt);
           fieldType_[RDB_DRIVER_CTRL_HDF5_STEERING_TGT] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_STEERING_TGT] = "steeringTgt";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_CURVATURE_TGT] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, curvatureTgt);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_CURVATURE_TGT] = sizeof(ENRICHED_RDB_DRIVER_CTRL::curvatureTgt);
           fieldType_[RDB_DRIVER_CTRL_HDF5_CURVATURE_TGT] = H5T_NATIVE_DOUBLE;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_CURVATURE_TGT] = "curvatureTgt";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_STEERING_TORQUE] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, steeringTorque);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_STEERING_TORQUE] = sizeof(ENRICHED_RDB_DRIVER_CTRL::steeringTorque);
           fieldType_[RDB_DRIVER_CTRL_HDF5_STEERING_TORQUE] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_STEERING_TORQUE] = "steeringTorque";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_ENGINE_TORQUE_TGT] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, engineTorqueTgt);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_ENGINE_TORQUE_TGT] = sizeof(ENRICHED_RDB_DRIVER_CTRL::engineTorqueTgt);
           fieldType_[RDB_DRIVER_CTRL_HDF5_ENGINE_TORQUE_TGT] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_ENGINE_TORQUE_TGT] = "engineTorqueTgt";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_SPEED_TGT] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, speedTgt);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_SPEED_TGT] = sizeof(ENRICHED_RDB_DRIVER_CTRL::speedTgt);
           fieldType_[RDB_DRIVER_CTRL_HDF5_SPEED_TGT] = H5T_NATIVE_FLOAT;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_SPEED_TGT] = "speedTgt";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_GEAR] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, gear);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_GEAR] = sizeof(ENRICHED_RDB_DRIVER_CTRL::gear);
           fieldType_[RDB_DRIVER_CTRL_HDF5_GEAR] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_GEAR] = "gear";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_SOURCE_ID] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, sourceId);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_SOURCE_ID] = sizeof(ENRICHED_RDB_DRIVER_CTRL::sourceId);
           fieldType_[RDB_DRIVER_CTRL_HDF5_SOURCE_ID] = H5T_NATIVE_UINT8;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_SOURCE_ID] = "sourceId";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_SPARE0] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, spare0);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_SPARE0] = sizeof(ENRICHED_RDB_DRIVER_CTRL::spare0);
           fieldType_[RDB_DRIVER_CTRL_HDF5_SPARE0] = uintArray8_;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_SPARE0] = "spare0";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_VALIDITY_FLAGS] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, validityFlags);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_VALIDITY_FLAGS] = sizeof(ENRICHED_RDB_DRIVER_CTRL::validityFlags);
           fieldType_[RDB_DRIVER_CTRL_HDF5_VALIDITY_FLAGS] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_VALIDITY_FLAGS] = "validityFlags";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_FLAGS] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, flags);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_FLAGS] = sizeof(ENRICHED_RDB_DRIVER_CTRL::flags);
           fieldType_[RDB_DRIVER_CTRL_HDF5_FLAGS] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_FLAGS] = "flags";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_0] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, mockupInput0);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_0] = sizeof(ENRICHED_RDB_DRIVER_CTRL::mockupInput0);
           fieldType_[RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_0] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_0] = "mockupInput0";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_1] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, mockupInput1);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_1] = sizeof(ENRICHED_RDB_DRIVER_CTRL::mockupInput1);
           fieldType_[RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_1] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_1] = "mockupInput1";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_2] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, mockupInput2);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_2] = sizeof(ENRICHED_RDB_DRIVER_CTRL::mockupInput2);
           fieldType_[RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_2] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_MOCKUP_INPUT_2] = "mockupInput2";

           dstOffset_[RDB_DRIVER_CTRL_HDF5_SPARE] = HOFFSET(ENRICHED_RDB_DRIVER_CTRL, spare);
           dstSizes_ [RDB_DRIVER_CTRL_HDF5_SPARE] = sizeof(ENRICHED_RDB_DRIVER_CTRL::spare);
           fieldType_[RDB_DRIVER_CTRL_HDF5_SPARE] = H5T_NATIVE_UINT32;
           fieldNames_[RDB_DRIVER_CTRL_HDF5_SPARE] = "spare";
        }

        void Hdf5RdbDriverCtrl::convertToModifiedStructure(const RDB_DRIVER_CTRL_t& data, const uint32_t frameNumber, Hdf5RdbDriverCtrl::ENRICHED_RDB_DRIVER_CTRL& modifiedData)
        {
            // DRIVER CONTROL
            modifiedData.frameNumber = frameNumber;
            modifiedData.playerId = data.playerId;
            modifiedData.steeringWheel = data.steeringWheel;
            modifiedData.steeringSpeed = data.steeringSpeed;
            modifiedData.throttlePedal = data.throttlePedal;
            modifiedData.brakePedal = data.brakePedal;
            modifiedData.clutchPedal = data.clutchPedal;
            modifiedData.accelTgt = data.accelTgt;
            modifiedData.steeringTgt = data.steeringTgt;
            modifiedData.curvatureTgt = data.curvatureTgt;
            modifiedData.steeringTorque = data.steeringTorque;
            modifiedData.engineTorqueTgt = data.engineTorqueTgt;
            modifiedData.speedTgt = data.speedTgt;
            modifiedData.gear = data.gear;
            modifiedData.sourceId = data.sourceId;
            modifiedData.spare0[0] = data.spare0[0];
            modifiedData.spare0[1] = data.spare0[1];
            modifiedData.validityFlags = data.validityFlags;
            modifiedData.sourceId = data.sourceId;
            modifiedData.flags = data.flags;
            modifiedData.mockupInput0 = data.mockupInput0;
            modifiedData.mockupInput1 = data.mockupInput1;
            modifiedData.mockupInput2 = data.mockupInput2;
            modifiedData.spare = data.spare;
        }
}

