#ifndef _RDB_HDF5_LIB_H
#define _RDB_HDF5_LIB_H

#include <VtdToolkit/viRDBIcd.h>
#include <string>


//#include <hdf5.h>
//#include <hdf5hl.h>
//#include "Hdf5RdbCamera.h"
//#include "Hdf5RdbContactPoint.h"
#include "Hdf5RdbCustomScoring.h"
#include "Hdf5RdbDriverCtrl.h"
#include "Hdf5RdbDriverPerception.h"
#include "Hdf5RdbEnvironment.h"
//#include "Hdf5RdbFunction.h"
//#include "Hdf5RdbIgFrame.h"
//#include "Hdf5RdbImage.h"
//#include "Hdf5RdbLightSourceBase.h"
//#include "Hdf5RdbLightSourceExt.h"
//#include "Hdf5RdbLightSource.h"
#include "Hdf5RdbMessageCoord.h"
//#include "Hdf5RdbMessageDrivetrainBase.h"
//#include "Hdf5RdbMessageDrivetrainExt.h"
//#include "Hdf5RdbMessageDrivetrain.h"
#include "Hdf5RdbMessageEngineBase.h"
#include "Hdf5RdbMessageEngineExt.h"
#include "Hdf5RdbMessageEngine.h"
#include "Hdf5RdbMessageEntryHeader.h"
#include "Hdf5RdbMessageGeometry.h"
#include "Hdf5RdbMessageHeader.h"
#include "Hdf5RdbMessageLaneInfo.h"
#include "Hdf5RdbMessageObjectCfg.h"
#include "Hdf5RdbMessageObjectStateBase.h"
#include "Hdf5RdbMessageObjectStateExt.h"
#include "Hdf5RdbMessageObjectStateState.h"
//#include "Hdf5RdbMessagePedAnimation.h"
//#include "Hdf5RdbMessageRoadMark.h"
#include "Hdf5RdbMessageRoadPos.h"
#include "Hdf5RdbMessageVehicleSetup.h"
#include "Hdf5RdbMessageVehicleSystem.h"
#include "Hdf5RdbMessageWheelBase.h"
#include "Hdf5RdbMessageWheelExt.h"
#include "Hdf5RdbMessageWheel.h"
//#include "Hdf5RdbMotionSystem.h"
//#include "Hdf5RdbProxy.h"
#include "Hdf5RdbRoadState.h"
#include "Hdf5RdbSensorObject.h"
#include "Hdf5RdbSensorState.h"
#include "Hdf5RdbSync.h"
#include "Hdf5RdbTrafficLightBase.h"
#include "Hdf5RdbTrafficLightExt.h"
#include "Hdf5RdbTrafficLightPhase.h"
#include "Hdf5RdbTrafficLight.h"
//#include "Hdf5RdbTrafficSign.h"
//#include "Hdf5RdbTrigger.h"



namespace RdbToHdf5Writer
{
    static const char* MESSAGE_HEADER_TABLE_NAME = "Message Header";
    static const char* ENVIRONMENT_TABLE_NAME = "Environment Data";
    static const char* MESSAGE_ENTRY_HEADER_TABLE_NAME = "Message Entry Header";
    static const size_t TABLE_NAME_SIZE = 32;
    static const char* HDF5_EXTENSION = ".h5";
    static const unsigned int NUM_OF_ROW_WR = 1;
    static const unsigned int SKIP_FIRST_RAW = 0;
}


#endif
