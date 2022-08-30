#include <VtdHdf5/Hdf5RdbTrafficSign.h>

namespace RdbToHdf5Writer
{
        Hdf5RdbTrafficSign::Hdf5RdbTrafficSign() : tableSize_(RDB_TRAFFIC_SIGN_NDATA)
        {
            this->initData();
        }

        void Hdf5RdbTrafficSign::initData()
        {
           dstSize_ = sizeof(RDB_TRAFFIC_SIGN_t);

           dstOffset_[RDB_TRAFFIC_SIGN_ID] = HOFFSET(RDB_TRAFFIC_SIGN_t, id);
           dstSizes_ [RDB_TRAFFIC_SIGN_ID] = sizeof(RDB_TRAFFIC_SIGN_t::id);
           fieldType_[RDB_TRAFFIC_SIGN_ID] = H5T_NATIVE_UINT32;
           fieldNames[RDB_TRAFFIC_SIGN_ID] = "id";

           dstOffset_[RDB_TRAFFIC_SIGN_PLAYER_ID] = HOFFSET(RDB_TRAFFIC_SIGN_t, playerId);
           dstSizes_ [RDB_TRAFFIC_SIGN_PLAYER_ID] = sizeof(RDB_TRAFFIC_SIGN_t::playerId);
           fieldType_[RDB_TRAFFIC_SIGN_PLAYER_ID] = H5T_NATIVE_UINT32;
           fieldNames[RDB_TRAFFIC_SIGN_PLAYER_ID] = "playerId";

           dstOffset_[RDB_TRAFFIC_SIGN_ROAD_DIST] = HOFFSET(RDB_TRAFFIC_SIGN_t, roadDist);
           dstSizes_ [RDB_TRAFFIC_SIGN_ROAD_DIST] = sizeof(RDB_TRAFFIC_SIGN_t::roadDist);
           fieldType_[RDB_TRAFFIC_SIGN_ROAD_DIST] = H5T_NATIVE_FLOAT;
           fieldNames[RDB_TRAFFIC_SIGN_ROAD_DIST] = "roadDist";

           dstOffset_[RDB_TRAFFIC_SIGN_TYPE] = HOFFSET(RDB_TRAFFIC_SIGN_t, type);
           dstSizes_ [RDB_TRAFFIC_SIGN_TYPE] = sizeof(RDB_TRAFFIC_SIGN_t::type);
           fieldType_[RDB_TRAFFIC_SIGN_TYPE] = H5T_NATIVE_INT32;
           fieldNames[RDB_TRAFFIC_SIGN_TYPE] = "type";

           dstOffset_[RDB_TRAFFIC_SIGN_SUB_TYPE] = HOFFSET(RDB_TRAFFIC_SIGN_t, subType);
           dstSizes_ [RDB_TRAFFIC_SIGN_SUB_TYPE] = sizeof(RDB_TRAFFIC_SIGN_t::subType);
           fieldType_[RDB_TRAFFIC_SIGN_SUB_TYPE] = H5T_NATIVE_INT32;
           fieldNames[RDB_TRAFFIC_SIGN_SUB_TYPE] = "subType";

           dstOffset_[RDB_TRAFFIC_SIGN_VALUE] = HOFFSET(RDB_TRAFFIC_SIGN_t, value);
           dstSizes_ [RDB_TRAFFIC_SIGN_VALUE] = sizeof(RDB_TRAFFIC_SIGN_t::value);
           fieldType_[RDB_TRAFFIC_SIGN_VALUE] = H5T_NATIVE_FLOAT;
           fieldNames[RDB_TRAFFIC_SIGN_VALUE] = "value";

           dstOffset_[RDB_TRAFFIC_SIGN_STATE] = HOFFSET(RDB_TRAFFIC_SIGN_t, state);
           dstSizes_ [RDB_TRAFFIC_SIGN_STATE] = sizeof(RDB_TRAFFIC_SIGN_t::state);
           fieldType_[RDB_TRAFFIC_SIGN_STATE] = H5T_NATIVE_FLOAT;
           fieldNames[RDB_TRAFFIC_SIGN_STATE] = "state";

           dstOffset_[RDB_TRAFFIC_SIGN_READABILITY] = HOFFSET(RDB_TRAFFIC_SIGN_t, readability);
           dstSizes_ [RDB_TRAFFIC_SIGN_READABILITY] = sizeof(RDB_TRAFFIC_SIGN_t::readability);
           fieldType_[RDB_TRAFFIC_SIGN_READABILITY] = H5T_NATIVE_INT8;
           fieldNames[RDB_TRAFFIC_SIGN_READABILITY] = "readability";

           dstOffset_[RDB_TRAFFIC_SIGN_OCCLUSION] = HOFFSET(RDB_TRAFFIC_SIGN_t, occlusion);
           dstSizes_ [RDB_TRAFFIC_SIGN_OCCLUSION] = sizeof(RDB_TRAFFIC_SIGN_t::occlusion);
           fieldType_[RDB_TRAFFIC_SIGN_OCCLUSION] = H5T_NATIVE_INT8;
           fieldNames[RDB_TRAFFIC_SIGN_OCCLUSION] = "occlusion";

           dstOffset_[RDB_TRAFFIC_SIGN_SPARE0] = HOFFSET(RDB_TRAFFIC_SIGN_t, spare0);
           dstSizes_ [RDB_TRAFFIC_SIGN_SPARE0] = sizeof(RDB_TRAFFIC_SIGN_t::spare0);
           fieldType_[RDB_TRAFFIC_SIGN_SPARE0] = H5T_NATIVE_INT8;
           fieldNames[RDB_TRAFFIC_SIGN_SPARE0] = "spare0";

           dstOffset_[RDB_TRAFFIC_SIGN_ADD_ON_ID] = HOFFSET(RDB_TRAFFIC_SIGN_t, addOnId);
           dstSizes_ [RDB_TRAFFIC_SIGN_ADD_ON_ID] = sizeof(RDB_TRAFFIC_SIGN_t::addOnId);
           fieldType_[RDB_TRAFFIC_SIGN_ADD_ON_ID] = H5T_NATIVE_UINT32;
           fieldNames[RDB_TRAFFIC_SIGN_ADD_ON_ID] = "addOnId";

           dstOffset_[RDB_TRAFFIC_SIGN_MIN_LANE] = HOFFSET(RDB_TRAFFIC_SIGN_t, minLane);
           dstSizes_ [RDB_TRAFFIC_SIGN_MIN_LANE] = sizeof(RDB_TRAFFIC_SIGN_t::minLane);
           fieldType_[RDB_TRAFFIC_SIGN_MIN_LANE] = H5T_NATIVE_INT8;
           fieldNames[RDB_TRAFFIC_SIGN_MIN_LANE] = "minLane";

           dstOffset_[RDB_TRAFFIC_SIGN_MAX_LANE] = HOFFSET(RDB_TRAFFIC_SIGN_t, maxLane);
           dstSizes_ [RDB_TRAFFIC_SIGN_MAX_LANE] = sizeof(RDB_TRAFFIC_SIGN_t::maxLane);
           fieldType_[RDB_TRAFFIC_SIGN_MAX_LANE] = H5T_NATIVE_INT8;
           fieldNames[RDB_TRAFFIC_SIGN_MAX_LANE] = "maxLane";

           dstOffset_[RDB_TRAFFIC_SIGN_SPARE] = HOFFSET(RDB_TRAFFIC_SIGN_t, spare);
           dstSizes_ [RDB_TRAFFIC_SIGN_SPARE] = sizeof(RDB_TRAFFIC_SIGN_t::spare);
           fieldType_[RDB_TRAFFIC_SIGN_SPARE] = H5T_NATIVE_UINT16;
           fieldNames[RDB_TRAFFIC_SIGN_SPARE] = "spare";
        }

}

