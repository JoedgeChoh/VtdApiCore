/*********************************************************
* ICD of the Generic Simulation Interface (GSI)          *
*------------------------------------------------------- *
* (c) VIRES GmbH                 Author: Marius Dupuis   *
* -----------------------------------------------------  *
* change log:                                            *
*  10.01.2008: created                                   *
*  22.01.2008: upgrade to "simulation" interface         *
*  25.01.2008: beta for Revision 0x0002 (not released)   *
*              header contains array size                *
*  03.03.2008: Revision 0x0001                           *
*              added message and structure for video     *
*              image transfer                            *
*  05.03.2008: Revision 0x0003                           *
*              added messages for line information of    *
*              master                                    *
*  11.03.2008: introduced image port                     *
*  11.04.2008: Revision 0x0004 introduced package        *
*              END_OF_FRAME                              *
*  14.04.2008: introduced posUSK in structure            *
*              GSI_TRAF_OBJECT_STATE_t                   *
*              introduced elevInertial in structure      *
*              GSI_ROAD_POS_INFO_t                       *
*  06.05.2008: Revision 0x0005                           *
*              introduced GSI_CAMERA_INFO and            *
*              corresponding package GSI_PKG_ID_CAMERA   *
*              added player types MOTORBIKE and BUS      *
*  13.05.2008: Revision 0x0006                           *
*              extracted GSI_ROADMARK_INFO_t from        *
*              GSI_ROAD_POS_INFO_t; extended info with   *
*              USK data of line positions                *
*  21.05.2008: Rev. 0x0006  GSI_PKG_ID_CAMERA 0x0002:    *
*              added posUSK to structure                 *
*              GSI_CAMERA_INFO_t                         *
*  26.06.2008: GSI_PKG_ID_CAMERA rev 0x0002:             *
*              added posUSK to structure                 *
*              GSI_CAMERA_INFO_t                         *
*  11.07.2008: Revision 0x0007                           *
*              added vertical curvature                  *
*              to GSI_ROADMARK_t                         *
*  25.08.2008: Revision 0x0008                           *
*              acceleration and USK positions are now    *
*              of new type GSI_POINT                     *
*  26.08.2008: Revision 0x0009                           *
*              "near" and "far" in camera package are    *
*              now "clipNear" and "clipFar"              *
*              extended GSI_TRAF_OBJECT_STATE_t with     *
*              "speedUSK" and "accelUSK"                 *
*              added GSI_LIGHT_SOURCE_INFO_t             *
*  01.09.2008: Revision 0x000A                           *
*              corrected USK orientation of camera       *
*  22.10.2008: Revision 0x000B                           *
*              contact points introduced                 *
*              GSI_PKG_ID_CONTACT_POINT                  *
*              modified GSI_LIGHT_SOURCE_INFO_t (now     *
*              providing template ID)                    *
*              introduced symbolic constant              *
*              GSI_SIZE_OBJECT_NAME and name             *
*              field in GSI_TRAF_OBJECT_STATE_t          *
*              introduced "posBoxUSK" in structure       *
*              GSI_TRAF_OBJECT_STATE_t, representing the *
*              USK co-ordinates of an object's bounding  *
*              box according to CARMEQ document,         *
*              chapter 6                                 *
*  12.01.2009: Revision 0x000C                           *
*              sensor feedback data contains cone info   *
*              see GSI_SENSOR_DEF_t                      *
*              added "noElements" to header info         *
*              GSI_VEHICLE_SYS_t contains steering angle *
*              introduced the following messages:        *
*                + GSI_PKG_ID_DYNAMICS_INPUT             *
*                + GSI_PKG_ID_DYNAMICS_OUTPUT            *
*  15.04.2009: Revision 0x000D                           *
*              added GSI_TRAFFIC_SIGN_t                  *
*  27.04.2009: modified GSI_DYNAMICS_INPUT_t with        *
*              steering values instead of steering wheel *
*              values                                    *
*              extended GSI_VEHICLE_DYN_t with setup     *
*              information                               *
*              vehicles and pedestrians no longer have a *
*              maximum number, they are now treated like *
*              contact points etc.                       *
*  28.04.2009: USK position of traffic objects is of     *
*              type GSI_COORD again                      *
*              introduced GSI_PKG_ID_ENVIRONMENT         *
*              introduced GSI_DRIVER_FLAG_xxx for driver *
*              info in dynamics input                    *
*  04.06.2009: introduced package with advanced info     *
*              about traffic objects                     *
*              GSI_PKG_TRAF_OBJ_CFG                      *
*  04.08.2009: introduced package with additional info   *
*              about pedestrian geometry                 *
*              GSI_PKG_ID_PED_ANIMATION                  *
*              extended GSI_PKG_TRAF_OBJ_CFG             *
*  06.09.2009: added GSI_PKG_ID_SCORING                  *
*  09.09.2009: introduced GSI_PKG_ID_TRIGGER             *
*  28.09.2009: introduced prototype items of GSI Rev. 2  *
*              these are signified by the prefix         *
*              GSI2_ instead of GSI_                     *
*  22.10.2009: added package GSI_PKG_ID_DRIVER_CTRL      *
*              which can be used for the control of      *
*              dynamics etc. from externally computed    *
*              drivers                                   *
*  04.02.2010: added message GSI_PKG_ID_TRLIGHT_INFO     *
*  07.02.2010: added msg. GSI_PKG_ID_VEHICLE_DYN_SIMPLE  *
*  22.04.2010: modified for 64bit compatibility          *
*  26.07.2010: version 0x000D++                          *
*              introduced GSI_PKG_ID_ROAD_STATE          *
*              split "flags" in GSI_PKG_ID_ENVIRONMENT   *
*              into flags and precipitation info         *
*  02.08.2010: introduced roadS in scoring package       *
*  25.08.2010: split object type in object list package  *
*              into flags and ID                         *
*  27.08.2010: introduced GSI_PKG_ID_LIGHT_SOURCE_CMPLX  *
*  20.09.2010: modified pkg GSI_VEHICLE_WHEEL_SIMPLE_t:  *
*              vAngular is now rotAngle                  *
*  23.09.2010: added further vehicle light masks         *
*  08.05.2014: added traffic driver control package      *
*********************************************************/
#pragma pack (push, 4)

#ifndef _VTD_GENERIC_SIMULATION_ICD_H
#define _VTD_GENERIC_SIMULATION_ICD_H

/* ====== INCLUSIONS ====== */
#include <sys/types.h>
#include <stdint.h>

/* ====== DEFINITIONS ====== */

/* ------ general definitions ------ */
#define GSI_DEFAULT_PORT   48180       /* default port for GSI communication        */
#define GSI_FEEDBACK_PORT  48181       /* port for GSI feedback to taskControl      */
#define GSI_IMAGE_PORT     48182       /* port for GSI image data                   */
#define GSI_NAME_LENGTH       64       /* length of a name sent via GSI             */
#define GSI_MAGIC_NO       14711       /* magic number                              */
#define GSI_VERSION       0x000E       /* upper byte = major, lower byte = minor    */
                                      
/* ------ array sizes ------ */       
#define GSI_SIZE_LANE_INFO        8       /* maximum number of lanes with corresponding information */
#define GSI_SIZE_ROADMARK_INFO    8       /* maximum number of roadmark information entries         */
#define GSI_SIZE_WHEELS           4       /* maximum number of wheels at EGO                        */
#define GSI_NO_SENSORS            5       /* maximum number of active sensors                       */
#define GSI_NO_SENSOR_OBJECTS    50       /* maximum number of objects detected by sensors          */
#define GSI_SIZE_ROADMARK_POINTS 64       /* USK points per roadmark                                */
#define GSI_SIZE_OBJECT_NAME     32       /* maximum length of an object's name                     */
#define GSI_SIZE_JOINT_VALUES    80       /* maximum number of values for pedestrian joint infos    */
#define GSI_SIZE_FILENAME       256       /* number of bytes in a filename                          */
#define GSI_SIZE_TRLIGHT_PHASES   8       /* maximum number of phases for a traffic light           */

/* ------ message types ------ */
#define GSI_PKG_ID_EGO                 0     /* EGO, macroscopic information (as for all other players)       */
#define GSI_PKG_ID_EGO_DYN             1     /* EGO, dynamics information                                     */
#define GSI_PKG_ID_VEHICLE             2     /* macroscopic vehicle player information                        */
#define GSI_PKG_ID_PEDESTRIAN          3     /* info about pedestrian objects                                 */
#define GSI_PKG_ID_OBJ_LIGHT           4     /* info about light objects                                      */
#define GSI_PKG_ID_OBJ_TRSIGN          5     /* info about traffic signs objects                              */
#define GSI_PKG_ID_OBJ_ENV             6     /* info about arbitrary environment objects                      */
#define GSI_PKG_ID_IMAGE               7     /* video image                                                   */
#define GSI_PKG_ID_OBJLIST             8     /* object list for detected objects                              */
#define GSI_PKG_ID_END_OF_FRAME        9     /* sent as last package of a simulation frame                    */
#define GSI_PKG_ID_CAMERA             10     /* camera parameters corresponding to video image                */
#define GSI_PKG_ID_ROADMARK           11     /* road mark information of a player (typically EGO)             */
#define GSI_PKG_ID_LIGHT_SOURCE       12     /* light source information                                      */
#define GSI_PKG_ID_CONTACT_POINT      13     /* road data at a given contact point                            */ /* ver. 0x000B  */
#define GSI_PKG_ID_DYNAMICS_INPUT     14     /* input of an external driver into a vehicle dynamics module    */ /* ver. 0x000C  */
#define GSI_PKG_ID_DYNAMICS_OUTPUT    15     /* output a vehicle dynamics module                              */ /* ver. 0x000C  */
#define GSI_PKG_ID_ENVIRONMENT        16     /* environment information                                       */ /* ver. 0x000D  */
#define GSI_PKG_ID_TRAF_OBJ_CFG       17     /* traffic object configuration info                             */ /* ver. 0x000D+ */
#define GSI_PKG_ID_PED_ANIMATION      18     /* pedestrian animation (joint angles etc.)                      */ /* ver. 0x000D+ */
#define GSI_PKG_ID_SCORING            19     /* parameters for driver scoring (efficiency, safety, race etc.) */ /* ver. 0x000D+ */
#define GSI_PKG_ID_TRIGGER            20     /* trigger info for next simulation frame                        */ /* ver. 0x000D+ */
#define GSI_PKG_ID_DRIVER_CTRL        21     /* trigger info from externally controlled mockup                */ /* ver. 0x000D+ */
#define GSI_PKG_ID_TRLIGHT_INFO       22     /* information about a traffic lights and their states           */ /* ver. 0x000D+ */
#define GSI_PKG_ID_VEHICLE_DYN_SIMPLE 23     /* simplified vehicle dynamics info                              */ /* ver. 0x000D+ */
#define GSI_PKG_ID_ROAD_STATE         24     /* road state information for a given player                     */ /* ver. 0x000D++ */
#define GSI_PKG_ID_LIGHT_SOURCE_CMPLX 25     /* complex light source information                              */
#define GSI_PKG_ID_TRLIGHT_SIMPLE     26     /* simplified traffic light information                          */ /* ver. 0x000D+ */
#define GSI_PKG_ID_TRAF_DRIVER_INFO   27     /* driver control information by traffic                         */ /* ver. 0x000E  */

/* --- new message types for GSI release 2, don't use until officially released!!! --- */
#define GSI2_PKG_ID_MASTER          200
#define GSI2_PKG_ID_VEHICLE         202

/* ------ object types ------ */
#define GSI_OBJECT_TYPE_NONE        0
#define GSI_OBJECT_TYPE_CAR         1
#define GSI_OBJECT_TYPE_TRUCK       2
#define GSI_OBJECT_TYPE_VAN         3
#define GSI_OBJECT_TYPE_BIKE        4
#define GSI_OBJECT_TYPE_PEDESTRIAN  5
#define GSI_OBJECT_TYPE_PED_GROUP   6
#define GSI_OBJECT_TYPE_POLE        7
#define GSI_OBJECT_TYPE_TREE        8
#define GSI_OBJECT_TYPE_BARRIER     9
#define GSI_OBJECT_TYPE_OPT1       10
#define GSI_OBJECT_TYPE_OPT2       11
#define GSI_OBJECT_TYPE_OPT3       12
#define GSI_OBJECT_TYPE_MOTORBIKE  13
#define GSI_OBJECT_TYPE_BUS        14


/* ------ object flags ------ */
#define GSI_OBJECT_FLAG_NONE               0x0000
#define GSI_OBJECT_FLAG_CRITICALITY_LOW    0x0001
#define GSI_OBJECT_FLAG_CRITICALITY_MEDIUM 0x0002
#define GSI_OBJECT_FLAG_CRITICALITY_HIGH   0x0003       /* yes, this really is 0x0003! */

/* ------ light states ------ */
#define GSI_VEHICLE_LIGHT_OFF		    0x00000000       /* all lights OFF                       */
#define GSI_VEHICLE_LIGHT_PARK		    0x00000001       /* front and rear lights are ON         */
#define GSI_VEHICLE_LIGHT_LOWBEAM       0x00000002       /* front and rear lights are ON         */
#define GSI_VEHICLE_LIGHT_HIGHBEAM      0x00000004       /* front and rear lights are ON         */
#define GSI_VEHICLE_LIGHT_REAR_BRAKE    0x00000008       /* only rear lights are ON              */
#define GSI_VEHICLE_LIGHT_REAR_DRIVE    0x00000010       /* only rear lights are ON              */
#define GSI_VEHICLE_LIGHT_INDICATOR_L   0x00000020       /* front and rear lights are ON         */
#define GSI_VEHICLE_LIGHT_INDICATOR_R   0x00000040       /* front and rear lights are ON         */
#define GSI_VEHICLE_LIGHT_FLASH			0x00000080       /* special light for police forces etc. */
#define GSI_VEHICLE_LIGHT_FRONT_FOG		0x00000100       /* only front lights are ON             */
#define GSI_VEHICLE_LIGHT_REAR_FOG		0x00000200       /* only rear lights are ON              */
#define GSI_VEHICLE_LIGHT_VIRES1        0x00000400       /* used internally by VIRES             */ 
#define GSI_VEHICLE_LIGHT_DRL           0x00000800       /**< daytime running light                                   @version 0x0001 */
#define GSI_VEHICLE_LIGHT_DRL_LEFT_LOW  0x00001000       /**< dimmed state of left front DRLs                         @version 0x0001 */
#define GSI_VEHICLE_LIGHT_DRL_RIGHT_LOW 0x00002000       /**< dimmed state of right front DRLs                        @version 0x0001 */

/* ------ lane border types ------ */
#define GSI_LANE_BORDER_UNKNOWN          0
#define GSI_LANE_BORDER_NONE             1
#define GSI_LANE_BORDER_POLE             2
#define GSI_LANE_BORDER_BARRIER          3
#define GSI_LANE_BORDER_SOFT_SHOULDER    4
#define GSI_LANE_BORDER_HARD_SHOULDER    5
#define GSI_LANE_BORDER_CURB             6

/* ------ road mark types ------ */
#define GSI_ROADMARK_TYPE_NONE           0
#define GSI_ROADMARK_TYPE_SOLID          1
#define GSI_ROADMARK_TYPE_BROKEN         2
#define GSI_ROADMARK_TYPE_CURB           3
#define GSI_ROADMARK_TYPE_GRASS          4
#define GSI_ROADMARK_TYPE_BOTDOT         5
#define GSI_ROADMARK_TYPE_OTHER          6

/* ------ road mark colors ------ */
#define GSI_ROADMARK_COLOR_NONE          0
#define GSI_ROADMARK_COLOR_WHITE         1
#define GSI_ROADMARK_COLOR_RED           2
#define GSI_ROADMARK_COLOR_YELLOW        3
#define GSI_ROADMARK_COLOR_OTHER         4

/* ------ wheel indices ------ */
#define GSI_WHEEL_FRONT_LEFT             0
#define GSI_WHEEL_FRONT_RIGHT            1
#define GSI_WHEEL_REAR_LEFT              2
#define GSI_WHEEL_REAR_RIGHT             3

/* ------ gear box types ------ */
#define GSI_GEAR_BOX_TYPE_AUTOMATIC      0
#define GSI_GEAR_BOX_TYPE_MANUAL         1

/* ------ drivetrain types ------ */
#define GSI_DRIVETRAIN_TYPE_FRONT        0
#define GSI_DRIVETRAIN_TYPE_REAR         1
#define GSI_DRIVETRAIN_TYPE_AWD          2

/* ------ image pixel formats ------ */
#define GSI_PIX_FORMAT_RGB            0  /*  8 bit RGB data               */
#define GSI_PIX_FORMAT_RGB_16         1  /* 16 bit RGB data               */
#define GSI_PIX_FORMAT_RGB_24         2  /* 24 bit RGB data               */
#define GSI_PIX_FORMAT_RGBA           3  /*  8 bit RGB data + 8 bit alpha */
#define GSI_PIX_FORMAT_RGBA_16        4  /* 16 bit RGB data + 8 bit alpha */
#define GSI_PIX_FORMAT_RGBA_24        5  /* 24 bit RGB data + 8 bit alpha */
#define GSI_PIX_FORMAT_BW_8           6  /*  8 bit GREY data              */
#define GSI_PIX_FORMAT_BW_16          7  /* 16 bit GREY data              */
#define GSI_PIX_FORMAT_BW_24          8  /* 24 bit GREY data              */
#define GSI_PIX_FORMAT_DEPTH_8        9  /*  8 bit DEPTH data             */
#define GSI_PIX_FORMAT_DEPTH_16      10  /* 16 bit DEPTH data             */
#define GSI_PIX_FORMAT_DEPTH_24      11  /* 24 bit DEPTH data             */

/* ------ sensor types ------ */
#define GSI_SENSOR_TYPE_NONE             0  /* unknown sensor type  */
#define GSI_SENSOR_TYPE_RADAR            1  /* radar sensor         */
#define GSI_SENSOR_TYPE_VIDEO            2  /* radar sensor         */

/* ------ lane existence masks ------ */
#define GSI_LANE_EXISTS_OWN         0x0001  /* own lane exists    */        /* ver. 0x0003 */
#define GSI_LANE_EXISTS_LEFT        0x0002  /* left lane exists   */        /* ver. 0x0003 */
#define GSI_LANE_EXISTS_RIGHT       0x0004  /* right lane exists  */        /* ver. 0x0003 */

/* ------ lane status masks ------ */
#define GSI_LANE_STATUS_NONE        0x0000  /* nothing special    */        /* ver. 0x0003 */
#define GSI_LANE_STATUS_ROADWORKS   0x0001  /* road works         */        /* ver. 0x0003 */
#define GSI_LANE_STATUS_EXIT        0x0002  /* motorway exit      */        /* ver. 0x0003 */
#define GSI_LANE_STATUS_ENTRY       0x0004  /* motorway entry     */        /* ver. 0x0003 */
#define GSI_LANE_STATUS_LINKED      0x0008  /* linked lanes       */        /* ver. 0x0003 */

/* ------ position types ------ */
#define GSI_POS_TYPE_NONE                0  /* default */                                      /* ver. 0x0009 */
#define GSI_POS_TYPE_RELATIVE            1  /* relative position in object's co-ordinates */   /* ver. 0x0009 */
#define GSI_POS_TYPE_INERTIAL            2  /* absolute, i.e. inertial position           */   /* ver. 0x0009 */

/* ------ dynamics input flags ------ */
#define GSI_DRIVER_FLAG_NONE                  0x00000000  /* default                                    */   /* ver. 0x000D */
#define GSI_DRIVER_FLAG_INDICATOR_L           0x00000001  /* driver activated left indicator            */   /* ver. 0x000D */
#define GSI_DRIVER_FLAG_INDICATOR_R           0x00000002  /* driver activated right indicator           */   /* ver. 0x000D */

/* ------ arbitrary state flags ------ */
#define GSI_STATE_FLAG_NONE                   0x00000000  /* default                                    */   /* ver. 0x000D+ */
#define GSI_STATE_FLAG_COLLISION              0x00000001  /* driver caused collision                    */   /* ver. 0x000D+ */
#define GSI_STATE_FLAG_OFF_ROAD               0x00000002  /* driver went off road                       */   /* ver. 0x000D+ */

/* ------ traffic light phases ------ */
#define GSI_TRLIGHT_PHASE_OFF           0
#define GSI_TRLIGHT_PHASE_STOP          1
#define GSI_TRLIGHT_PHASE_STOP_ATTN     2
#define GSI_TRLIGHT_PHASE_GO            3
#define GSI_TRLIGHT_PHASE_GO_EXCL       4
#define GSI_TRLIGHT_PHASE_ATTN          5
#define GSI_TRLIGHT_PHASE_BLINK         6
#define GSI_TRLIGHT_PHASE_UNKNOWN       7

/* ------ road mark information ------ */
/* ------ generic co-ordinate structure --- */
typedef struct 
{
    double x;        /* x position           [m] */
    double y;        /* y position           [m] */
    double z;        /* z position           [m] */
} GSI_POINT_t;

typedef struct
{
    int32_t     id;                                  /* id of road mark                                                    [0..15] */  /* ver. 0x0003 */
    int32_t     prevId;                              /* id of predecessor                                                  [0..15] */  /* ver. 0x0003 */
    int32_t     nextId;                              /* id of successor                                                    [0..15] */  /* ver. 0x0003 */
    float       lateralDist;                         /* lateral distance to vehicle ref. point and dir                         [m] */  /* ver. 0x0003 */
    float       yawRel;                              /* yaw angle relative to vehicle dir                                    [rad] */  /* ver. 0x0003 */
    float       curvHor;                             /* horizontal curvature                                                 [1/m] */  /* ver. 0x0003 */
    float       curvHorDot;                          /* change of horizontal curvature                                      [1/m2] */  /* ver. 0x0003 */
    int32_t     type;                                /* type of road mark                                  [GSI_ROADMARK_TYPE_xxx] */
    int32_t     color;                               /* color of road mark                                [GSI_ROADMARK_COLOR_xxx] */
    float       startDx;                             /* start of road mark in driving dir                                      [m] */
    float       previewDx;                           /* distance of last valid measurement                                     [m] */
    float       width;                               /* width of road mark                                                     [m] */
    float       height;                              /* height of road mark                                                    [m] */
    int32_t     noPoints;                            /* number of points valid in the following array                          [-] */ /* ver. 0x0006 */
    GSI_POINT_t posIn[GSI_SIZE_ROADMARK_POINTS];     /* inertial positions of tesselated road mark                         [m/m/m] */ /* ver. 0x0006 */
    GSI_POINT_t posUSK[GSI_SIZE_ROADMARK_POINTS];    /* USK positions of tesselated road mark                              [m/m/m] */ /* ver. 0x0006 */
    float       curvVert;                            /* vertical curvature                                                   [1/m] */ /* ver. 0x0007 */
    float       curvVertDot;                         /* vertical of vertical curvature                                      [1/m2] */ /* ver. 0x0007 */
} GSI_ROADMARK_t;

/* ------ lane information ------ */
typedef struct
{
    int16_t id;           /* lane ID according to OpenDRIVE                          [-8..8] */
    int16_t borderType;   /* type of lane border                       [GSI_LANE_BORDER_xxx] */
    float   width;        /* lane width                                                  [m] */
} GSI_LANE_INFO_t;

/* ------ road position and properties ------ */
typedef struct
{
    int16_t          roadId;                            /* unique road ID                                                  [-] */
    int16_t          laneId;                            /* lane ID                                                         [-] */
    float            laneOffset;                        /* offset from lane center in road co-ordinates                    [m] */
    float            hdgRel;                            /* heading angle relative to lane tangent dir                    [rad] */
    float            pitchRel;                          /* pitch angle relative to road tangent plane                    [rad] */
    float            rollRel;                           /* roll angle relative to road tangent plane                     [rad] */
    double           curvVert;                          /* vertical curvature in lane center                             [1/m] */
    double           curvVertDot;                       /* change of vertical curvature in lane center                  [1/m2] */
    double           curvHor;                           /* horizontal curvature in lane center                           [1/m] */
    double           curvHorDot;                        /* change of horizontal curvature in lane center                [1/m2] */
    int32_t          noLaneInfo;                        /* number of valid lane information entries                        [-] */
    GSI_LANE_INFO_t  laneInfo[GSI_SIZE_LANE_INFO];      /* lane information entries                                        [-] */
    int32_t          laneExistenceMask;                 /* existence mask for lanes                      [GSI_LANE_EXISTS_xxx] */ /* ver. 0x0003 */
    int32_t          statusMask;                        /* status mask for position                      [GSI_LANE_STATUS_xxx] */ /* ver. 0x0003 */
} GSI_ROAD_POS_INFO_t;

/* ------ road mark information ------ */
typedef struct
{
    int32_t        playerId;                          /* unique of traffic object to which road mark info belongs        [-] */
    int32_t        noRoadMarks;                       /* number of valid roadmark information entries                    [-] */
    GSI_ROADMARK_t roadMark[GSI_SIZE_ROADMARK_INFO];  /* road mark information                                           [-] */
} GSI_ROADMARK_INFO_t;

/* ------ geometry information for an object --- */
typedef struct 
{
    float dimX;        /* x dimension in object co-ordinates (length)      [m] */
    float dimY;        /* y dimension in object co-ordinates (width)       [m] */
    float dimZ;        /* z dimension in object co-ordinates (height)      [m] */
    float offX;        /* x distance from ref. point to center of geometry [m] */
    float offY;        /* y distance from ref. point to center of geometry [m] */
    float offZ;        /* z distance from ref. point to center of geometry [m] */
} GSI_GEOMETRY_INFO_t;

/* ------ generic co-ordinate structure --- */
typedef struct 
{
    double x;        /* x position           [m] */
    double y;        /* y position           [m] */
    double z;        /* z position           [m] */
    double h;        /* heading angle      [rad] */
    double p;        /* pitch angle        [rad] */
    double r;        /* roll angle         [rad] */
} GSI_COORD_t;

/* ------ common traffic object (not vehicle) ------ */
typedef struct
{
    int32_t             id;                         /* unique ID                                                                              [-] */
    int32_t             type;                       /* object type                                                          [GSI_OBJECT_TYPE_xxx] */
    char                name[GSI_SIZE_OBJECT_NAME]; /* symbolic name                                                                          [-] */
    GSI_GEOMETRY_INFO_t geo;                        /* info about object's geometry                                                 [m,m,m,m,m,m] */
    GSI_COORD_t         posIn;                      /* inertial position and orientation of reference point                   [m,m,m,rad,rad,rad] */
    GSI_COORD_t         speedIn;                    /* inertial speed and rates                                   [m/s,m/s,m/s,rad/s,rad/s,rad/s] */
    GSI_POINT_t         accelIn;                    /* inertial acceleration                                                     [m/s2,m/s2,m/s2] */
    GSI_ROAD_POS_INFO_t roadInfo;                   /* additional road information at player's position                                       [-] */
    GSI_COORD_t         origUSKIn;                  /* Version 0x0004: inertial position/orientation of USK's origin          [m,m,m,rad,rad,rad] */
    GSI_COORD_t         posUSK;                     /* Version 0x000D: position in USK                                        [m,m,m,rad,rad,rad] */
    GSI_COORD_t         speedUSK;                   /* Version 0x0009: USK speed and rates                        [m/s,m/s,m/s,rad/s,rad/s,rad/s] */
    GSI_POINT_t         accelUSK;                   /* Version 0x0009: USK acceleration                                          [m/s2,m/s2,m/s2] */
    GSI_COORD_t         posBoxUSK;                  /* Version 0x000B: position of the object's bounding box in USK           [m,m,m,rad,rad,rad] */
} GSI_TRAF_OBJECT_STATE_t;

typedef struct
{
    int32_t             id;                         /* unique ID                                                                              [-] */
    int32_t             type;                       /* object type                                                          [GSI_OBJECT_TYPE_xxx] */
    char                name[GSI_SIZE_OBJECT_NAME]; /* symbolic name                                                                          [-] */
    GSI_GEOMETRY_INFO_t geo;                        /* info about object's geometry                                                 [m,m,m,m,m,m] */
    GSI_COORD_t         posIn;                      /* inertial position and orientation of reference point                   [m,m,m,rad,rad,rad] */
    GSI_COORD_t         speedIn;                    /* inertial speed and rates                                   [m/s,m/s,m/s,rad/s,rad/s,rad/s] */
    GSI_POINT_t         accelIn;                    /* inertial acceleration                                                     [m/s2,m/s2,m/s2] */
} GSI2_TRAF_OBJECT_STATE_t;

/* ------ traffic object (not vehicle) ------ */
typedef struct
{
    int32_t id;                                        /* unique ID                                                                              [-] */
    int32_t modelId;                                   /* visual model ID                                                                        [-] */
    int32_t type;                                      /* object type                                                          [GSI_OBJECT_TYPE_xxx] */
    char    modelName[GSI_SIZE_OBJECT_NAME];           /* filename associated to a traffic object                                                [-] */
    char    fileName[GSI_SIZE_FILENAME];               /* filename associated to a traffic object                                                [-] */
} GSI_TRAF_OBJECT_CFG_t;

/* ------ vehicle system information --- */
typedef struct 
{
    uint32_t lightMask;         /* mask of active light systems                             [GSI_VEHICLE_LIGHT_xxx] */
    float    steering;          /* front wheel steering angle (NOT: steering wheel angle)                     [rad] */
} GSI_VEHICLE_SYS_t;

/* ------ driver information --- */
typedef struct
{
    float steeringWheel;    /* steering wheel angle                     [rad] */
    float steeringSpeed;    /* steering speed                         [rad/s] */
    float throttlePedal;    /* throttle pedal position             [0.0..1.0] */
    float brakePedal;       /* brake pedal position                [0.0..1.0] */
    float clutchPedal;      /* clutch pedal position               [0.0..1.0] */
} GSI_DRIVER_t; 

/* ------ vehicle dynamics information ------ */
typedef struct
{
    float rpm;                   /* speed                         [1/s] */
    float rpmStart;              /* start speed                   [1/s] */
    float torque;                /* torque                         [Nm] */
    float torqueInner;           /* inner torque                   [Nm] */
    float torqueMax;             /* maximum torque                 [Nm] */
    float torqueFriction;        /* friction torque                [Nm] */
    float throttlePos;           /* throttle position        [0.0..1.0] */
} GSI_VEHICLE_ENGINE_t;

typedef struct
{
    float springCompression;      /* compression of spring        [m] */
    float damperSpeed;            /* speed of damper            [m/s] */
    float steeringAngle;          /* steering angle             [rad] */
} GSI_VEHICLE_SUSPENSION_t;

typedef struct
{
    float                    vAngular;              /* angular velocity                [rad/s] */
    float                    forceZ;                /* wheel contact force                 [N] */
    float                    forceLat;              /* lateral force                       [N] */
    float                    forceLong;             /* longitudinal force                  [N] */
    float                    forceTireWheelXYZ[3];  /* force of tire on wheel              [N] */
    float                    radiusStatic;          /* static tire radius                  [m] */
    float                    radiusDynamic;         /* dynamic tire radius                 [m] */
    float                    slip;                  /* slip factor                  [0.0..1.0] */
    float                    brakePressure;         /* brake pressure at wheel            [Pa] */
    GSI_VEHICLE_SUSPENSION_t suspension;            /* wheel suspension information        [-] */
} GSI_VEHICLE_WHEEL_t;

typedef struct
{
    float    torqueDriveShaft[GSI_SIZE_WHEELS];  /* torque at drive shaft                                     [Nm] */
    float    torqueGearBoxIn;                    /* torque at entry of gearbox                                [Nm] */
    float    torqueCenterDiffOut;                /* torque at exit of center differential                     [Nm] */
    float    torqueShaft;                        /* torque at shaft                                           [Nm] */
    uint32_t gearBoxType;                        /* type of gear box                       [GSI_GEAR_BOX_TYPE_xxx] */
    uint32_t driveTrainType;                     /* type of drivetrain                   [GSI_DRIVETRAIN_TYPE_xxx] */
    uint32_t gear;                               /* current gear position                                      [-] */
} GSI_VEHICLE_DRIVETRAIN_t;

/* ------ vehicle dynamics information ------ */
typedef struct
{
    GSI_VEHICLE_ENGINE_t     engine;                  /* engine info                                   [-] */
    GSI_VEHICLE_WHEEL_t      wheel[GSI_SIZE_WHEELS];  /* wheel information [index see GSI_WHEEL_INDEX_xxx] */
    GSI_VEHICLE_DRIVETRAIN_t driveTrain;              /* drive train information                       [-] */
} GSI_VEHICLE_DYN_t;

/* ------ simplified vehicle dynamics information ------ */
typedef struct
{
    float rotAngle;               /* rotation angle                    [rad] */
    float radiusStatic;           /* static tire radius                  [m] */
    float slip;                   /* slip factor                  [0.0..1.0] */
    float springCompression;      /* compression of spring               [m] */
    float steeringAngle;          /* steering angle                    [rad] */
} GSI_VEHICLE_WHEEL_SIMPLE_t;

typedef struct
{
    uint32_t id;                                    /* unique ID of the vehicle (i.e. player)                     [-] */
    float    engineRpm;                             /* engine speed                                             [1/s] */
    float    engineLoad;                            /* engine load                                         [0.0..1.0] */
    uint32_t gearBoxType;                           /* type of gear box                       [GSI_GEAR_BOX_TYPE_xxx] */
    uint32_t driveTrainType;                        /* type of drivetrain                   [GSI_DRIVETRAIN_TYPE_xxx] */
    uint32_t gear;                                  /* current gear position                                      [-] */
    GSI_VEHICLE_WHEEL_SIMPLE_t wheel[GSI_SIZE_WHEELS];  /* wheel information              [index see GSI_WHEEL_INDEX_xxx] */
} GSI_VEHICLE_DYN_SIMPLE_t;

/* ------ vehicle setup information ------ */
typedef struct
{
    float   mass;           /* vehicle mass  [kg] */
    float   wheelBase;      /* wheel base     [m] */
    char    spare[16];      /* for future use     */
} GSI_VEHICLE_SETUP_t;

/* ------ traffic object (vehicle) ------ */
typedef struct
{
    GSI_TRAF_OBJECT_STATE_t base;      /* base information about object (position, geometry, speed etc.)    [-] */
    GSI_VEHICLE_SYS_t       systems;   /* common vehicle system information                                 [-] */
    GSI_DRIVER_t            driver;    /* basic driver information                                          [-] */
    GSI_VEHICLE_SETUP_t     setup;     /* basic vehicle setup information                                   [-] */
} GSI_VEHICLE_STATE_t;

typedef struct
{
    GSI2_TRAF_OBJECT_STATE_t base;     /* base information about object (position, geometry, speed etc.)    [-] */
    GSI_VEHICLE_SYS_t       systems;   /* common vehicle system information                                 [-] */
    GSI_VEHICLE_SETUP_t     setup;     /* basic vehicle setup information                                   [-] */
} GSI2_VEHICLE_STATE_t;

/* ------ image ------ */
typedef struct
{
    uint32_t width;          /* width of the image                   [pixel] */
    uint32_t height;         /* height of the image                  [pixel] */
    uint16_t pixelSize;      /* memory size of a pixel                 [bit] */
    uint16_t pixelFormat;    /* format of a pixel     [GSI_PIXEL_FORMAT_xxx] */
    uint32_t imgSize;        /* total size of image                   [byte] */
} GSI_IMAGE_t;

/* ------ entry in object list ------ */
typedef struct
{
    double   dist;        /* distance between object and referring device         [m] */
    uint16_t type;        /* type of the object                 [GSI_OBJECT_TYPE_xxx] */
    uint16_t flags;       /* object flags                       [GSI_OBJECT_FLAG_xxx] */
    uint32_t id;          /* id of the object                                     [-] */
    uint32_t sensorId;    /* id of the detecting sensor                           [-] */
} GSI_OBJECT_ENTRY_t;

/* ------ sensor definition list ------ */
typedef struct
{  
    uint32_t id;          /* id of the sensor                                     [-] */
    uint32_t type;        /* type of the sensor                 [GSI_SENSOR_TYPE_xxx] */
    char     name[32];    /* pkg-ver. 0x0002: name of the sensor                  [-] */  
    float    dxyz[3];     /* position relative to vehicle                         [m] */
    float    dhpr[3];     /* orientation relative to vehicle                    [rad] */
    float    fovHV[2];    /* field-of-view (horizontal/vertical)                [rad] */
    float    clipNF[2];   /* clipping ranges (near/far)                           [m] */
} GSI_SENSOR_DEF_t;

/* ------ object list ------ */
typedef struct
{
    uint32_t           noSensors;                     /* number of active sensors in list [-] */
    GSI_SENSOR_DEF_t  sensor[GSI_NO_SENSORS];         /* actual sensor definitions            */
    uint32_t           noObjects;                     /* number of active objects in list [-] */
    GSI_OBJECT_ENTRY_t entry[GSI_NO_SENSOR_OBJECTS];  /* detected objects                 [-] */
} GSI_OBJECT_LIST_t;

/* ------ camera list ------ */
typedef struct
{
    int32_t     width;                      /* width of viewport                                      [pixel] */
    int32_t     height;                     /* height of viewport                                     [pixel] */
    float       clipNear;                   /* near clipping plane                                        [m] */
    float       clipFar;                    /* far clipping plane                                         [m] */
    float       focalX;                     /* focal length in x direction                            [pixel] */
    float       focalY;                     /* focal length in y direction                            [pixel] */
    float       principalX;                 /* position of principal point in x direction             [pixel] */
    float       principalY;                 /* position of principal point in y direction             [pixel] */
    GSI_COORD_t posIn;                      /* inertial position and orientation          [m/m/m/rad/rad/rad] */
    GSI_COORD_t posUSK;                     /* USK position and orientation               [m/m/m/rad/rad/rad] */
} GSI_CAMERA_INFO_t;

/* ------ info about a light illuminating the scene ------ */
typedef struct
{
    uint16_t     id;                      /* unique ID of the light source                                               [-] */
    int8_t       templateId;              /* template definition of light source (-1 deletes light source)               [-] */
    uint8_t      state;                   /* state of light source                                                       [-] */
    int32_t      playerId;                /* ID of the player to which light source shall be linked                      [-] */
    uint32_t     posType;                 /* position type of the light source                            [GSI_POS_TYPE_xxx] */
    GSI_COORD_t  position;                /* position and orientation of light source                    [m/m/m/rad/rad/rad] */
} GSI_LIGHT_SOURCE_INFO_t;

/* ------ info about a complex light illuminating the scene ------ */
typedef struct
{
    uint16_t     id;                      /* unique ID of the light source                                               [-] */
    int8_t       templateId;              /* template definition of light source (-1 deletes light source)               [-] */
    uint8_t      state;                   /* state of light source                                                       [-] */
    int32_t      playerId;                /* ID of the player to which light source shall be linked                      [-] */
    uint32_t     posType;                 /* position type of the light source                            [GSI_POS_TYPE_xxx] */
    GSI_COORD_t  position;                /* position and orientation of light source                    [m/m/m/rad/rad/rad] */
    float        nearFar[2];              /* near and far clip of light soure                                          [m,m] */
    float        frustumLRBT[4];          /* frustum left / right / bottom / top                                   [m,m,m,m] */
    float        intensity[3];            /* intensity of the light (ambient, diffuse, specular)                     [-,-,-] */
    float        atten[3];                /* attenuation (constant, linear, quadratic)                               [-,-,-] */
    int32_t      reserved0;
    int32_t      reserved1;
} GSI_LIGHT_SOURCE_CMPLX_t;

/* ------ info about an arbitrary contact point ------ */
typedef struct
{
    uint16_t    id;                      /* unique ID of the contact point                                                                          [-] */
    GSI_COORD_t roadDataIn;              /* inertial position of contact point; heading=0; pitch and roll relative to vehicle axis  [m/m/m/rad/rad/rad] */
    float       friction;                /* road friction at contact point                                                                          [-] */
} GSI_CONTACT_POINT_INFO_t;

/* ------ input of an external driver into an arbitrary (generalized) vehicle dynamics module ------ */
typedef struct
{
    uint32_t id;                    /* unique ID of the dynamics instance (i.e. vehicle)      [-] */
    float    steeringPos;           /* steering position                                    [rad] */
    float    steeringSpeed;         /* steering speed                                     [rad/s] */
    float    accelTgt;              /* desired acceleration                                [m/s2] */
    uint32_t flags;                 /* input flags (indicator etc.)         [GSI_DRIVER_FLAG_xxx] */  /* ver. 0x000D */
} GSI_DYNAMICS_INPUT_t;

/* ------ output of an arbitrary (generalized) dynamics module ------ */
typedef struct
{
    uint32_t            id;              /* unique ID of the dynamics instance (i.e. vehicle)                                      [-] */
    int32_t             type;            /* object type                                                          [GSI_OBJECT_TYPE_xxx] */
    GSI_GEOMETRY_INFO_t geo;             /* info about object's geometry                                                 [m,m,m,m,m,m] */
    GSI_COORD_t         posIn;           /* inertial position and orientation of reference point                   [m,m,m,rad,rad,rad] */
    GSI_COORD_t         speedIn;         /* inertial speed and rates                                   [m/s,m/s,m/s,rad/s,rad/s,rad/s] */
    GSI_POINT_t         accelIn;         /* inertial acceleration                                                     [m/s2,m/s2,m/s2] */
    GSI_VEHICLE_SYS_t   systems;         /* info about vehicle system states (steering, lights etc.)                               [-] */
} GSI_DYNAMICS_OUTPUT_t;

/* ------ signal / sign info for a given vehicle ------ */
typedef struct
{
    uint32_t     id;              /* ID of the signal                                           [-] */
    uint32_t     playerId;        /* ID of the player who "detected" the signal                 [-] */
    float        roadDist;        /* distance to signal along road                              [m] */
    GSI_COORD_t  posIn;           /* inertial position of signal                [m,m,m,rad,rad,rad] */
    int32_t      type;            /* signal type according to OpenDRIVE                         [-] */
    int32_t      subType;         /* signal sub-type according to OpenDRIVE                     [-] */
    float        value;           /* value associated with signal                               [-] */
    uint32_t     state;           /* traffic sign's state (if dynamic)                          [-] */
    uint32_t     spare;           /* spare for upcoming info                                    [-] */
} GSI_TRAFFIC_SIGN_t;

/* ------ road state for a given vehicle ------ */
typedef struct
{
    uint32_t     playerId;        /* ID of the player for which the state applies               [-] */
    uint32_t     roadId;          /* unique ID of the road                                      [-] */
    float        defaultSpeed;    /* default speed of the road                                  [m] */
    float        waterLevel;      /* rain level on road                                  [0.0..1.0] */
    int32_t      spare[12];       /* for future use                                             [-] */
} GSI_ROAD_STATE_t;

/* ------ information about the environment state ------ */
typedef struct
{
    float    visibility;    /* visibility range                   [m] */
    int32_t  cloudState;    /* CLOUD_STATE_XXX                    [-] */
    int32_t  timeOfDay;     /* time of day at sim start           [s] */
    float    brightness;    /* brightness of ambient light [0.0..1.0] */
    uint16_t flags;         /* tbd.                               [-] */
    uint8_t  precipitation; /* intensity of precipitation    [0..255] */
    uint8_t  spare;         /* spare for future use               [-] */
} GSI_ENVIRONMENT_t;

/* ------ details about pedestrians ------ */
typedef struct
{
    int32_t      id;                               /* unique ID                                                              [-] */
    GSI_COORD_t  posIn;                            /* real-world position and orientation of reference point [m,m,m,rad,rad,rad] */
    int32_t      noCoords;                         /* number of valid co-ordinates in coord array                            [-] */ 
    float        coord[GSI_SIZE_JOINT_VALUES];     /* coordinate info of joints                                                  */
} GSI_PED_ANIMATION_t;

/* ------ scoring information ------ */
typedef struct
{
    int32_t  id;                         /* unique player ID                                                                       [-] */
    float    pathS;                      /* path position (negative if no path is available)                                       [m] */
    float    fuelCurrent;                /* current fuel consumption                                                         [l/100km] */
    float    fuelAverage;                /* average fuel consumption                                                         [l/100km] */
    uint32_t stateFlags;                 /* arbitrary state information                                           [GSI_STATE_FLAG_xxx] */
    float    slip;                       /* slip factor                                                                     [0.0..1.0] */
    float    roadS;                      /* progressive road co-ordinate                                                           [m] */
    uint32_t spare[3];                   /* we'll certainly have some more ideas....                                                   */
} GSI_SCORING_t;

/* ------ trigger information ------ */
typedef struct
{
    float deltaT;                 /* delta time by which to advance the simulation    [s] */
    float spare;                  /* spare for future use                                 */
} GSI_TRIGGER_t;

/* ------ information about driver control inputs ------ */
typedef struct
{
    int32_t  playerId;         /* unique player ID to which the controls apply                          [-] */
    float    steeringWheel;    /* steering wheel angle                                                [rad] */
    float    steeringSpeed;    /* steering speed                                                    [rad/s] */
    float    throttlePedal;    /* throttle pedal position                                        [0.0..1.0] */
    float    brakePedal;       /* brake pedal position                                           [0.0..1.0] */
    uint32_t flags;            /* input flags (indicator etc.)                        [GSI_DRIVER_FLAG_xxx] */
    uint32_t spare[6];         /* some spares for future use                                            [-] */
} GSI_DRIVER_CTRL_t; 

/* ------ information about traffic driver control inputs ------ */
typedef struct
{
    int32_t  id;                                                 /* player ID for which info is valid                                         [-] */
    float    steering;                                           /* steering angle.                                                         [rad] */
    float    steeringRate;                                       /* steering rate                                                         [rad/s] */
    float    accelTgt;                                           /* desired acceleration of driver                                         [m/s2] */
    uint32_t flags;                                              /* flags for driver switches etc.                                            [-] */
    float    tgtPos[2];                                          /* XY-coordinates of path target position                                  [m,m] */
    float    speedTgt;                                           /* target speed                                        @unit m/s                 */
    uint32_t validityFlags;                                      /* flags which of the above inputs are valid           @unit DRVR_INPUT_VALIDITY */
    uint32_t spare;                                              /* some spares for future use                                                [-] */
} GSI_TRAF_INFO_DRVR_CTRL_t;

/* ------ information about a traffic light (phases, state) ------ */
typedef struct
{
   float   duration;            /* normalized duration of the phase, invalid phases will have duration 0.0   [0.0..1.0] */
   int32_t type;                /* type of the phase                                            [GSI_TRLIGHT_PHASE_xxx] */
} GSI_TRLIGHT_PHASE_t;

typedef struct
{
   int32_t id;                                         /* unique ID of the traffic light                            [-] */
   int32_t ctrlId;                                     /* ID of the traffic light's controller                      [-] */
   float   cycleTime;                                  /* duration of a complete cycle of all phases                [s] */
   float   state;                                      /* current state (normalized)                         [0.0..1.0] */
   GSI_TRLIGHT_PHASE_t phase[GSI_SIZE_TRLIGHT_PHASES]; /* detailed information about the traffic light phases       [-] */
} GSI_TRLIGHT_INFO_t;

/* ------ simplified traffic light information ------ */
typedef struct
{
    int32_t  id;                                       /* unique ID of a traffic light                              [-] */
    uint32_t stateMask;                                /* traffic light's state mask                                [-] */
} GSI_TRLIGHT_SIMPLE_t;


/* ------ header ------ */
typedef struct
{
    uint16_t magicNo;      /* must be 14711                                                                                [-] */
    uint16_t version;      /* upper byte = major, lower byte = minor                                                       [-] */
    uint32_t frameNo;      /* number of the simulation frame                                                               [-] */
    double   simTime;      /* simulation time                                                                              [s] */
    uint16_t pkgId;        /* package identifier                                                                           [-] */
    uint16_t dataVersion;  /* version number of data block                                                                 [-] */
    uint32_t dataSize;     /* size of data following the header                                                         [byte] */
    uint32_t elementSize;  /* Ver. 0x0004: if data following the header contains an array of elements:                  [byte] */
                           /*              size of one element in this data                                                    */
                           /*              (elementSize is equivalent to dataSize if only one element is transmitted)          */
    uint32_t headerSize;   /* Ver. 0x0004: size of this header structure when transmitted                               [byte] */
    uint32_t noElements;   /* Ver. 0x000C: number of elements following the header data which may also                         */
                                  /*              be computed from dataSize and elementSize                                    [byte] */
} GSI_MSG_HDR_t;

/* ------ the message union ------ */
typedef union
{
    GSI_VEHICLE_STATE_t       egoState;                      /* macroscopic EGO state information                               */
    GSI_VEHICLE_DYN_t         egoDynamics;                   /* EGO dynamics information                                        */
    GSI_VEHICLE_STATE_t       vehicle;                       /* traffic player (vehicle) information                            */
    GSI_TRAF_OBJECT_STATE_t   pedestrian;                    /* traffic player (pedestrian)  information, has no acceleration   */
    GSI_IMAGE_t               image;                         /* video image (followed by data)                                  */
    GSI_OBJECT_LIST_t         objList;                       /* list of detected objects (e.g. from sensor)                     */
    GSI_CAMERA_INFO_t         camera;                        /* camera settings used for video image                            */
    GSI_ROADMARK_INFO_t       roadMarkInfo;                  /* road mark information for a player (EGO)                        */
    GSI_LIGHT_SOURCE_INFO_t   lightSrcInfo;                  /* info about a light source                                       */
    GSI_CONTACT_POINT_INFO_t  contactPoint;                  /* info about contact points                                       */
    GSI_DYNAMICS_INPUT_t      dynamicsInput;                 /* info about input into external dynamics                         */
    GSI_DYNAMICS_OUTPUT_t     dynamicsOutput;                /* info about output from external dynamics                        */
    GSI_TRAFFIC_SIGN_t        trafficSign;                   /* info about traffic signs seen by a vehicle                      */
    GSI_ENVIRONMENT_t         environment;                   /* info about environment state                                    */
    GSI_TRAF_OBJECT_CFG_t     trafObjCfg;                    /* info about traffic object configuration                         */
    GSI_PED_ANIMATION_t       pedAnimation;                  /* pedestrian animation (joint angles etc.)                        */
    GSI_SCORING_t             scoring;                       /* scoring information                                             */
    GSI_TRIGGER_t             trigger;                       /* trigger information                                             */
    GSI_DRIVER_CTRL_t         driverCtrl;                    /* driver input (e.g. from mockup)                                 */
    GSI_TRLIGHT_INFO_t        trLightInfo;                   /* info about traffic lights                                       */
    GSI_VEHICLE_DYN_SIMPLE_t  vehicleDynamicsSimple;         /* simplified information about a vehicle's dynamics state         */
    GSI_ROAD_STATE_t          roadState;                     /* simplified road state for certain vehicles                      */
    GSI_LIGHT_SOURCE_CMPLX_t  lightSrcComplex;               /* info about a complex light source                               */
    GSI_TRLIGHT_SIMPLE_t      trLightSimple;                 /* simplified traffic light information                            */
    GSI_TRAF_INFO_DRVR_CTRL_t trafDriverCtrl;                /* traffic driver contol info                                      */
    
    /* --------------- prototype elements for GSI rev. 2 ------------------ */
    GSI2_VEHICLE_STATE_t     gsi2VehicleState;              /* traffic player (vehicle) information                            */
} GSI_MSG_UNION_t;

/* ------ now the complete message ------ */
typedef struct
{
    GSI_MSG_HDR_t   hdr;
    GSI_MSG_UNION_t u;
} GSI_MSG_t;

#endif		/* _VTD_GENERIC_SIMULATION_ICD_H */

// end of pragma 4
#pragma pack(pop)

