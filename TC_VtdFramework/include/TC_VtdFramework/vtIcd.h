/********************************************************
* STATE AND MESSAGE DEFINITIONS FOR                     *
*         PLATFORM AUDI Virtual Test Drive              *
*       CONFIDENTIAL PART                               *
*-------------------------------------------------------*
* (c) VIRES                      Author: Marius Dupuis  *
* ----------------------------------------------------- *
* change log:                                           *
*  14.10.2007: derived from FTronik VT-1                *
*              increased N_MM from 30 to 50             *
*              increased N_OVERLAYS from 10 to 20       *
*              decreased N_PLAYER_EXT from 10 to 4      *
*              added symbols and pedestrians            *
* 19.10.2007:  modified text alignments                 *
* 14.01.2008:  extended player configuration            *
* 06.02.2008:  added MSG_TRAF_INFO_DRVR and             *
*              MSG_DRVR_INFO_TRAF                       *
* 26.02.2008:  added IG commands and image return msg   *
*              MSG_IG_IMG_TC                            *
* 14.04.2008:  added IG control port PORT_IG_CTRL       *
*              and message MSG_TC_CTRL_IG               *
* 21.04.2008:  introduced                               *
*              OS_ACTION_SET_PROJECTION_MATRIX          *
*              OS_ACTION_SET_PROJECTION                 *
*              OS_ACTION_SET_CAMERA_OFFSETS             *
* 08.05.2008:  removed cmdMask from IG runtime data     *
*              added inertial symbol positioning        *
* 09.05.2008:  added message TRAF_INFO_TRLIGHT          *
* 23.07.2008:  added message TC_INFO_INST               *
* 27.08.2008:  introduced TC_INFO_IG_REV02 with larger  *
*              pedestrian data array                    *
*              extended MSG_IG_IMG_TC_t                 *
* 02.09.2008:  Symbols rev.2 may be positioned on       *
*              screen or in space                       *
* 15.10.2008:  modified light source structure to IG    *
* 14.01.2009:  added MSG_TRAF_INFO_DRVR_CTRL            *
* 19.01.2009:  added alternative transmission format    *
*              MSG_PKG_VEC                              *
* 27.02.2009:  added dynamic structures for             *
*              communication to IG (look for REV03)     *
* 03.03.2009:  added two new messages                   *
*              MSG_TRAF_INFO_PED                        *
*              MSG_TRAF_INFO_PLAYER                     * 
*              and one action                           *
*              OS_ACTION_SET_PROJECT_PATH               *
* 27.04.2009:  added new message                        *
*              MSG_TC_PLAYER_SCVIS                      *
*              changed steering wheel to steering in    *
*              MSG_TRAF_INFO_DRVR_CTRL_t                *
* 13.05.2009:  added flags to MSG_TRAF_INFO_DRVR_CTRL_t *
* 27.05.2009:  added MSG_MM_WHEEL                       *
*              and MM_STATE_REV03                       *
*              and PEDESTRIAN_INFO_REV03                *
*              and MSG_IG_LIGHT_SOURCE_REV03            *
* 26.06.2009:  made MM_FEATURE_xxx definitions public   *
* 01.07.2009:  added SYMBOL_TEXT_REV03_t and            *
*              SYMBOL_LINE_REV03_t                      *
* 29.07.2009:  made fogColor in environment message     *
*              unsigned char                            *
* 03.08.2009:  added new sound communication            *
*              (quite a few structures, enums etc.)     *
* 05.02.2010:  added MSG_TRLIGHT_UPDATE_t               *
* 22.04.2010:  modified for 64bit compatibility         *
* 04.05.2010:  added MSG_EXT_PLAYER_STATE               *
* 06.05.2010:  added detailed fog control to environment*
*              message:                                 *
*               IG_ENV_CFG_OVERRIDE_VISIBILITY          *
*               IG_ENV_CFG_OVERRIDE_FOG_COLOR           * 
*               IG_ENV_CFG_FOG_COLOR_HAZE               *
* 27.08.2010:   upgraded LIGHT_SOURCE_REV03             *
*               (has not been used since introduction)  *
* 14.11.2011:   added flags for image transfer via SHM  *
*               or network                              *
* 27.06.2011:   introduced IG_ENV_CFG_STREETLAMPS_ON    *
* 24.08.2011:   added MSG_DRIVER_CTRL                   *
* 26.09.2011:   extended MSG_TRAF_INFO_DRVR_CTRL_t      *
*               with target position                    *
* 07.05.2012:   additional IG commands (rerender, flush)*
* 08.05.2012:   introduced MSG_OBJECT_STATE and corres- *
*               ponding structure                       *
* 02.10.2012:   introduced MSG_IG_LIGHT_SOURCE_REV04    *
* 16.10.2012:   corrected ID of                         *
*               MSG_IG_LIGHT_SOURCE_REV04               *
*               added OS_ACTION_IG_SNAPSHOT             *
*               introduced MSG_RECEIVER_MASK_t          *
* 21.10.2012:   added                                   *
*               DRVR_INPUT_VALIDITY_ADD_ON              *
*               DRVR_INPUT_VALIDITY_FLAGS               *
* 24.10.2012:   introduced                              *
*               IG_CMD_RENDER_CONTINUOUS                *
*               IG_CMD_RENDER_PAUSE                     *
*               IG_CMD_RENDER_SINGLE_FRAME              *
* 10.07.2013:   introduced                              *
*               MSG_STEERING_POINT and                  *
*               MSG_STEERING_POINT_t                    *
* 14.05.2014:   increased precision, introduced:        *
*               TC_INFO_IG_REV10                        *
*               MSG_TC_INFO_IG_REV10                    *
*               SYMBOL_LINE_ENTRY_REV10_t               *
*               MSG_IG_SYMBOL_LINE_REV10                *
*               LIGHT_SOURCE_REV10_t                    *
*               MSG_IG_LIGHT_SOURCE_REV10               *
*               MM_STATE_REV10_t                        *
*               MSG_MM_STATE_REV10                      *
*               PEDESTRIAN_INFO_REV10_t                 *
*               MSG_PED_REV10                           *
* 08.06.2014:   increased precision for text symbols:   *
*               SYMBOL_TEXT_REV10_t                     *
*               MSG_IG_SYMBOL_TEXT_REV10                *
* 07.01.2015:   introduced DYN_EL_SCOPE_xxx             *
*               DYN_EL_DOF_REV10_t                      *
*               DYN_EL_SWITCH_REV10_t                   *
*               MSG_IG_DYN_EL_SWITCH_REV10              *
*               MSG_IG_DYN_EL_DOF_REV10                 *
* 11.03.2015:   introduced MSG_IG_MOTION_SYSTEM         *
*               MOTION_SYSTEM_REV10_t                   *
* 20.07.2015:   removed legacy protocols                *
* 31.07.2015:   introduced                              *
*               SYMBOL_TEXT_REV11_t to overcome some    *
*               deficiencies in SYMBOL_TEXT_REV10_t     *
* 05.08.2015:   introduced MSG_PED_ANIMATION_t          *
*               introduced MSG_PED_ANIMATION            *
* 24.08.2015:   added IG_OBJECT_ANIMATION_t and         *
*               MSG_IG_OBJECT_ANIMATION                 *
* 25.11.2015:   added various DRVR_INPUT_VALIDITY flags *
* 13.01.2017:   added SND_SINGLE_SOURCE_t               *
* 03.05.2018:   converted a spare in                    *
*               MOTION_SYSTEM_REV10_t to reflect        *
*               a sub-system                            *
* 04.03.2019:   converted spare in traffic light update *
*               message for indicating PAUSED mode      *
*********************************************************/
#pragma pack (push, 4)

#ifndef _VT_ICD_H
#define _VT_ICD_H

/* ====== INCLUSIONS ====== */
#include <TC_VtdFramework/vtIcdPub.h>

/* ====== DEFINITIONS ====== */

/*****   MAGIC NUMBER   *****/
#define VT_MAGIC_NO       14714       /* magic number                              */


/*****   DEFAULT COMMUNICATION PORTS   *****/
   /* TCP */
#define PORT_TC_2_OS        13104   /* scenario control to operator station and vice versa */
#define PORT_IG_IMG         13110
#define PORT_TC_2_SCENE     13111
#define PORT_IG_CTRL        13112   /* IG control channel */

   /* UDP */
#define ADDR_ROD            "127.0.0.1"
#define PORT_TC_2_ROD       51234
#define PORT_TC_2_TRAFFIC   13101   /* scenario control to traffic and vice versa */
#define PORT_TC_2_IG        13102
#define PORT_IG_2_TC        13103
#define PORT_TC_2_SCVIS     13105
#define PORT_SCVIS_2_TC     13106
#define PORT_TC_2_SOUND     13107
#define PORT_SOUND_2_TC     13108

/*****   SW COMPONENTS   *****/
/* COMP_FAS and COMP_VILSI are defined in com.h */
//#define COMP_FAS      1
#define COMP_IG       3
#define COMP_TRAFFIC  4  /* traffic simulation */
#define COMP_OS       5
#define COMP_SCVIS    6
#define COMP_SENSOR   7
#define COMP_VEHICLE  8
#define COMP_SOUND    9

/*****   COMMUNICATION MSG IDs   *****/
#define MSG_ENVIRONMENT             2    /* must remain defined for backward compatibility */
#define MSG_IG_TRIGGER              5  
#define MSG_IG_INFO_TC             10    /* must remain defined for backward compatibility */
#define MSG_TC_INFO_OS             13
#define MSG_TC_INFO_TRAF           15    /* package from scenario control to traffic */
#define MSG_TC_INFO_SCVIS          16
#define MSG_SCVIS_INFO_TC          17
#define MSG_PLAYER_INITPOS         19
#define MSG_DATAVIS_CFG            20
#define MSG_DATAVIS_SEL            21
#define MSG_DATAVIS_SET            22
#define MSG_SOUND_INFO_TC          24
#define MSG_TC_INFO_SOUND          25
#define MSG_SCVIS_CFG_TRAFFIC      28
#define MSG_TRAF_INFO_DRVR         29
#define MSG_DRVR_INFO_TRAF         30
#define MSG_PLAYER_EXT_CFG         33
#define MSG_IG_IMG_TC              34
#define MSG_TC_CTRL_IG             36
#define MSG_TRAF_INFO_TRLIGHT      37
#define MSG_TC_INFO_INST           38
#define MSG_TRAF_INFO_DRVR_CTRL    40
#define MSG_PKG_VEC                41    /* message composed of a vector of messages         */
#define MSG_PED                    42    /* pedestrians from TC to IG                        */
#define MSG_IG_LIGHT_SOURCE        44    /* light sources from TC to IG                      */
#define MSG_IG_OVERLAY             46    /* overlays from TC to IG                           */
#define MSG_END_OF_FRAME           48    /* basic frame info from TC to IG                   */
#define MSG_TRAF_INFO_PED          49    /* pedestrian info from traffic to TC               */
#define MSG_TRAF_INFO_PLAYER       50    /* player info from traffic to TC                   */
#define MSG_TC_PLAYER_SCVIS        51    /* player info from TC to ScEditor                  */
#define MSG_MM_WHEEL               52    /* info about a wheel of a moving model             */
#define MSG_IG_LIGHT_SOURCE_REV03  55    /* light sources from TC to IG                      */
/* #define MSG_DYN_PLAYER_RESET       58  */  /* reset dynamics player (in pub version )     */
#define MSG_SND_EGO_STATE          59    /* ego state for sound                              */
#define MSG_SND_OBJ_STATE          60    /* other object's state for sound                   */
#define MSG_SND_ENVIRONMENT        61    /* environment state for sound                      */
#define MSG_TRLIGHT_UPDATE         62    /* update traffic light states                      */
#define MSG_EXT_PLAYER_STATE       63    /* state of a non-traffic player                    */
#define MSG_DRIVER_CTRL            64    /* common driver control message                    */
#define MSG_OBJECT_STATE           65    /* object info from traffic to TC                   */
#define MSG_RECEIVER_MASK          67
#define MSG_STEERING_POINT         68    /* info about a steering path planning point        */
#define MSG_TC_INFO_IG_REV10       69    /*                                                  */
#define MSG_IG_SYMBOL_LINE_REV10   70    /* line symbol from TC to IG                        */
#define MSG_IG_LIGHT_SOURCE_REV10  71    /* light sources from TC to IG                      */
#define MSG_MM_STATE_REV10         72    /* moving models from TC to IG                      */
#define MSG_PED_REV10              73    /* pedestrians from TC to IG                        */
#define MSG_IG_SYMBOL_TEXT_REV10   74    /* text symbol from TC to IG                        */
#define MSG_IG_DYN_EL_SWITCH_REV10 75    /* generic information about a switch               */
#define MSG_IG_DYN_EL_DOF_REV10    76    /* generic information about a DOF                  */
#define MSG_IG_MOTION_SYSTEM       77    /* motion system position for dynamic warping       */
#define MSG_PED_ANIMATION          78    /* pedestrian animation data                        */
#define MSG_IG_SYMBOL_TEXT_REV11   79    /* text symbol from TC to IG, rev 11                */
#define MSG_IG_OBJECT_ANIMATION    80    /* binary package for object animation              */
#define MSG_SND_SINGLE_SOURCE      81    /* state of a single sound source                   */
#define MSG_COMPRESSED             82    /* contains compressed message entries              */
#define MSG_IG_CHANNEL_MASK        83    /* channel mask of IG for TC                        */
#define MSG_END_OF_FRAME_REV11     84    /* An end of frame message with package count       */
#define MSG_FRAGMENT               85    /* Application layer message fragmentation, contains parts of a package vec, avoids fragmentation and udp reordering on the IP layer  */
#define MSG_RDB_OVER_VT            86    /* Entry header is followed by a complete RDB message  */
#define MSG_MM_STATE_EXT           87    /* contains position/velocity/accel information     */
#define MSG_OBJECTPOSITION_INFO    88    /* object positioning information, including player */

/*****   SIMULATION COMMANDS / STATES   *****/
#define CMD_ADMA_INIT           100
#define CMD_BIRD_INIT           101
#define CMD_PREVIEW_RUN         103
#define CMD_PREVIEW_PAUSE       104
#define CMD_PREVIEW_STOP        105
#define CMD_REPLAY_RUN          106
#define CMD_REPLAY_PAUSE        107
#define CMD_REPLAY_STOP         108
#define CMD_REPLAY_STARTPOS     109
#define CMD_REPLAY_ENDPOS       110
#define CMD_REPLAY_STEP_FWD     111
#define CMD_REPLAY_STEP_BACK    112
#define CMD_BIRD_SET_BORESIGHT  113
#define CMD_BIRD_REM_BORESIGHT  114

/****** MESSAGE MEMBER SIZES ******/
#define N_PLAYER_EXT                 4        /* # of simultaneously active external players (not controlled by traffic sim) 
                                                 decreased from 10 to 4                               15.10.2007 */
#define NET_TEXT_SIZE               80        /* length of text string                                           */
#define N_COMP                       7        
#define NET_SIZE_COMP_NAME          64        
#define N_MM                        50        /* # of simultaneously active MM                                   */
#define N_CP                         4        /* number of contact points                                        */
#define NET_SIZE_PARAM_NAME         64        /* length of a parameter's name                                    */
#define N_DATAVIS_PARAM              6        /* number of concurrently available parameters                     */
#define N_DATAVIS_PT_PER_SET        20        /* number of concurrently available parameters                     */
#define N_OVERLAYS                  20        /* introduced                                           19.03.2007 
                                                 increased from 10 to 20                              15.10.2007 */
#define NET_N_SYMBOLS               50        /* number of symbols for IG                             15.10.2007 */
#define NET_SIZE_SYMBOL_TEXT        32        /* size of text associated with symbol                  15.10.2007 */
#define NET_SIZE_SYMBOL_LINES        8        /* maximum number of lines per symbol                              */
#define NET_N_PEDESTRIANS            4        /* maximum number of pedestrians                                   */
#define NET_N_COORD_PER_PED_REV02   80        /* number of coordinates per new pedestrian             27.08.2008 */
#define NET_N_TRLIGHTS              20        /* maximum number of traffic lights per message                    */

/***** ACTIONS FROM OPERATOR STATION TO SCENARIO CONTROL *****/
#define OS_ACTION_FWD          0
#define OS_ACTION_BACK         1
#define OS_ACTION_LEFT         2
#define OS_ACTION_RIGHT        3
#define OS_ACTION_SET_SPEED    4

#define OS_ACTION_SET_PREVIEW_FILE          10
#define OS_ACTION_SET_SCENARIO_FILE         11
#define OS_ACTION_SET_RECORD_FILE           12
#define OS_ACTION_SET_RECORD_OPTION         13
#define OS_ACTION_SET_REPLAY_FILE           14
#define OS_ACTION_SET_REPLAY_STEP           15
#define OS_ACTION_SET_REPLAY_POS            16
#define OS_ACTION_SET_DB_ELEV               19
// find missing actions in public header
#define OS_ACTION_SET_REPLAY_EYEPOINT       34
#define OS_ACTION_SET_DB_FILE               35
#define OS_ACTION_SET_REPLAY_EXPORT         36
#define OS_ACTION_SET_REPLAY_VIDEO          37
#define OS_ACTION_SET_ACC_BEAM              38
#define OS_ACTION_SET_BSD_BEAM              39
#define OS_ACTION_SET_DATABASE              40
#define OS_ACTION_SET_EVENT                 41
#define OS_ACTION_SET_SYMBOL_MODE           42
#define OS_ACTION_SET_DATABASE_MODE         43
#define OS_ACTION_SET_REPLAY_SPEED          44
#define OS_ACTION_SET_PROJECTION_MATRIX     46
#define OS_ACTION_SET_PROJECTION            47
#define OS_ACTION_SET_CAMERA_OFFSETS        48
#define OS_ACTION_SET_PROJECT_PATH          49
// find missing actions in public header
#define OS_ACTION_SET_VIDEO_REC_START       51
#define OS_ACTION_SET_VIDEO_REC_STOP        52
#define OS_ACTION_GET_CAMERA_POS            53
#define OS_ACTION_INFO_CAMERA_POS           54
#define OS_ACTION_VISTA_OVERLAY_START       55
#define OS_ACTION_VISTA_OVERLAY_STOP        56
#define OS_ACTION_VISTA_OVERLAY_CFG         57
#define OS_ACTION_IG_SNAPSHOT               58
#define OS_ACTION_SET_ASYMMETRIC_PROJECTION 59

#define ACTION_ARG_REC_ON        "record_on"
#define ACTION_ARG_REC_OFF       "record_off"
#define ACTION_ARG_OVERWRITE_ON  "overwrite_on"
#define ACTION_ARG_OVERWRITE_OFF "overwrite_off"

/****** TRAFFIC ACTIONS ******/
#define TRAFFIC_ACTION_TYPE_NONE           0x0000
#define TRAFFIC_ACTION_TYPE_LANE_CHANGE    0x0001
#define TRAFFIC_ACTION_TYPE_SPEED          0x0002
#define TRAFFIC_ACTION_TYPE_AUTONOMOUS     0x0004
#define TRAFFIC_ACTION_TYPE_COUNTER        0x0008
#define TRAFFIC_ACTION_TYPE_EVENT          0x0010

/****** MODES OF THE SCENARIO VISUALIZATION ******/
#define SCVIS_MODE_EDIT        0
#define SCVIS_MODE_DRIVE       1
#define SCVIS_MODE_LISTEN      2

/****** REPLAY EYEPOINTS ******/
#define REPLAY_EYEPOINT_EGO          0
#define REPLAY_EYEPOINT_FOLLOWER     1
#define REPLAY_EYEPOINT_EGO_REAR     2
#define REPLAY_EYEPOINT_USER1        3
#define REPLAY_EYEPOINT_USER2        4
#define REPLAY_EYEPOINT_USER3        5
#define REPLAY_EYEPOINT_TVSENSOR     6
#define REPLAY_EYEPOINT_RADARSENSOR  7

/****** TEXT ALIGNMENT ******/
#define SYMBOL_TEXT_ALIGN_LEFT_TOP                   1
#define SYMBOL_TEXT_ALIGN_LEFT_CENTER                2
#define SYMBOL_TEXT_ALIGN_LEFT_BOTTOM                3
#define SYMBOL_TEXT_ALIGN_CENTER_TOP                 4
#define SYMBOL_TEXT_ALIGN_CENTER_CENTER              5
#define SYMBOL_TEXT_ALIGN_CENTER_BOTTOM              6
#define SYMBOL_TEXT_ALIGN_RIGHT_TOP                  7
#define SYMBOL_TEXT_ALIGN_RIGHT_CENTER               8
#define SYMBOL_TEXT_ALIGN_RIGHT_BOTTOM               9
#define SYMBOL_TEXT_ALIGN_LEFT_BASE_LINE            10
#define SYMBOL_TEXT_ALIGN_CENTER_BASE_LINE          11
#define SYMBOL_TEXT_ALIGN_RIGHT_BASE_LINE           12
#define SYMBOL_TEXT_ALIGN_LEFT_BOTTOM_BASE_LINE     13
#define SYMBOL_TEXT_ALIGN_CENTER_BOTTOM_BASE_LINE   14
#define SYMBOL_TEXT_ALIGN_RIGHT_BOTTOM_BASE_LINE    15

/****** SYMBOL POSITIONING ******/
#define SYMBOL_POS_TYPE_INERTIAL        0
#define SYMBOL_POS_TYPE_SCREEN          1

/****** SPECIAL EVENTS ******/
#define DAS_EVENT_RING_PHONE         1
#define DAS_EVENT_TRAFFIC_INFO       2
#define DAS_EVENT_PEDESTRIAN_DETECT  3
#define DAS_EVENT_PEDESTRIAN_WARNING 4
#define DAS_EVENT_AUTO_BRAKE         5

/****** SYMBOL MODES ******/
#define SYMBOL_DISPLAY_MODE_OFF      0
#define SYMBOL_DISPLAY_MODE_BOX      1
#define SYMBOL_DISPLAY_MODE_CROSS    2

/****** DATABASE MODES ******/
#define DATABASE_MODE_OFF         0
#define DATABASE_MODE_NORMAL      1

/***** ENVIRONMENT CONFIGURATION for the IG ******/
/***** ENVIRONMENT STATES for the IG        ******/
#define IG_ENV_CFG_OVERRIDE_VISIBILITY  0x00000001        /* override visibility (i.e.. control fog range via interface) */
#define IG_ENV_CFG_SHADOWS_OFF          0x00000002        /* turn off real-time shadows                                  */
#define IG_ENV_CFG_SURFACE_WET          0x00000004        /* show wet roads etc.                                         */
#define IG_ENV_CFG_SURFACE_SNOW         0x00000008        /* show snow roads etc.                                        */
#define IG_ENV_CFG_OVERRIDE_FOG_COLOR   0x00000010        /* override fog color by interface                             */
#define IG_ENV_CFG_FOG_COLOR_HAZE       0x00000020        /* use IG's haze color table                                   */
#define IG_ENV_CFG_PRECIPITATION_SNOW   0x00000040        /* precipitation is to be displayed as snow                    */
#define IG_ENV_STATE_IN_TUNNEL          0x00010000        /* name changed from IG_ENV_IN_TUNNEL                          */
#define IG_ENV_CFG_STREETLAMPS_ON       0x00020000        /* turn on streetlamps                                         */

/***** COMMANDS for the IG ******/
#define IG_CMD_NONE                     0x00000000        /* do nothing special                                                             */
#define IG_CMD_SNAPSHOT_COLOR           0x00000001        /* get a snapshot of the color buffer                                             */
#define IG_CMD_SNAPSHOT_DEPTH           0x00000002        /* get a snapshot of the depth buffer                                             */
#define IG_CMD_SNAPSHOT_DONE            0x00000004        /* snapshot is finished                                                           */
#define IG_CMD_SNAPSHOT_SHM             0x00000008        /* get snapshot via shared memory                                                 */
#define IG_CMD_SNAPSHOT_NET             0x00000010        /* get snapshot via network also (this will happen per default if no flag is set) */
#define IG_CMD_HDR_SHM                  0x00000020        /* provide HDR image/data in shared memory                                        */
#define IG_CMD_SNAPSHOT_DISK            0x00000040        /* save snapshot locally on the disk                                              */
#define IG_CMD_RENDER_CONTINUOUS        0x00000080        /* render as usual                                                                */
#define IG_CMD_RENDER_PAUSE             0x00000100        /* pause rendering                                                                */
#define IG_CMD_RENDER_SINGLE_FRAME      0x00000200        /* render single frame based on current data                                      */

/***** PIXEL FORMATS USED IN IG *****/
#define IG_PIX_FORMAT_RGB            0  /*  8 bit RGB data               */
#define IG_PIX_FORMAT_RGB_16         1  /* 16 bit RGB data               */
#define IG_PIX_FORMAT_RGB_24         2  /* 24 bit RGB data               */
#define IG_PIX_FORMAT_RGBA           3  /*  8 bit RGB data + 8 bit alpha */
#define IG_PIX_FORMAT_RGBA_16        4  /* 16 bit RGB data + 8 bit alpha */
#define IG_PIX_FORMAT_RGBA_24        5  /* 24 bit RGB data + 8 bit alpha */
#define IG_PIX_FORMAT_BW_8           6  /*  8 bit GREY data              */
#define IG_PIX_FORMAT_BW_16          7  /* 16 bit GREY data              */
#define IG_PIX_FORMAT_BW_24          8  /* 24 bit GREY data              */
#define IG_PIX_FORMAT_DEPTH_8        9  /*  8 bit DEPTH data             */
#define IG_PIX_FORMAT_DEPTH_16      10  /* 16 bit DEPTH data             */
#define IG_PIX_FORMAT_DEPTH_24      11  /* 24 bit DEPTH data             */
#define IG_PIX_FORMAT_DEPTH_32      20  /* 32 bit DEPTH data             */

/***** PEDESTRIAN FEATUERS *****/
#define PED_FEATURE_NONE             0x00000000       
#define PED_FEATURE_INVISIBLE        0x00000001  /* model is completely invisible */

/*****  DRVR_GEAR_BOX_POS *****/
#define DRVR_GEAR_BOX_POS_AUTO             0
#define DRVR_GEAR_BOX_POS_P                1
#define DRVR_GEAR_BOX_POS_R                2
#define DRVR_GEAR_BOX_POS_N                3
#define DRVR_GEAR_BOX_POS_D                4
#define DRVR_GEAR_BOX_POS_1                5
#define DRVR_GEAR_BOX_POS_2                6
#define DRVR_GEAR_BOX_POS_3                7
#define DRVR_GEAR_BOX_POS_4                8
#define DRVR_GEAR_BOX_POS_6                9
#define DRVR_GEAR_BOX_POS_7               10
#define DRVR_GEAR_BOX_POS_8               11
#define DRVR_GEAR_BOX_POS_9               12
#define DRVR_GEAR_BOX_POS_10              13
#define DRVR_GEAR_BOX_POS_11              14
#define DRVR_GEAR_BOX_POS_12              15
#define DRVR_GEAR_BOX_POS_13              16
#define DRVR_GEAR_BOX_POS_14              17
#define DRVR_GEAR_BOX_POS_15              18
#define DRVR_GEAR_BOX_POS_16              19
#define DRVR_GEAR_BOX_POS_R1              20
#define DRVR_GEAR_BOX_POS_R2              21
#define DRVR_GEAR_BOX_POS_R3              22

/*****  DRIVER FLAGS *****/
#define DRVR_FLAG_NONE                      0x00000000  /**< default                                       */
#define DRVR_FLAG_INDICATOR_L               0x00000001  /**< driver activated left indicator               */
#define DRVR_FLAG_INDICATOR_R               0x00000002  /**< driver activated right indicator              */
#define DRVR_FLAG_PARKING_BRAKE             0x00000004  /**< driver activated parking brake                */
#define DRVR_FLAG_LIGHT_EMERGENCY           0x00000080  /**< driver activated emergency light (indic. L&R) */
                                                                                                     
/*****  DRIVER INPUT_VALIDITY *****/                                                                 
#define DRVR_INPUT_VALIDITY_NONE            0x00000000  /**< default                                             */
#define DRVR_INPUT_VALIDITY_STEERING_WHEEL  0x00000001  /**< steering wheel is valid                             */
#define DRVR_INPUT_VALIDITY_STEERING_SPEED  0x00000002  /**< steering speed is valid                             */
#define DRVR_INPUT_VALIDITY_THROTTLE        0x00000004  /**< throttle is valid                                   */
#define DRVR_INPUT_VALIDITY_BRAKE           0x00000008  /**< brake is valid                                      */
#define DRVR_INPUT_VALIDITY_CLUTCH          0x00000010  /**< clutch is valid                                     */
#define DRVR_INPUT_VALIDITY_TGT_ACCEL       0x00000020  /**< target acceleration is valid                        */
#define DRVR_INPUT_VALIDITY_TGT_STEERING    0x00000040  /**< target steering is valid                            */
#define DRVR_INPUT_VALIDITY_GEAR            0x00000080  /**< gear selection is valid                             */
#define DRVR_INPUT_VALIDITY_CURVATURE       0x00000100  /**< curvature is valid for lateral control              */
#define DRVR_INPUT_VALIDITY_STEERING_TORQUE 0x00000200  /**< torque at steering wheel is valid                   */
#define DRVR_INPUT_VALIDITY_ENGINE_TORQUE   0x00000400  /**< target torque of engine is valid                    */
#define DRVR_INPUT_VALIDITY_TGT_SPEED       0x00000800  /**< target speed is valid                               */
#define DRVR_INPUT_VALIDITY_INFO_ONLY       0x00001000  /**< consider the values for info only                   */
#define DRVR_INPUT_VALIDITY_ADD_ON          0x00002000  /**< consider the values as an addOn for existing values */
#define DRVR_INPUT_VALIDITY_FLAGS           0x00004000  /**< member "flags" of MSG_DRIVER_CTRL_t is valid        */
#define DRVR_INPUT_VALIDITY_MOCKUP_INPUT0   0x00008000  /**< member "mockupInput0" of RDB_DRIVER_CTRL_t is valid */
#define DRVR_INPUT_VALIDITY_MOCKUP_INPUT1   0x00010000  /**< member "mockupInput1" of RDB_DRIVER_CTRL_t is valid */
#define DRVR_INPUT_VALIDITY_MOCKUP_INPUT2   0x00020000  /**< member "mockupInput2" of RDB_DRIVER_CTRL_t is valid */
#define DRVR_INPUT_VALIDITY_STEERING_TPOS   0x00040000  /**< steeringTgt to be interpreted as t-position         */

/****** OBJECT STATE FLAGS ******/
#define OBJECT_FLAG_NONE               0x0000 /**< default                                      */
#define OBJECT_FLAG_PERSISTENT         0x0001 /**< object is persistent and must not be deleted */

/****** DYNAMIC ELEMENT SCOPE ******/
#define DYN_EL_SCOPE_UNKNOWN            0       /** scope of a dynamic element definition in unknown                           */
#define DYN_EL_SCOPE_STATIC_DB          1       /** scope of a dynamic element definition in the static database               */
#define DYN_EL_SCOPE_DYN_OBJECT         2       /** scope of a dynamic element definition in a dynamic object                  */
#define DYN_EL_SCOPE_ANY                3       /** scope of a dynamic element definition in any object in the data tree       */
#define DYN_EL_SCOPE_FIRST              4       /** scope of a dynamic element definition in the first object in the data tree */
#define DYN_EL_SCOPE_STATIC_DB_SIGNAL   5       /** scope of a signal definition in the static database                        */
#define DYN_EL_SCOPE_STATIC_DB_SWITCH   6       /** scope of a switch definition in the static database                        */

/****** TRAFFIC LIGHT FLAGS ******/
#define TRAFFIC_LIGHT_FLAG_NONE         0x00    /** no flag set for traffic light */
#define TRAFFIC_LIGHT_FLAG_PAUSED       0x01    /** traffic light is paused       */

/****** COMPRESSION TYPES *****/
#define COMPRESSED_NONE                 0       /** the bytes in the entry are uncompressed   */
#define COMPRESSED_LZ4                  1       /** the bytes in the are compressed using lz4 */

/****** OBJECT_POSITION_INFO TYPES *****/
#define OBJECT_POSITION_INFO_TYPE_PLAYER       0
#define OBJECT_POSITION_INFO_TYPE_LIGHT_SOURCE 1
#define OBJECT_POSITION_INFO_TYPE_RDB_SYMBOL   2
#define OBJECT_POSITION_INFO_TYPE_CAMERA       3

/****** PKG_VEC_VERSIONS*/
#define MSG_PKG_VEC_VERSION_INITIAL     0x0001  /** version 1 for the MSG_PKG_VEC_t **/
/* ====== STRUCTURES ====== */

/**********************/
/*****   IG->TC   *****/
/**********************/
typedef struct
{   int32_t frameNumber;  /* actual frame number      [-] */
    float deltaT;       /* delta t for last frame   [-] */
} MSG_IG_TRIGGER_t;


/**********************/
/*****   TC->IG   *****/
/**********************/
typedef struct
{
    float xyz[3];       /* position      [m] */
    float hpr[3];       /* orientation [rad] */
} NET_COORD_STRUCT;

typedef struct
{
    double xyz[3];       /* position      [m] */
    float  hpr[3];       /* orientation [rad] */
} NET_COORD_DOUBLE_t;

typedef struct
{   int16_t id;                /* ID of light source                                              [-] */
    int8_t  templateID;        /* template definition of light source (-1 deletes headlight)      [-] */
    uint8_t state;             /* state of light source                                           [-] */
    float   xyz[3];            /* light source coordinates                                        [m] */
    float   hpr[3];            /* light source attitude                                         [rad] */
} LIGHT_SOURCE_t;

typedef struct
{
    float  xyz[3];        /* contact point co-ordinates [m]   */
} MM_CONTACT_POINT_t;

typedef struct
{
    int16_t id;        /* overlay ID    */
    int16_t mode;      /* overlay mode  */
    int16_t state;     /* overlay state */
} OVERLAY_INFO_t;

typedef struct
{
    int32_t             id;                             /* unique ID                                                              [-] */
    NET_COORD_STRUCT  refPos;                           /* real-world position and orientation of reference point [m,m,m,rad,rad,rad] */
    float             coord[NET_N_COORD_PER_PED_REV02]; /* coordinate info of joints                                                  */
} PEDESTRIAN_INFO_REV02_t;

typedef struct
{
    double                 simTime;                         /* simulation time                             [s]  14.05.2014  */
    uint32_t               frameNo;                         /* number of the simulation frame              [-]  14.05.2014  */
    NET_COORD_DOUBLE_t     simCarPosition;                  /* position and orientation of simCar               14.05.2014  */
    NET_COORD_DOUBLE_t     cameraEyepoint;                  /* position and orientation of camera eyepoint      14.05.2014  */
    char                   text[NET_TEXT_SIZE];             /* HUD commands message                        [-]  14.05.2014  */
    uint32_t               cameraId;                        /* numeric ID of the camera                    [-]  02.06.2014  */
    uint32_t               spare[4];                        /* some spares for the future                       02.06.2014  */
} MSG_TC_INFO_IG_REV10_t;

typedef struct
{
    uint32_t       cmdMask;       /* set of special IG commands [IG_CMD_xxx] */ 
} MSG_TC_CTRL_IG_t;

typedef struct
{   int32_t            id;                                /* moving model ID                                                                [-] */
    int32_t            type;                              /* model type                                                                     [-] */
    uint32_t           statemask;                         /* moving model state                                                             [-] */
    NET_COORD_DOUBLE_t pos;                               /* position and orientation of moving model                       [m,m,m,rad,rad,rad] */
    float              scale[3];                          /* model scale                                                              [-, -, -] */
    float              steering;                          /* steering angle                                                               [rad] */
    uint32_t           featureMask;                       /* vehicle features like driver, passenger, roof-top coffin etc.     [MM_FEATURE_xxx] */
    int32_t            reserved0;                         
    int32_t            reserved1;                         
} MM_STATE_REV10_t;

typedef struct
{
    int32_t             id;                               /* unique ID                                                                               [-] */
    NET_COORD_DOUBLE_t  refPos;                           /* real-world position and orientation of reference point                  [m,m,m,rad,rad,rad] */
    float               coord[NET_N_COORD_PER_PED_REV02]; /* coordinate info of joints                                                                   */
    uint32_t            featureMask;                      /* features like visibility etc.                                             [PED_FEATURE_xxx] */
    int32_t             reserved0;
    int32_t             reserved1;
} PEDESTRIAN_INFO_REV10_t;

typedef struct
{
    int32_t             id;                               /* unique ID                                                                               [-] */
    NET_COORD_DOUBLE_t  refPos;                           /* real-world position and orientation of reference point                  [m,m,m,rad,rad,rad] */
    uint32_t            featureMask;                      /* features like visibility etc.                                             [PED_FEATURE_xxx] */
    int32_t             reserved0;
    int32_t             reserved1;
} PEDESTRIAN_INFO_REV11_t;

typedef struct
{   int16_t id;                                   /* ID of light source                                                    [-] */
    int8_t  templateID;                           /* template definition of light source (-1 deletes headlight)            [-] */
    uint8_t state;                                /* state of light source                                                 [-] */
    float   xyz[3];                               /* light source coordinates                                          [m,m,m] */
    float   hpr[3];                               /* light source attitude                                       [rad,rad,rad] */
    float   nearFar[2];                           /* near and far clip of light soure                                    [m,m] */
    float   frustumLRBT[4];                       /* frustum left / right / bottom / top in near plane           [m,m,m,m,m,m] */
    float   intensity[3];                         /* intensity of the light (ambient, diffuse, specular)               [-,-,-] */
    float   atten[3];                             /* attenuation (constant, linear, quadratic)                         [-,-,-] */

    int32_t reserved0;
    int32_t reserved1;
} LIGHT_SOURCE_REV03_t;

typedef struct
{   int16_t id;                                   /* ID of light source                                                    [-] */
    int8_t  templateID;                           /* template definition of light source (-1 deletes headlight)            [-] */
    uint8_t state;                                /* state of light source                                                 [-] */
    double  xyz[3];                               /* light source coordinates                                          [m,m,m] */
    float   hpr[3];                               /* light source attitude                                       [rad,rad,rad] */
    float   nearFar[2];                           /* near and far clip of light soure                                    [m,m] */
    float   frustumLRBT[4];                       /* frustum left / right / bottom / top in near plane           [m,m,m,m,m,m] */
    float   intensity[3];                         /* intensity of the light (ambient, diffuse, specular)               [-,-,-] */
    float   atten[3];                             /* attenuation (constant, linear, quadratic)                         [-,-,-] */
    int32_t reserved0;
    int32_t reserved1;
    uint8_t isMaskEnabled;                        /* Whether the mask is enabled */
    uint8_t spare[3];                             /* just a few spares */
    float   maskPos[2];                           /* Normalized position of the mask. (0,0) is bottom, left; (1,1) top, right */
    float   maskScale[2];                         /* XY Scaling of the mask. */
} LIGHT_SOURCE_REV10_t;

typedef struct
{
    uint8_t  fontId;                               /* numerical ID of the font which is to be used                      [-] */
    uint8_t  layer;                                /* layer on which to draw the text                                   [-] */
    uint8_t  alignment;                            /* text alignment, see                           [SYMBOL_TEXT_ALIGN_XXX] */
    uint8_t  posType;                              /* position type                                   [SYMBOL_POS_TYPE_xxx] */
    float    textSize;                             /* text size                                                       [pts] */                                                         
    double   textAnchor[10];                       /* anchor point of text x/y/z                                    [m/m/m] */
    uint8_t  colorRGBA[4];                         /* text color                                                        [-] */
    uint32_t spare[8];                             /* for future use                                                    [-] */
    uint16_t spare2;                               /* just another spare                                                [-] */
    uint16_t length;                               /* length of the text (without terminating character)                [-] */
    /* actual text follows directly after this block                                                                    [-] */
} SYMBOL_TEXT_REV10_t;

typedef struct
{
    uint8_t  fontId;                               /* numerical ID of the font which is to be used                      [-] */
    uint8_t  layer;                                /* layer on which to draw the text                                   [-] */
    uint8_t  alignment;                            /* text alignment, see                           [SYMBOL_TEXT_ALIGN_XXX] */
    uint8_t  posType;                              /* position type                                   [SYMBOL_POS_TYPE_xxx] */
    float    textSize;                             /* text size                                                       [pts] */                                                         
    double   textAnchor[3];                        /* anchor point of text x/y/z                                    [m/m/m] */
    uint8_t  colorRGBA[4];                         /* text color                                                        [-] */
    uint32_t spare[8];                             /* for future use                                                    [-] */
    uint16_t spare2;                               /* just another spare                                                [-] */
    uint16_t length;                               /* length of the text (without terminating character)                [-] */
    /* actual text follows directly after this block                                                                    [-] */
} SYMBOL_TEXT_REV11_t;

typedef struct
{
    double xyzFrom[3]; /* real-world position of line's from point */
    double xyzTo[3];   /* real-world position of line's to point   */
} SYMBOL_LINE_ENTRY_REV10_t;

typedef struct
{
    uint8_t  layer;                                /* layer on which to draw the symbol                                                            [-] */
    int8_t   ovlTemplate;                          /* ID of the overlay template which is to be used for texturing the symbol (-1 for outline)     [-] */
    uint8_t  ovlState;                             /* state of the overlay template which is to be used for texturing the symbol                   [-] */
    uint8_t  posType;                              /* position type                                                              [SYMBOL_POS_TYPE_xxx] */
    uint8_t  colorRGBA[4];                         /* symbol / line color                                                                          [-] */
    float    lineWidth;                            /* width of the following lines                                                             [pixel] */
    uint32_t spare[8];                             /* for future use                                                                               [-] */
    uint16_t spare2;                               /* just another spare                                                                           [-] */
    uint16_t nLines;                               /* number of valid lines                                                                        [-] */
    /* actual lines follow directly after this block                                                                       [SYMBOL_LINE_ENTRY_REV10_t] */
} SYMBOL_LINE_REV03_t;

typedef struct
{
    uint32_t objectId;                             /* ID of the object which contains the switch                                                   [-] */
    uint32_t elementId;                            /* ID of the switch itself                                                                      [-] */
    uint8_t  scope;                                /* scope of the dynamic element                                                  [DYN_EL_SCOPE_xxx] */
    uint8_t  spare0[3];                            /* for future use                                                                               [-] */
    uint32_t state;                                /* state of the switch as bit mask                                                              [-] */
    uint32_t spare1[2];                            /* for future use                                                                               [-] */
} DYN_EL_SWITCH_REV10_t;

typedef struct
{
    uint32_t objectId;                             /* ID of the object which contains the switch                                                                       [-] */
    uint32_t elementId;                            /* ID of the switch itself                                                                                          [-] */
    uint8_t  scope;                                /* scope of the dynamic element                                                                      [DYN_EL_SCOPE_xxx] */
    uint8_t  validity;                             /* mask of elements controlled by the following double numbers         [x=0x01, y=0x02, z=0x04, h=0x08, p=0x10, r=0x20] */
    uint8_t  nValues;                              /* number of double values sent immediately after this structure                                                    [-] */
    uint8_t  spare0;                               /* for future use                                                                                                   [-] */
    uint32_t spare1[3];                            /* for future use                                                                                                   [-] */
    /* actual values follow directly after this block                                                                                                             [double] */
} DYN_EL_DOF_REV10_t;

typedef struct
{
    double   xyz[3];                                /* position of the motion system [m/m/m]          */
    float    hpr[3];                                /* orientation of the motion system [rad/rad/rad] */
    uint32_t flags;                                 /* optional flags for motion system operation [-] */
    uint8_t  subSystem;                             /* sub-system indicator [-]                       */
    uint8_t  spare1[3];                             /* several spares for future use [-]              */
    uint32_t spare[1];                              /* several spares for future use [-]              */
} MOTION_SYSTEM_REV10_t;

typedef struct
{
    uint32_t dataSize;                              /* length of payload data following this package [byte]   */
    uint8_t  version;                               /* version number                                         */
    uint8_t  spare0[3];                             /* several spares for future use [-]                      */
    uint32_t spare[2];                              /* several spares for future use [-]                      */
    /* actual values follow directly after this block [-] */
} IG_OBJECT_ANIMATION_t;


/**********************/
/*****   TC->OS   *****/
/**********************/
typedef struct
{
    int32_t id;
    char name[NET_SIZE_COMP_NAME];
    int32_t state;
} COMPONENT_STATE_t;

typedef struct
{
    int32_t nComponents;
    COMPONENT_STATE_t component[N_COMP];
} MSG_TC_INFO_OS_t;

typedef struct
{
    char paramName[NET_SIZE_PARAM_NAME];   /* full name of the parameter   [-] */
    int32_t paramId;                          /* unique ID of the parameter   [-] */
    int32_t last;                             /* set to 1 for last parameter  [-] */
} MSG_DATAVIS_CFG_t;

typedef struct
{
    float time;
    float value[N_DATAVIS_PARAM];
} DATAVIS_PT_t;

typedef struct
{
    int32_t nPt;
    DATAVIS_PT_t pt[N_DATAVIS_PT_PER_SET];
} MSG_DATAVIS_SET_t;


/**********************/
/*****   OS->TC   *****/
/**********************/
typedef struct
{
    int paramId[N_DATAVIS_PARAM];   /* IDs of the parameters for visualization */
} MSG_DATAVIS_SEL_t;

/*************************/
/*****   TC->SCVIS   *****/
/*************************/
typedef struct
{
    char  name[NET_TEXT_SIZE]; /* name of the player        [-] */
    int32_t  id;                  /* player model ID           [-] */
    int32_t  type;                /* player type               [-] */
    double xyz[3];              /* player coordinates        [m] */
    float  hpr[3];              /* player attitude         [rad] */
    uint32_t statemask;           /* model state               [-] */
} SCVIS_PLAYER_STATE_t;

typedef struct
{
    double simTime;                         /* simulation time                    [s] */
    uint32_t frameNumber;                     /* frame number                       [-] */
    int32_t  nPlayer;                         /* number of valid players in message [-] */
    SCVIS_PLAYER_STATE_t pl[N_PLAYER_TRAF]; /* player entries                     [-] */
} MSG_TC_INFO_SCVIS_t;


/*************************/
/*****   SCVIS->TC   *****/
/*************************/
typedef struct
{
    int32_t mode;                   /* see SCVIS_MODE...                                    */
    float mouseXY[2];             /* relative mouse-position in window [-1.000f, +1.000f] */
} MSG_SCVIS_INFO_TC_t;

typedef struct
{
    char  name[NET_TEXT_SIZE];         /* name of the player       [-]      */
    double xy[2];                       /* x/y position of external player   */
    float  hdg;                         /* heading of external player        */
} MSG_PLAYER_INITPOS_t;

typedef struct
{
    char  name[NET_SIZE_PLAYER_NAME];  /* player to configure               */
    int32_t  type;                        /* type of configured parameter      */
    float  param[5];                    /* values of the parameter           */
} MSG_SCVIS_CFG_TRAFFIC_t;

/*************************/
/*****   SOUND->TC   *****/
/*************************/
typedef struct
{
    int32_t status;                 /* see TASK_STATE_ */
} MSG_SOUND_INFO_TC_t;

/*************************/
/*****   TC->SOUND   *****/
/*************************/
typedef struct
{
    float  speed;       /* speed                     [m/s]      */
    float  rpmEngine;   /* rpm of the engine         [1/s]      */
    float  slip;        /* wheel slip                [-]        */
    float  loadFactor;  /* normalized load factor    [0.0..1.0] */
    uint32_t envmask;     /* environment interaction state [-]    */
    uint32_t sysmask;     /* system state              [-]        */
} MSG_TC_INFO_SOUND_t;

/** This is the structure describing the properties of a sound object.
 *  The object is defined by ID and a type.
 *  Position, speed and attitude are defined in geo coordinates with 
 *  x-axis  positiv to east
 *  y-axis  positiv to north
 *  z-axis  positiv up
 *  hpr[0]  rotation around z-axis
 *  hpr[1]  rotation around y-axis
 *  hpr[2]  rotation around x-axis
 *  mask defines type specific states
 *  var contains type specific variables
 */
typedef struct
{
    int32_t  id;			        /* moving model ID		        [-]     */
    uint16_t type;		        /* model type		   	        [-]     */
    float  xyz[3];             /* moving model coordinates     [m]     */
    float  xyzDot[3];          /* speed                        [m/s]   */
    float  hpr[3];             /* moving model attitude        [rad]   */
    float  rps;                /* rpm of the engine            [1/s]   */
    float  load;               /* engine load factor           [%]     */
    uint32_t mask;	            /* mask for special sounds 	    [-]     */
    uint32_t sysmask;            /* system mask eg. SndFlagCar_e [-]     */
    float  var[3];             /* spare variables              [-]     */
} SND_OBJ_STATE_t;

/** This structure describes a .
 *  The object is defined by ID and a type.
 */
typedef struct
{
    uint16_t          roadType;           /* road type                [-]     */
    uint16_t          roadProperty;       /* road property            [-]     */
    uint32_t          roadFx;             /* road effects             [-]     */
    float           wheelSlip;          /* wheel slip               [%]     */
} SND_WHEEL_STATE_t;

typedef struct
{
    uint32_t              carType;            /* car type                 [-]     */
    SND_WHEEL_STATE_t   wheel[4];           /* wheel state              [%]     */
    uint32_t              sndmask1;           /* special sounds           [-]     */
    uint32_t              sndmask2;           /* special sounds           [-]     */
    SND_OBJ_STATE_t     car;                /* sound object info        [-]     */
} SND_CAR_STATE_t;

typedef struct
{   
    uint32_t              envmask;        /* environment state            [-] */
} SND_ENVIRONMENT_t;

typedef struct
{   
    uint16_t       id;        /* ID of the sound source        [-] */
    uint16_t       spare0;    /* for future use                [-] */
    float          gain;      /* individual gain of the source [-] */
    uint32_t       spare1[2]; /* for future use                [-] */
} SND_SINGLE_SOURCE_t;

/* ----------------------------------------------------- */
/* ------ BEGIN OF BACKWARD COMPATIBILITY SECTION ------ */

typedef struct
{
    int32_t nCp;          /* number of contact points        */
    float z[N_CP];      /* z-value of a contact point  [-] */
} MSG_IG_INFO_TC_t;

/* ------ END OF BACKWARD COMPATIBILITY SECTION ------ */
/* ----------------------------------------------------- */
/*************************/
/*****     TC->IG    *****/
/*************************/

typedef struct
{   float         precipitation;      /* precipitation scale parameter                    [0.0..1.0] */
    float         surfaceEffectScale; /* scale for surface effect like wet road           [0.0..1.0] */ /* was snow before */
    float         visibility;         /* visibility range                                        [m] */
    int32_t       cloudState;         /* CLOUD_STATE_XXX                                         [-] */
    int32_t       day;                /* day of sim. date                                        [-] */
    int32_t       month;              /* month of sim. date                                      [-] */
    int32_t       timeOfDay;          /* time of day at sim start                                [s] */
    uint32_t      flags;              /* IG_ENV_CFG_XXX                                          [-] */
    uint8_t       fogColor[3];        /* fog color (RGB)                                         [-] */
    float         shadowDist;         /* shadow display distance                                 [-] */
} MSG_ENVIRONMENT_t;

typedef struct
{
    __uint128_t      mask;               /* mask of valid receivers for subsequent msg contents     [-] */
} MSG_RECEIVER_MASK_t;

/*************************/
/*****     IG->TC    *****/
/*************************/

typedef struct
{
    uint32_t         width;          /* width of the image                           [pixel] */
    uint32_t         height;         /* height of the image                          [pixel] */
    uint16_t         pixelSize;      /* memory size of a pixel                         [bit] */
    uint16_t         pixelFormat;    /* format of a pixel              [IG_PIXEL_FORMAT_xxx] */
    uint32_t         imgSize;        /* total size of image                           [byte] */
} MSG_IG_IMG_TC_t;

/***************************/
/*****   TC->TRAFFIC   *****/
/***************************/
typedef struct
{
    int32_t  id;                   /* player model ID            [-] */
    double   xyz[3];               /* player coordinates         [m] */
    float    hpr[3];               /* player attitude          [rad] */
    float    speed[2];             /* speed in x and y         [m/s] */
    float    accel[2];             /* acceleration in x and y  [m/s] */
    uint32_t statemask;            /* model state                [-] */
    float    steering;             /* steering angle           [rad] */
} EXT_PLAYER_STATE_t;   

typedef struct
{
    double              simTime;                /* simulation time                             [s] */
    uint32_t              frameNumber;          /* frame number                                    */
    int32_t               nPlayer;              /* number of valid external players in message [-] */
    EXT_PLAYER_STATE_t  plExt[N_PLAYER_EXT];    /* external player structures                  [-] */
} MSG_TC_INFO_TRAF_t;

typedef struct
{
    int32_t id;                 /* player ID for which info is valid              [-] */
    float previewDistRules;   /* preview distance for signs, obstacles etc.     [s] */
} MSG_DRVR_INFO_TRAF_t;


/***************************/
/*****   TRAFFIC->TC   *****/
/***************************/
typedef struct
{
    int32_t  id;          /* player ID                     [-] */
    double   xyz[3];      /* player coordinates            [m] */
    float    hpr[3];      /* player attitude             [rad] */
    float    speed[2];    /* speed in xg and yg          [m/s] */
    float    accel[2];    /* acceleration in xg and yg  [m/s2] */
    int32_t  lane;        /* lane ID                       [-] */
    float    angle;       /* lane angle                  [rad] */
    float    offset;      /* lane offset                   [m] */
    uint32_t statemask;   /* moving model state            [-] */
    float    steering;    /* steering angle              [rad] */
} PLAYER_STATE_t;

typedef struct  // the following object state replaces the previous PLAYER_STATE_t starting TC 3.6
{
    int32_t  id;          /* object ID                               [-] */
    double   xyz[3];      /* object coordinates                      [m] */
    float    hpr[3];      /* object attitude                       [rad] */
    float    speed[2];    /* speed in xg and yg                    [m/s] */
    float    accel[2];    /* acceleration in xg and yg            [m/s2] */
    int8_t   lane;        /* lane ID                                 [-] */
    uint8_t  spare0;      /* spare                                   [-] */
    uint16_t flags;       /* flags for object handling     [OBJECT_FLAG] */
    float    angle;       /* lane angle                            [rad] */
    float    offset;      /* lane offset                             [m] */
    uint32_t statemask;   /* moving model state                      [-] */
    float    steering;    /* steering angle                        [rad] */
    uint32_t spare1[4];   /* yet another spare                       [-] */
} OBJECT_STATE_t;

typedef struct  /* player state relative to given driver */
{
    int32_t id;           /* player ID for which info is valid                                         [-] */
    float tComp;        /* lateral offset to ownship moving along path                                   */
                        /* compensated for driving direction                                         [m] */
    float sDist;        /* longitudinal distance to ownship moving along path                            */
} PLAYER_REL_STATE_t;

typedef struct
{
    int32_t id;                                                      /* player ID for which info is valid                                         [-]*/
    float previewDistRules;                                          /* preview distance for signs, obstacles etc.                                [s] */
    float maxSpeedFromRules;                                         /* maximum speed from traffic rules                                        [m/s] */
    float distToMaxSpeed;                                            /* distance to maximum speed from traffic rules                              [m] */
    int32_t turnDir;                                                 /* dir of road at preview dist, see                     [DYN_INPUT_TURN_DIR_xxx] */
    int32_t noActions;                                               /* number of valid driver actions                                            [-] */
    DRIVER_ACTION_t action[DYN_DRVR_N_ACTIONS];                      /* list of driver actions                                                    [-] */
    int32_t noRelPlayers;                                            /* number of relative players                                                [-] */
    PLAYER_REL_STATE_t playerRel[N_PLAYER_TRAF+NET_N_PEDESTRIANS];   /* state information relative to own player                                  [-] */
} MSG_TRAF_INFO_DRVR_t;

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
} MSG_TRAF_INFO_DRVR_CTRL_t;

typedef struct
{
    uint32_t playerId;                                           /* unique player ID to which the controls apply         @unit _                        */
    float    steeringWheel;                                      /* steering wheel angle                                 @unit rad                      */
    float    steeringSpeed;                                      /* steering speed                                       @unit rad/s                    */
    float    throttlePedal;                                      /* throttle pedal position                              @unit [0.0..1.0]               */
    float    brakePedal;                                         /* brake pedal position                                 @unit [0.0..1.0]               */
    float    clutchPedal;                                        /* clutch pedal position                                @unit [0.0..1.0]               */
    float    accelTgt;                                           /* desired acceleration                                 @unit m/s2                     */
    float    steeringTgt;                                        /* desired steering angle at wheels                     @unit rad                      */
    double   curvatureTgt;                                       /* desired resulting curvature of the lateral motion    @unit 1/m                      */
    float    steeringTorque;                                     /* torque at steering wheel                             @unit Nm                       */ 
    float    engineTorqueTgt;                                    /* target engine torque                                 @unit Nm                       */ 
    float    speedTgt;                                           /* target speed                                         @unit m/s                      */ 
    uint8_t  gear;                                               /* desired gear box position                            @unit DRVR_GEAR_BOX_POS        */
    uint8_t  sourceId;                                           /* unique number of the source providing this input     @unit _                        */
    uint8_t  spare0[2];                                          /* some spares for future use                           @unit _                        */
    uint32_t validityFlags;                                      /* flags which of the above inputs are valid            @unit DRVR_INPUT_VALIDITY      */
    uint32_t flags;                                              /* input flags (indicator etc.)                         @unit DRVR_FLAG                */
    uint32_t mockupInput0;                                       /* flags resulting from mockup buttons, part 1          @unit _                        */
    uint32_t mockupInput1;                                       /* flags resulting from mockup buttons, part 2          @unit _                        */
    uint32_t mockupInput2;                                       /* flags resulting from mockup buttons, part 3          @unit _                        */
    uint32_t spare;                                              /* some spare for future use                            @unit _                        */
} MSG_DRIVER_CTRL_t;

typedef struct
{
    int32_t  id;                                                /* unique ID of a traffic light                                               [-] */
    uint32_t stateMask;                                         /* traffic light's state mask                                                 [-] */
} TRLIGHT_STATE_t;

typedef struct
{
    int32_t nTrLights;                                                /* number of valid traffic lights in message                                 [-]*/
    TRLIGHT_STATE_t trLight[NET_N_TRLIGHTS];                         /* state information about individual traffic lights                         [-]*/
} MSG_TRAF_INFO_TRLIGHT_t;

/* ------ traffic light state update ------ */
typedef struct
{
    int32_t    id;                                            /* unique ID of a traffic light                                               [-] */
    uint32_t   stateMask;                                     /* traffic light's state mask                                                 [-] */
    float      state;                                         /* current state in phase cycle                                        [0.0..1.0] */
    uint8_t    flags;                                         /* additional flags for certain behavior                                      [-] */
    int8_t     spare;                                         /* you never know....                                                         [-] */
    int16_t    spare1;                                        /* you never know....                                                         [-] */
} MSG_TRLIGHT_UPDATE_t;

/* ------ traffic light state update ------ */
typedef struct
{
    uint32_t  playerId;                                        /* unique player ID                                                           [-]     */
    double    xyz[3];                                          /* xyz position of steering point                                             [m/m/m] */
    double    targetTime;                                      /* foresight time when steering point will be met                             [s]     */
    int32_t   spare[6];                                        /* you never know....                                                         [-]     */
} MSG_STEERING_POINT_t;

/* ------ pedestrian animation data ------ */
typedef struct
{
    uint32_t            playerId;    /**< unique player ID                                                        @unit _                 */
    NET_COORD_DOUBLE_t  pos;         /**< real-world position and orientation of reference point32_t              @unit m,m,m,rad,rad,rad */
    uint32_t            spare[4];    /**< some more spares                                                        @unit _                 */
    uint32_t            featureMask; /** features like visibility etc.                                            [PED_FEATURE_xxx]       */
    uint32_t            noCoords;    /**< number of valid co-ordinates in coord array                             @unit _                 */
    uint32_t            dataSize;    /**< size of the following data containing the actual co-ordinates           @unit byte              */
} MSG_PED_ANIMATION_t;

/*******************************/
/*****   TC->INSTRUMENTS   *****/
/*******************************/
typedef struct
{
    float  speed;       /* speed                     [m/s] */
    float  rpmEngine;   /* rpm of the engine         [1/s] */
    uint32_t sysMask;     /* system states               [-] */
    uint32_t spare[5];   
} MSG_TC_INFO_INST_t;

/*******************************/
/*****   TRAFFIC->TC->IG   *****/
/*******************************/
typedef struct
{
    int16_t  playerId;       /* ID of the player to which the wheel belongs [-] */
    int16_t  wheelId;        /* ID of the wheel within the player           [-] */
    float  deflZ;          /* deflection in z direction                   [m] */
    float  rotAngle;       /* angle of rotation                         [rad] */
    int32_t  spare0;         /* reserved for future use                         */
} MSG_MM_WHEEL_t;


typedef struct
{
    uint8_t compressionType; /** Compression type see COMPRESS* */
    uint8_t spare0[3];        /** reserved for future use        */
    uint32_t uncompressedSize; /** full size of the data        */
    uint32_t spare1[2];        /** reserved for future use      */
}
MSG_COMPRESSED_t;

typedef struct 
{
    uint16_t numPackages; /** Amount of MSG_PKG_VEC_t that were part of this frame */
    uint16_t spare[7];    /** reserved for future use - set to zero */
} MSG_END_OF_FRAME_REV11_t;

/*****************************************/
/*****  ALL->ALL new package format  *****/
/*****************************************/
typedef struct
{
    uint32_t hdrSize;        /* size of this header structure when transmitted                               [byte] */
    uint32_t dataSize;       /* size of data following this package header                                   [byte] */
    uint32_t elementSize;    /* if data following the header contains an array of elements:                  [byte] */
                             /* size of one element in this data                                                    */
                             /* (elementSize is equivalent to dataSize if only one element is transmitted)          */
    uint16_t pkgId;          /* package identifier (type of package)                                            [-] */
    uint16_t dataVersion;    /* version number of data block                                                    [-] */
} MSG_VEC_ENTRY_HDR_t;

typedef struct
{
    uint16_t  magicNo;    /* must be VT_MAGIC_NO                                                           [-] */
    uint16_t  version;    /* upper byte = major, lower byte = minor                                        [-] */
    uint32_t  frameNo;    /* number of the simulation frame                                                [-] */
    double    simTime;    /* simulation time                                                               [s] */
    uint32_t  hdrSize;    /* size of this header structure when transmitted                             [byte] */
    uint32_t dataSize;    /* size of data following this package header                                 [byte] */
} MSG_PKG_VEC_t;    

typedef struct 
{
    uint64_t mask[2];     /* 128 bit wide channel mask of the sending ig 0 is low, 1 is high */
    uint64_t reserved[2]; /* reserved for future use - should be zero */
} MSG_IG_CHANNEL_MASK_t;

typedef struct
{
    uint16_t id;           /*id of the fragmented package, unique within a frame to avoid overlap */
    uint16_t fragmentNo;   /*id of the current fragment, reassembly in numeric order */
    uint16_t numFragments; /*total number of fragments */
    uint16_t spare[5];
} MSG_FRAGMENT_t;

typedef struct
{
    uint32_t id;                   /* id of the player this information belongs to */
    NET_COORD_DOUBLE_t position;   /* coordinates of the object */
    NET_COORD_STRUCT velocity;     /* velocity of the object */
    NET_COORD_STRUCT acceleration; /* acceleration of the object */
} MSG_MM_STATE_EXT_t;

typedef struct
{
    uint32_t id;                 /* id of the object this information belongs to */
    uint16_t type;               /* scope of the id, rdb symbol, camera, light source */
    uint16_t spare[3];
    uint32_t playerId;           /* id of the player this object is relative to or 0 if not */
    NET_COORD_DOUBLE_t offset;   /* coordinates of the object, either absolute or relative */
} MSG_OBJECT_POSITION_INFO_t;

/*****************************/
/*****   MESSAGE UNION   *****/
/*****************************/
typedef union
{                                                                                    
    MSG_ACTION_t            action;        // also in COM_MSG_DATA_PUB_u               
    MSG_CMD_t               cmd;           // also in COM_MSG_DATA_PUB_u               
    MSG_TASK_STATE_t        taskState;     // also in COM_MSG_DATA_PUB_u
    MSG_PLAYER_CFG_t        playerCfg;     // also in COM_MSG_DATA_PUB_u
    MSG_TC_INFO_DYN_t       tcInfoDyn;     // also in COM_MSG_DATA_PUB_u
    MSG_DYN_INFO_TC_t       dynInfoTc;     // also in COM_MSG_DATA_PUB_u
    MSG_IG_TRIGGER_t        igTrigger;
    MSG_TC_INFO_OS_t        tcInfoOs;
    MSG_ENVIRONMENT_t       env;         // for backward compatibility only
    MSG_IG_INFO_TC_t        igInfoTc;    // for backward compatibility only
    MSG_TC_INFO_SCVIS_t     tcInfoScVis;
    MSG_SCVIS_INFO_TC_t     scVisInfoTc;
    MSG_PLAYER_INITPOS_t    playerInitPos;
    MSG_DATAVIS_CFG_t       dataVisCfg;
    MSG_DATAVIS_SEL_t       dataVisSel;
    MSG_DATAVIS_SET_t       dataVisSet;
    MSG_SOUND_INFO_TC_t     soundInfoTc;                                                        
    MSG_TC_INFO_SOUND_t     tcInfoSound;
    MSG_TC_INFO_TRAF_t      tcInfoTraf;
    MSG_SCVIS_CFG_TRAFFIC_t scVisCfgTraf;
    MSG_DYN_PLAYER_CFG_t    dynPlayerCfg;
    MSG_DYN_PLAYER_RESET_t  dynPlayerReset;
    MSG_PATH_CFG_t          pathCfg;
    MSG_TRAF_INFO_DRVR_t    trafInfoDrvr;
    MSG_DRVR_INFO_TRAF_t    drvrInfoTraf;
    MSG_IG_IMG_TC_t         igImgTc;
    MSG_TC_CTRL_IG_t        tcCtrlIg;
    MSG_DYN_CFG_TC_t        dynCfgTc;
    MSG_TRAF_INFO_TRLIGHT_t trafInfoTrLight;
    MSG_TC_INFO_INST_t      tcInfoInst;
    MSG_TRLIGHT_UPDATE_t    trLightUpdate;
    MSG_RECEIVER_MASK_t     receiverMask; 
    MSG_TC_INFO_IG_REV10_t  tcInfoIg10;
    MSG_IG_CHANNEL_MASK_t   igChannelMask;
} COM_MSG_DATA_u;


/***********************/
/*****   MESSAGE   *****/
/***********************/
typedef struct
{
    COM_MSG_HEADER_t hdr;
    COM_MSG_DATA_u     u;
} COM_MSG_t;

#endif        /* _VT_ICD_H */

// end of pragma 4
#pragma pack(pop)

