#ifndef _RDB_HDF5_MESSAGE_RDB_ENGINE_EXT_H
#define _RDB_HDF5_MESSAGE_RDB_ENGINE_EXT_H

#include <VtdToolkit/viRDBIcd.h>
#include <hdf5.h>
#include <hdf5_hl.h>

namespace RdbToHdf5Writer
{
    class Hdf5RdbMessageEngineExt
    {
        
    public:

        struct ENRICHED_RDB_ENGINE_EXT
        {
            uint32_t frameNumber;
            float    rpsStart;                    /**< start speed                                      @unit 1/s                       @version 0x0100 */
            float    torque;                      /**< torque                                           @unit Nm                        @version 0x0100 */
            float    torqueInner;                 /**< inner torque                                     @unit Nm                        @version 0x0100 */
            float    torqueMax;                   /**< maximum torque                                   @unit Nm                        @version 0x0100 */
            float    torqueFriction;              /**< friction torque                                  @unit Nm                        @version 0x0100 */
            float    fuelCurrent;                 /**< current fuel consumption                         @unit l/100km                   @version 0x0100 */
            float    fuelAverage;                 /**< average fuel consumption                         @unit l/100km                   @version 0x0100 */
            float    oilTemperature;              /**< oil temperature                                  @unit deg                       @version 0x0119 */
            float    temperature;                 /**< engine core temperature                          @unit deg                       @version 0x0119 */
        };

        static const size_t TABLE_NAME_SIZE = 32;

        enum RDB_ENGINE_EXT_HDF5 {  RDB_ENGINE_EXT_HDF5_FRAME_NUMBER,
                                    RDB_ENGINE_EXT_HDF5_RPS_START,
                                    RDB_ENGINE_EXT_HDF5_TORQUE,
                                    RDB_ENGINE_EXT_HDF5_TORQUE_INNER,
                                    RDB_ENGINE_EXT_HDF5_TORQUE_MAX,
                                    RDB_ENGINE_EXT_HDF5_TORQUE_FRICTION,
                                    RDB_ENGINE_EXT_HDF5_FUEL_CURRENT,
                                    RDB_ENGINE_EXT_HDF5_FUEL_AVERAGE,
                                    RDB_ENGINE_EXT_HDF5_OIL_TEMPERATURE,
                                    RDB_ENGINE_EXT_HDF5_TEMPERATURE,
                                    RDB_ENGINE_EXT_HDF5_NDATA};

        Hdf5RdbMessageEngineExt();

        virtual ~Hdf5RdbMessageEngineExt(){}

        void initData();

        static void convertToModifiedStructure(const RDB_ENGINE_EXT_t& data, const uint32_t frameNumber, ENRICHED_RDB_ENGINE_EXT& modifiedData);

    public:
        
        size_t dstOffset_[RDB_ENGINE_EXT_HDF5_NDATA];
        size_t dstSizes_[RDB_ENGINE_EXT_HDF5_NDATA];
        size_t dstSize_;
        // Define field information
        const char* fieldNames_[RDB_ENGINE_EXT_HDF5_NDATA];
        hid_t fieldType_[RDB_ENGINE_EXT_HDF5_NDATA];
        // Initialize the field field_type
        size_t tableSize_;

    private:

        uint32_t positionFrameId_;
        char tableName_[TABLE_NAME_SIZE];
    };
}

#endif
