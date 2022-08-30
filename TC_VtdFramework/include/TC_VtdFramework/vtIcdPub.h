/********************************************************
* STATE AND MESSAGE DEFINITIONS FOR                     *
* PLATFORM                                              *
*       Audi Virtual Test Drive                         *
*                                                       *
* PUBLIC SECTION                                        *
*-------------------------------------------------------*
* (c) VIRES                      Author: Marius Dupuis  *
* ----------------------------------------------------- *
* change log:                                           *
*  14.10.2007: derived from FTronik VT-1                *
*              increased N_PLAYER_TRAF from 32 to 42    *
*              introduced CAR_INDICATOR_PERM            *               
*  03.12.2007: introduced interface to DRIVER           *
*              extended VEHICLE interface               *
*              introduced DYN_INPUT_MODE_XXX            *
*  14.01.2008: introduced MSG_PATH_CFG                  *
*              update according to spec. rel. F of VTD  *
*  15.01.2008: version 1.1 of MSG_PLAYER_CFG            *
*  27.01.2008: added drivetrain info etc.               *
*  06.02.2008: version 1.2 of MSG_PLAYER_CFG            *
*              added info from/to traffic               *
*  08.02.2008: re-defined OS_ACTION_SET_ACC_MODE        *
*  13.03.2008: added driver input autonomous            *
*  01.04.2008: added warn actuators DRIVER_WARNACT_t    *
*              added CAR_GEAR_AUTO                      *
*  10.04.2008: previewDistRules for driver set to [m]   *
*  14.04.2008: introduced MSG_DYN_CFG_TC [m]            *
*  25.04.2008: changed gap in DRIVER_INPUT_t to [m]     *
*  25.06.2008: added DYN_INPUT_MODE_STEERING            *
*              added gapMin to DRIVER_INPUT             *
*              ignoring ttc                             *
*  03.03.2009: added wheel base and mass to PLAYER_CFG_t*
*  19.05.2009: adapted to AudiForum requirements        *
*              added CAR_SYSSTATE_xxx                   *
*              added CAR_TYPE_xxx                       *
*  26.06.2009: added feature mask to PLAYER_CFG_t       *
*              made MM_FEATURE_xxx definitions public   *
*  03.07.2009: intrroduced MSG_DYN_PLAYER_RESET_t       *
*              introduced DYN_CFG_FLAG_xxx              *
*              extended MSG_DYN_INFO_TC_t with          *
*              DYN_DRIVER_INPUT_t                       *
*              introduced CAR_SYSSTATE_ESP_ACTIVE and   *
*              CAR_SYSSTATE_ASR_ACTIVE                  *
*  06.09.2009: added CAR_SYSSTATE_DEADLOCK to trigger   *
*              re-start of dynamics                     *
*  22.04.2010: modified for 64bit compatibility         *
*  08.05.2012: added further player types               *
*  27.08.2012: added PLAYER_TYPE_TRAILER                *
*  26.11.2012: added PLAYER_TYPE_TRAIN                  *
*  23.01.2013: added CAR_INDICATOR_LAMP_ON              *
*  05.11.2013: added tractor and trailer to player cfg  *
*  13.02.2014: added player types (AB)                  *
*  20.07.2015: removed legacy protocols                 *
*  08.03.2017: added CAR_LIGHT_FAST_FLASH               *
*********************************************************/
#pragma pack (push, 4)

#ifndef _VT_ICD_PUB_H
#define _VT_ICD_PUB_H

/* ====== INCLUSIONS ====== */
#include <sys/types.h>
#include <stdint.h>

#ifdef _WIN32
    #ifdef interface
    #undef interface
    #endif
#endif

/* ------------------------------------ */
/*  geographic coordinates              */
/*  xg = geographic east                */
/*  yg = geographic north               */
/*  zg = up                             */
/*  heading = CCW, 0 = east             */
/*                                      */
/*  vehicle coordinates                 */
/*  xv = forward                        */
/*  yv = left                           */
/*  zv = up                             */
/*  heading = CCW, 0 = forward          */
/*  pitch = CCW, 0 = level              */
/*  roll = CCW, 0 = level               */
/*                                      */
/*  track coordinates                   */
/*  s = track cord line                 */
/*  t = left                            */
/*  z = up (track elev + rolled elev)   */
/*  heading = CCW, 0 = pos. track dir   */
/* ------------------------------------ */

/* ====== DEFINITIONS ====== */

/*****   DEFAULT COMMUNICATION PORTS   *****/
   /* TCP */
#define PORT_TC_2_VEDYNA    13109   /* scenario control to veDYNA and vice versa */

   /* UDP */
#define ADDR_LOCAL          "127.0.0.1"

/*****   SW COMPONENTS   *****/
#define COMP_TC      2  /* task control - VIRES */
#define COMP_VEDYNA  10 /* veDYNA       - TESIS */

/*****   COMMUNICATION MSG IDs   *****/
#define MSG_NIL                    0
#define MSG_CMD                    1
#define MSG_TASK_STATE             6
#define MSG_ACTION                12    /* package from taskControl to traffic e.a.         */
#define MSG_PLAYER_CFG            18    /* package from traffic to taskControl              */
#define MSG_TC_INFO_DYN           23    /* package from taskControl to veDYNA               */
#define MSG_DYN_INFO_TC           26    /* package from veDYNA to taskControl               */
#define MSG_DYN_PLAYER_CFG        31    /* package from taskControl to veDYNA               */
#define MSG_PATH_CFG              32    /* package from taskControl to veDYNA               */
#define MSG_DYN_CFG_TC            35    /* configuration package from veDYNA to taskControl */
#define MSG_DYN_PLAYER_RESET      58    /* reset dynamics player                            */

/*****   SIMULATION COMMANDS / STATES   *****/
#define CMD_INIT              1
#define CMD_RUN               2
#define CMD_PAUSE             3
#define CMD_TASK_EXIT         5
#define CMD_CALIBRATE         6
#define CMD_STOP              9
#define CMD_REQUEST_CFG      10
#define CMD_INIT_CONFIRM     11
#define CMD_REQUEST_ANIM_OBJ 12

/*****   TASK STATE   *****/
#define TASK_STATE_READY     1
#define TASK_STATE_RUN       2
#define TASK_STATE_PEND      3
#define TASK_STATE_FAIL      4

/*****   MODEL TYPES   *****/
#define MODEL_NIL            0
#define MODEL_CAR1           1
#define MODEL_CAR2           2
#define MODEL_CAR3           3
#define MODEL_CAR4           4
#define MODEL_CAR5           5
#define MODEL_CAR6           6
#define MODEL_CAR7           7
#define MODEL_CAR8           8
#define MODEL_CAR9           9
#define MODEL_CAR_ACC_FAULT 88

#define PLAYER_TYPE_MOTORCYCLE           0
#define PLAYER_TYPE_CAR                  1
#define PLAYER_TYPE_TRUCK                2
#define PLAYER_TYPE_VAN                  3
#define PLAYER_TYPE_BIKE                 4
#define PLAYER_TYPE_PEDESTRIAN           5
#define PLAYER_TYPE_OPT1                10
#define PLAYER_TYPE_OPT2                11
#define PLAYER_TYPE_OPT3                12
#define PLAYER_TYPE_BUS                 14
#define PLAYER_TYPE_OBSTACLE            15
#define PLAYER_TYPE_SIGN                16
#define PLAYER_TYPE_TRAILER             17
#define PLAYER_TYPE_TRAIN               18
#define PLAYER_TYPE_POLE                19
#define PLAYER_TYPE_VEGETATION          20
#define PLAYER_TYPE_TREE                21
#define PLAYER_TYPE_BARRIER             22
#define PLAYER_TYPE_STREET_LIGHT        23
#define PLAYER_TYPE_TRAFFIC_SIGN        24
#define PLAYER_TYPE_BUILDING            25
#define PLAYER_TYPE_PARKING_SPACE       26
#define PLAYER_TYPE_ROAD_WORKS          27
#define PLAYER_TYPE_ROAD                28
#define PLAYER_TYPE_MISC_MOTORWAY       29
#define PLAYER_TYPE_MISC_TOWN           30
#define PLAYER_TYPE_PATCH               31
#define PLAYER_TYPE_OTHER               32
#define PLAYER_TYPE_SEMI_TRAILER        33
#define PLAYER_TYPE_RAILCAR             34
#define PLAYER_TYPE_RAILCAR_SEMI_HEAD   35
#define PLAYER_TYPE_RAILCAR_SEMI_BACK   36

/****** ANIMATION TYPES ******/
#define PLAYER_ANIMATION_INTERN     0
#define PLAYER_ANIMATION_EXTERN     1

/****** MESSAGE MEMBER SIZES ******/
#define N_PLAYER_TRAF         42    /* # of simultaneously active players in traffic simulation */
#define NET_SIZE_PLAYER_NAME  32    /* length of player name */
#define NET_SIZE_FILENAME    256    /* length of a filename */
#define NET_SIZE_OS_ARG      256    /* length of argument from operator station */

/*****   STATEMASK DEFINITIONS of MOVING MODELS   *****/
#define CAR_HEADLIGHT_OFF       0x00000000
#define CAR_HEADLIGHT_PARK      0x00000001
#define CAR_HEADLIGHT_LOWBEAM   0x00000002
#define CAR_HEADLIGHT_HIGHBEAM  0x00000004
#define CAR_BRAKELIGHT          0x00000008
#define CAR_REARLIGHT           0x00000010
#define CAR_INDICATOR_L         0x00000020
#define CAR_INDICATOR_R         0x00000040
#define CAR_FLASHLIGHT          0x00000080
#define CAR_FOGLIGHT_FRONT      0x00000100
#define CAR_FOGLIGHT_REAR       0x00000200
#define CAR_INDICATOR_PERM      0x00000400
#define CAR_LIGHT_DRL           0x00000800       /**< daytime running light                                   @version 0x0001 */
#define CAR_LIGHT_DRL_LEFT_LOW  0x00001000       /**< dimmed state of left front DRLs                         @version 0x0001 */
#define CAR_LIGHT_DRL_RIGHT_LOW 0x00002000       /**< dimmed state of right front DRLs                        @version 0x0001 */
#define CAR_INDICATOR_LAMP_ON   0x00004000
#define CAR_HEADLIGHT_CONE      0x00008000       /** show headlight cone on the street                                        */
#define CAR_LIGHT_FAST_FLASH    0x00010000


/***** GEAR POSITIONS OF CAR *****/
#define CAR_GEAR_P      0
#define CAR_GEAR_R      1
#define CAR_GEAR_D      3
#define CAR_GEAR_AUTO  99

/***** WIPER STATE OF CAR *****/
#define CAR_WIPER_FRONT_ON     0x0001
#define CAR_WIPER_FRONT_FAST   0x0002
#define CAR_WIPER_FRONT_FLUSH  0x0004

/***** ACTIONS for special settings *****/
#define OS_ACTION_SET_MESSAGE               17
#define OS_ACTION_SET_COURSE_FILE           18
#define OS_ACTION_SET_SCENARIO_ID           20  /* was OS_ACTION_SET_DB_FILE in old versions */
#define OS_ACTION_SET_FRUSTUM               21  /* was OS_ACTION_SET_ACC_MODE                */
#define OS_ACTION_SET_HUD_MODE              22
#define OS_ACTION_SET_NIGHTVIS_MODE         23
#define OS_ACTION_SET_HIGHBEAM_MODE         24
#define OS_ACTION_SET_CURVELIGHT_MODE       25
#define OS_ACTION_SET_ACTSTEERING_MODE      26
#define OS_ACTION_SET_COLLWARN_MODE         27
#define OS_ACTION_SET_FOURWHEEL_MODE        28
#define OS_ACTION_SET_HILLHOLD_MODE         29
#define OS_ACTION_SET_HDC_MODE              30
#define OS_ACTION_SET_STEERING_MODE         31
#define OS_ACTION_SET_DAS_CMD               32
#define OS_ACTION_SET_RESET_POS             33
#define OS_ACTION_SET_ACC_MODE              45
#define OS_ACTION_SET_VERSION               50

/***** STATES for vehicle-environment interaction ******/
#define CAR_ENVSTATE_NONE            0x00000000
#define CAR_ENVSTATE_COLLISION       0x00000001
#define CAR_ENVSTATE_ROADMARK        0x00000002
#define CAR_ENVSTATE_OFFROAD         0x00000004

/***** STATES for vehicle sub-systems ******/
#define CAR_SYSSTATE_NONE               0x00000000
#define CAR_SYSSTATE_ACC_LIGHT          0x00000001     /* obsolete */
#define CAR_SYSSTATE_BSD_LEFT_OK        0x00000002
#define CAR_SYSSTATE_BSD_LEFT_DETECT    0x00000004
#define CAR_SYSSTATE_BSD_LEFT_WARN      0x00000008
#define CAR_SYSSTATE_BSD_RIGHT_OK       0x00000010
#define CAR_SYSSTATE_BSD_RIGHT_DETECT   0x00000020
#define CAR_SYSSTATE_BSD_RIGHT_WARN     0x00000040
#define CAR_SYSSTATE_COLLISION_WARN     0x00000080
#define CAR_SYSSTATE_LDW_LEFT           0x00000100
#define CAR_SYSSTATE_LDW_RIGHT          0x00000200
#define CAR_SYSSTATE_ACC_SET_1          0x00000400
#define CAR_SYSSTATE_ACC_SET_2          0x00000800
#define CAR_SYSSTATE_ACC_SET_3          0x00001000
#define CAR_SYSSTATE_ACC_SET_4          0x00002000
#define CAR_SYSSTATE_ACC_LOCK           0x00004000
#define CAR_SYSSTATE_ACC_WARN           0x00008000
#define CAR_SYSSTATE_LDW_DETECT         0x00010000
#define CAR_SYSSTATE_BING               0x00020000
#define CAR_SYSSTATE_PHONE_RING         0x00040000
#define CAR_SYSSTATE_TRAFFIC_INFO       0x00080000
#define CAR_SYSSTATE_PEDEST_WARN        0x00100000
#define CAR_SYSSTATE_AUTO_BRAKE         0x00200000
#define CAR_SYSSTATE_PEDEST_DETECT      0x00400000
#define CAR_SYSSTATE_COLLISION          0x00800000  /* new for AUDI Forum */
#define CAR_SYSSTATE_EXIT_FROM_ROAD     0x01000000  /* new for AUDI Forum */
#define CAR_SYSSTATE_STEER_ERROR        0x02000000  /* new for AUDI Forum */
#define CAR_SYSSTATE_ESP_ACTIVE         0x04000000  /* new for AUDI Forum */
#define CAR_SYSSTATE_ASR_ACTIVE         0x08000000  /* new for AUDI Forum */
#define CAR_SYSSTATE_DEADLOCK           0x10000000  /* new for AUDI Forum */


/***** DRIVER ASSISTANCE SYSTEMS COMMANDS ******/
#define DAS_CMD_ACC_UP         0x00000001   /* ACC handle up                       */
#define DAS_CMD_ACC_DOWN       0x00000002   /* ACC handle down                     */
#define DAS_CMD_ACC_PUSH_1     0x00000004   /* ACC push handle to 1st position     */
#define DAS_CMD_ACC_PUSH_2     0x00000008   /* ACC push handle to 2nd position     */
#define DAS_CMD_ACC_PULL_1     0x00000010   /* ACC pull handle to 1st position     */
#define DAS_CMD_ACC_PULL_2     0x00000020   /* ACC pull handle to 2nd position     */
#define DAS_CMD_ACC_RESET      0x00000040   /* ACC reset pressed                   */
#define DAS_CMD_ACC_INC_DIST   0x00000080   /* ACC increase distance               */
#define DAS_CMD_ACC_DEC_DIST   0x00000100   /* ACC decrease distance               */
#define DAS_CMD_LDW_ON         0x00000200   /* LDW system activated                */
#define DAS_CMD_BSD_ON         0x00000400   /* BSD system activated                */
#define DAS_CMD_HUD_ON         0x00000800   /* HUD system activated                */
#define DAS_CMD_NIGHTVIS_ON    0x00001000   /* Night Vision system activated       */
#define DAS_CMD_HIGHBEAM_ON    0x00002000   /* High Beam system activated          */
#define DAS_CMD_CURVELIGHT_ON  0x00004000   /* Curvelight system activated         */
#define DAS_CMD_ACTSTEERING_ON 0x00008000   /* Active Steering system activated    */
#define DAS_CMD_COLLWARN_ON    0x00010000   /* Collision Warning system activated  */
#define DAS_CMD_FOURWHEEL_ON   0x00020000   /* Four Wheel system activated         */
#define DAS_CMD_HILLHOLD_ON    0x00040000   /* Hill Hold system activated          */
#define DAS_CMD_HDC_ON         0x00080000   /* Hill Descend system activated       */
#define DAS_CMD_LDW_OPT        0x00100000   /* Lane Departure Warning optically - actually, it's ABS for RPB3 */
#define DAS_CMD_LDW_ACO        0x00200000   /* Lane Departure Warning acoustically */
#define DAS_CMD_LDW_HAP        0x00400000   /* Lane Departure Warning optically    */

/***** SYNC MODES ******/
#define DYN_SYNC_MODE_NONE          0   /* undefined synchronization */
#define DYN_SYNC_MODE_ASYNC         1   /* asynchronous mode         */
#define DYN_SYNC_MODE_FRAME_SYNC    2   /* frame-synchronous mode    */

/***** INPUT MODES FOR DYNAMICS ******/
#define DYN_INPUT_MODE_NONE         0x0000   /* undefined input mode                        */
#define DYN_INPUT_MODE_VEHICLE      0x0001   /* use valid vehicle input parameters          */
#define DYN_INPUT_MODE_DRIVER       0x0002   /* use vaild driver input parameters           */
#define DYN_INPUT_MODE_STEERING     0x0004   /* use steering value of VEHICLE_IN message    */

/***** INPUT INFO FOR TURNING VEHICLE ******/
#define DYN_INPUT_TURN_DIR_NONE         0        /* driving on through road              */
#define DYN_INPUT_TURN_DIR_LEFT         1        /* driving on left turn road            */
#define DYN_INPUT_TURN_DIR_RIGHT        2        /* driving on right turn road           */

/***** INPUT FOR SPECIAL DRIVER COMMANDS ******/
#define DYN_INPUT_CMD_ABORT            -1        /* abort current command                */
#define DYN_INPUT_CMD_NONE              0        /* go on driving                        */
#define DYN_INPUT_CMD_LANE_CHANGE       1        /* perform a lane change                */
#define DYN_INPUT_CMD_SPEED_CHANGE      2        /* perform a speed change               */
#define DYN_INPUT_CMD_AUTONOMOUS        3        /* drive autonomously                   */

/***** AVAILABLE BRAKE SYSTEMS ******/
#define DYN_BRAKE_SYSTEM_DRIVER         0        /* braking by driver input               */
#define DYN_BRAKE_SYSTEM_IMMEDIATE      1        /* braking by immediate brake value      */
#define DYN_BRAKE_SYSTEM_CAS            2        /* braking by collision avoidance system */
#define DYN_BRAKE_SYSTEM_BAS            3        /* braking by brake assist system        */

/***** DRIVER BEHAVIOR FLAGS ******/
#define DYN_BEHAVIOR_REGULAR         0x00000000     /* just the usual dude               */
#define DYN_BEHAVIOR_IGNORE_PLAYERS  0x00000001     /* ignore other players              */

/***** TRAFFIC_PLAYER FLAGS ******/
#define DYN_TRAF_PLAYER_FLAG_NONE        0x00000000     /* nothing special                   */
#define DYN_TRAF_PLAYER_FLAG_IGNORE      0x00000001     /* ignore the player                 */
#define DYN_TRAF_PLAYER_FLAG_POS_INVALID 0x00000002     /* player has invalid position       */

/***** SIZE PARAMETERS ******/
#define DYN_DRVR_N_ACTIONS           4                 /* maximum number of driver actions  */
#define DYN_DRVR_N_ACTION_ARGS       2                 /* number of driver action arguments */
#define DYN_N_WARNACT                4                 /* number of warning actuators       */

/***** WHEEL INDICES ******/
#define DYN_WHEEL_FRONT_LEFT         0
#define DYN_WHEEL_FRONT_RIGHT        1
#define DYN_WHEEL_REAR_LEFT          2
#define DYN_WHEEL_REAR_RIGHT         3

/***** NUMBER OF WHEELS ******/
#define DYN_SIZE_WHEELS              4

/***** CONFIGURATION FLAGS FOR DYNAMICS ******/
#define DYN_CFG_FLAG_STANDARD        0x0000
#define DYN_CFG_FLAG_RESET           0x0001

/***** GEARBOX TYPES ******/
#define GSI_GEAR_BOX_TYPE_AUTOMATIC      0
#define GSI_GEAR_BOX_TYPE_MANUAL         1

/***** DRIVETRAIN TYPES ******/
#define GSI_DRIVETRAIN_TYPE_FRONT        0
#define GSI_DRIVETRAIN_TYPE_REAR         1
#define GSI_DRIVETRAIN_TYPE_AWD          2

/***** CAR TYPES FOR VEDYNA ******/
#define CAR_TYPE_VEDYNA_NONE      0
#define CAR_TYPE_VEDYNA_A4        1
#define CAR_TYPE_VEDYNA_Q5        2
#define CAR_TYPE_VEDYNA_R8        3
#define CAR_TYPE_VEDYNA_A1        4

/***** MOVING MODEL FEATUERS *****/
#define MM_FEATURE_NONE              0x00000000       
#define MM_FEATURE_INVISIBLE         0x00000001  /* model is completely invisible */
#define MM_FEATURE_PASSENGER_0       0x00000002  /* passenger 0 (driver) visible  */
#define MM_FEATURE_PASSENGER_1       0x00000004  /* passenger 1 visible           */
#define MM_FEATURE_PASSENGER_2       0x00000008  /* passenger 2 visible           */
#define MM_FEATURE_PASSENGER_3       0x00000010  /* passenger 3 visible           */
#define MM_FEATURE_EXTERNAL_0        0x00000020  /* external feature 0 visible    */
#define MM_FEATURE_EXTERNAL_1        0x00000040  /* external feature 1 visible    */
#define MM_FEATURE_EXTERNAL_2        0x00000080  /* external feature 2 visible    */
#define MM_FEATURE_EXTERNAL_3        0x00000100  /* external feature 3 visible    */


/* ====== STRUCTURES ====== */

/**************************/
/*****   ALL->TC->ALL *****/
/**************************/
typedef struct
{   int32_t  action;
    char     argument[NET_SIZE_OS_ARG];
} MSG_ACTION_t;


/***********************/
/*****   TC->ALL   *****/
/***********************/
typedef struct
{   int32_t cmd;               /* simulation command message    [-]    */
} MSG_CMD_t;


/***********************/
/*****   ALL->TC   *****/
/***********************/
typedef struct
{   int32_t state;           /* task status message        [-]    */
} MSG_TASK_STATE_t;

/***************************/
/*****   TC->veDYNA    *****/
/***************************/
typedef struct  /* configuration of a driving route */
{
    int32_t id;                          /* unique ID of the path            [-] */
    int32_t last;                        /* set to 1 for last waypoint       [-] */
    int32_t trackId;                     /* id of the waypoint's track       [-] */
    float   s;                           /* s position along track           [m] */
    float   t;                           /* t position along track           [m] */
    float   spare;                       /* spare variable                   [-] */
} MSG_PATH_CFG_t;

typedef struct  /* configuration of non-EGO vehicles */
{
    /* V1.0 */ char     name[NET_SIZE_PLAYER_NAME];  /* name of the player                                                             [-] */
    /* V1.0 */ int32_t  id;                          /* player model ID (unique)                                                       [-] */
    /* V1.0 */ int32_t  type;                        /* player type                                                                    [-] */
    /* V1.0 */ float    length;                      /* model length                                                                   [m] */
    /* V1.0 */ float    width;                       /* model width                                                                    [m] */
    /* V1.0 */ int16_t  animation;                   /* extern/intern animation                                                        [-] */
    /* V1.0 */ int16_t  interface;                   /* interface for animation                                                        [-] */
    /* V1.0 */ char     fileName[NET_SIZE_FILENAME]; /* file for the player model                                                      [-] */
    /* V1.0 */ int32_t  last;                        /* set to 1 for last player in row                                                [-] */
    /* V1.0 */ double   xyhInitial[3];               /* initial position of player                                               [m,m,rad] */
    /* V1.0 */ float    xyVehicleOffsetCOG[2];       /* distance between center of geometry and                                            */
                                                   /* center of rear axle in vehicle system                                            [m] */
    /* V1.1 */ float    height;                      /* model height                                                                   [m] */
    /* V1.2 */ float    speedVehicleX;               /* initial speed in vehicle x direction                                         [m/s] */
    /* V1.2 */ int32_t  pathId;                      /* ID of path used by player                                                      [-] */
    /* V1.2 */ float    pathS;                       /* initial s-position along path                                                  [-] */
    /* V1.3 */ float    mass;                        /* mass of player                                                                [kg] */
    /* V1.3 */ float    wheelBase;                   /* wheel base (axle distance)                                                     [m] */
    /* V1.4 */ uint32_t featureMask;                 /* vehicle features like driver, passenger, roof-top coffin etc.     [MM_FEATURE_xxx] */
    /* V1.4 */ int32_t  tractorId;                   /* unique ID of the tractor (hooked to front coupling)                            [-] */
    /* V1.4 */ int32_t  trailerId;                   /* unique ID of the trailer (hooked to rear hitch)                                [-] */
    /* V1.4 */ float    spare[13];                   /* spare for future use                                                           [-] */
} PLAYER_CFG_t;

typedef PLAYER_CFG_t MSG_PLAYER_CFG_t;  /* now alias the structure for the message */

typedef struct  /* configuration of EGO vehicle */
{
    char     name[NET_SIZE_PLAYER_NAME];  /* name of the player                                         [-] */
    int32_t  id;                          /* player model ID                                            [-] */
    int32_t  type;                        /* player type                                                [-] */
    char     fileName[NET_SIZE_FILENAME]; /* file for the player model                                  [-] */
    int32_t  last;                        /* set to 1 for last player in row                            [-] */
    double   xyhInitial[3];               /* initial position of player                           [m,m,rad] */
    float    speedVehicleX;               /* initial speed in vehicle x direction                     [m/s] */
    int32_t  pathId;                      /* ID of path used by player                                  [-] */
    float    pathS;                       /* initial s-position along path                              [m] */
} MSG_DYN_PLAYER_CFG_t;

typedef struct  /* reset of EGO vehicle */
{
    char     name[NET_SIZE_PLAYER_NAME];  /* name of the player                                         [-] */
    int32_t  id;                          /* player model ID                                            [-] */
    double   xyhInitial[3];               /* initial position of player                           [m,m,rad] */
    float    speedVehicleX;               /* initial speed in vehicle x direction                     [m/s] */
    int32_t  pathId;                      /* ID of path used by player                                  [-] */
    float    pathS;                       /* initial s-position along path                              [m] */
    uint16_t flags;                       /* flags for correct interpretation of message [DYN_CFG_FLAG_xxx] */
    uint16_t spare1;                      /* just another spare                                         [-] */
    uint32_t spare2[8];                   /* just a series of spares                                    [-] */
} MSG_DYN_PLAYER_RESET_t;

typedef struct
{
    float    throttle;               /* throttle position                           [0.0..1.0] */
    float    brake;                  /* brake position                              [0.0..1.0] */
    float    parkingBrake;           /* parking brake position                      [0.0..1.0] */
    uint32_t gear;                   /* gear state                              [CAR_GEAR_xxx] */
    uint32_t dasCmd;                 /* commands for driver assistance systems       [DAS_xxx] */
    uint32_t lightMask;              /* car light state                              [CAR_xxx] */
    float    steeringWheel;          /* steering wheel angle                             [rad] */
    float    payload;                /* payload of vehicle                                [kg] */
    float    brakeLatencyRegular;    /* regular brake latency                              [s] */
    float    brakeLatencyPreFill;    /* brake latency in pre-fill conditions               [s] */
    float    decelImmediate;         /* immediate deceleration                          [m/s2] */
    float    decelCollAvoid;         /* deceleration for collision avoidance brake      [m/s2] */
    float    decelBrakeAssist;       /* deceleration for brake assistance brake         [m/s2] */
    int16_t  preFillOn;              /* activity of pre-fill system                      [0/1] */
    int16_t  autoBrake;              /* automatic brake by system       [DYN_BRAKE_SYSTEM_xxx] */
} VEHICLE_INPUT_t;

typedef struct
{
    uint16_t id;                          /* unique action ID                                              [-] */
    uint16_t type;                        /* action type.                                  [DYN_INPUT_CMD_xxx] */
    float    arg[DYN_DRVR_N_ACTION_ARGS]; /* action arguments                                              [-] */
                                          /* for speed change: cmdArg[0] = target speed                  [m/s] */
                                          /*                   cmdArg[1] = rate                         [m/s2] */
                                          /* for lane change:  cmdArg[0] = number of lanes                 [-] */
                                          /*                   cmdArg[1] = time                            [s] */
} DRIVER_ACTION_t;

typedef struct
{
    int32_t id;                          /* unique ID of the warning actuator.                            [-] */
    float   reactionTime;                /* reaction time from activation of actuator to action           [s] */
    float   brakePedal;                  /* brake pedal position at end of action                  [0.0..1.0] */
    float   brakeSpeed;                  /* brake pedal operation speed                                  [1/s] */
} DRIVER_WARNACT_t;

typedef struct
{
    float previewDistPath;                      /* preview distance for path planning                                        [s] */
    float previewDistRules;                     /* preview distance for signs, obstacles etc.                                [m] */
    float gapMin;                               /* desired minimum gap when following predecessor                            [m] */ 
    float gap;                                  /* desired time gap when following predecessor                               [s] */ 
    float ttc;                                  /* desired time-to-collistion to predecessor / obstacle - not used           [s] */
    float maxAccelLong;                         /* maximum desired longitudinal acceleration                              [m/s2] */
    float maxDecelLong;                         /* maximum desired longitudinal deceleration                              [m/s2] */
    float maxAccelLat;                          /* maximum desired lateral acceleration                                   [m/s2] */
    float maxSteerSpeed;                        /* maximum steering speed                                                [rad/s] */
    float maxSteerAngle;                        /* maximum desired steering angle (symmetric)                              [rad] */
    float lateralOffset;                        /* desired lateral offset                                                    [m] */
    float maxSpeedFromRules;                    /* maximum speed from traffic rules                                        [m/s] */
    float distToMaxSpeed;                       /* distance to maximum speed from traffic rules                              [m] */
    int32_t turnDir;                              /* dir of road at preview dist, see                     [DYN_INPUT_TURN_DIR_xxx] */
    int32_t noActions;                            /* number of valid driver actions                                            [-] */
    DRIVER_ACTION_t action[DYN_DRVR_N_ACTIONS]; /* list of driver actions                                                    [-] */
    uint32_t flagsBehavior;                /* driver behavior flags                                      [DYN_BEHAVIOR_xxx] */
    uint16_t noWarnAct;                   /* number of valid warning actuators                                         [-] */
    DRIVER_WARNACT_t warnAct[DYN_N_WARNACT];    /* details of active warning actuators                                       [-] */
} DRIVER_INPUT_t;

typedef struct
{
    int32_t  id;           /* player ID                                                                 [-] */
    int32_t  type;         /* player type                                                               [-] */
    double   xyz[3];       /* player coordinates                                                        [m] */
    float    hpr[3];       /* player attitude                                                         [rad] */
    float    speed[2];     /* speed in xg and yg                                                      [m/s] */
    float    accel[2];     /* acceleration in xg and yg                                              [m/s2] */
    float    length;       /* length of player                                                          [m] */
    float    width;        /* width of player                                                           [m] */
    float    cogOffset[2]; /* offset between center of geometry and                                         */
                           /* center of rear axle in vehicle system                                     [m] */
    float    tComp;        /* lateral offset to ownship moving along path                                   */
                           /* compensated for driving direction                                         [m] */
    float    sDist;        /* longitudinal distance to ownship moving along path                            */
    uint32_t flags;        /* special flags                                      [DYN_TRAF_PLAYER_FLAG_xxx] */
} TRAF_PLAYER_STATE_t;

typedef struct
{
    double              simTime;                 /* simulation time for which package is valid                   [s] */
    uint32_t            frameNumber;             /* frame number                                                 [-] */
    float               tod;                     /* time of day                                                  [s] */
    int32_t             syncMode;                /* synchronization mode                                         [-] */
    int32_t             inputMode;               /* driver input mode                           [DYN_INPUT_MODE_xxx] */
    VEHICLE_INPUT_t     vehicleInput;            /* input from simulator hardware                                [-] */
    DRIVER_INPUT_t      driverInput;             /* input from driver control                                    [-] */
    int32_t             nPlayer;                 /* number of valid traffic players in message                   [-] */
    TRAF_PLAYER_STATE_t plState[N_PLAYER_TRAF];  /* player state information                                     [-] */
} MSG_TC_INFO_DYN_t;


/***************************/
/*****   veDYNA->TC    *****/
/***************************/

/* --- vehicle configuration --- */
typedef struct
{
    double eyeOffsetXYZ[3];   /* offset between reference point and design eyepoint in vehicle co-ordinates [m] */
} MSG_DYN_CFG_TC_t;


typedef struct
{
    int32_t  id;                /* player model ID                                  [-] */
    double   xyz[3];            /* player coordinates (reference point)             [m] */
    float    hpr[3];            /* player attitude                                [rad] */
    float    speed[3];          /* inertial speed                                 [m/s] */
    float    accel[3];          /* inertial acceleration                         [m/s2] */
    float    hprDot[3];         /* angular speed                                [rad/s] */
    float    hprDot2[3];        /* angular acceleration                        [rad/s2] */
    uint32_t lightMask;         /* state of vehicle lights                          [-] */
    float    steering;          /* steering angle                                 [rad] */
    float    rpmEngine;         /* rpm of the engine                              [1/s] */
    float    slip;              /* wheel slip                                       [-] */
    float    loadFactor;        /* normalized load factor                        [0..1] */
    uint32_t envMask;           /* environment interaction state                    [-] */
    uint32_t sysMask;           /* system state                                     [-] */
    float    accSpeed;          /* speed set for ACC                              [m/s] */
    float    lightDir[2];       /* direction of headlights (0=left, 1=right)            */
                                /* relative to car heading                        [rad] */
    float    avgConsum;         /* average consumption                        [l/100km] */
    float    curConsum;         /* current consumption                        [l/100km] */
    float    previewDistRules;  /* preview distance for signs, obstacles etc.       [m] */
} DYN_PLAYER_STATE_t;

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
} DYN_VEHICLE_ENGINE_t;

typedef struct
{
    float springCompression;      /* compression of spring        [m] */
    float damperSpeed;            /* speed of damper            [m/s] */
    float steeringAngle;          /* steering angle             [rad] */
} DYN_VEHICLE_SUSPENSION_t;

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
    DYN_VEHICLE_SUSPENSION_t suspension;            /* wheel suspension information        [-] */
} DYN_VEHICLE_WHEEL_t;

typedef struct
{
    float    torqueDriveShaft[DYN_SIZE_WHEELS];  /* torque at drive shaft                                     [Nm] */
    float    torqueGearBoxIn;                    /* torque at entry of gearbox                                [Nm] */
    float    torqueCenterDiffOut;                /* torque at exit of center differential                     [Nm] */
    float    torqueShaft;                        /* torque at shaft                                           [Nm] */
    uint32_t gearBoxType;                        /* type of gear box                       [GSI_GEAR_BOX_TYPE_xxx] */
    uint32_t driveTrainType;                     /* type of drivetrain                   [GSI_DRIVETRAIN_TYPE_xxx] */
    uint32_t gear;                               /* current gear position                                      [-] */
} DYN_VEHICLE_DRIVETRAIN_t;

typedef struct
{
    float    steeringWheel;                      /* steering wheel angle                                     [rad] */
    float    throttlePedal;                      /* throttle pedal position                             [0.0..1.0] */
    float    brakePedal;                         /* throttle position                                   [0.0..1.0] */
    uint32_t spare[5];                           /* some spares for the future                                 [-] */
} DYN_DRIVER_INPUT_t;

typedef struct
{
    /* V1.0 */   double                   simTime;                 /* simulation time                               [s] */
    /* V1.0 */   uint32_t                 frameNumber;             /* frame number                                  [-] */
    /* V1.0 */   DYN_PLAYER_STATE_t       plState;                 /* dynamics player structure                     [-] */
    /* V1.1 */   DYN_VEHICLE_ENGINE_t     engine;                  /* engine info                                   [-] */
    /* V1.1 */   DYN_VEHICLE_WHEEL_t      wheel[DYN_SIZE_WHEELS];  /* wheel information [index see DYN_WHEEL_INDEX_xxx] */
    /* V1.1 */   DYN_VEHICLE_DRIVETRAIN_t driveTrain;              /* drive train information                       [-] */
    /* V1.0 */   int32_t                  cmd;                     /* control command for reset               [CMD_xxx] */
    /* V1.2 */   DYN_DRIVER_INPUT_t       driverInput;             /* control inputs of external driver             [-] */
} MSG_DYN_INFO_TC_t;


/**************************/
/*****   MSG HEADER   *****/
/**************************/
typedef struct
{   int32_t sender;            /* COMP_XXX                 [-] */
    int32_t receiver;          /* COMP_XXX                 [-] */
    int32_t type;              /* type of following msg    [-] */
    int32_t length;            /* length of following msg  [-] */
} COM_MSG_HEADER_t;


/*****************************/
/*****   MESSAGE UNION   *****/
/*****************************/
typedef union
{
    MSG_ACTION_t           action;
    MSG_CMD_t              cmd;
    MSG_TASK_STATE_t       taskState;
    MSG_PLAYER_CFG_t       playerCfg;
    MSG_TC_INFO_DYN_t      tcInfoDyn;
    MSG_DYN_INFO_TC_t      dynInfoTc;
    MSG_DYN_PLAYER_CFG_t   dynPlayerCfg;
    MSG_DYN_PLAYER_RESET_t dynPlayerReset;
    MSG_PATH_CFG_t         pathCfg;
    MSG_DYN_CFG_TC_t       dynCfgTc;
} COM_MSG_DATA_PUB_u;

/***********************/
/*****   MESSAGE   *****/
/***********************/
typedef struct
{
    COM_MSG_HEADER_t    hdr;
    COM_MSG_DATA_PUB_u    u;
} COM_MSG_PUB_t;

#endif        /* _VT_ICD_PUB_H */

// end of pragma 4
#pragma pack(pop)

