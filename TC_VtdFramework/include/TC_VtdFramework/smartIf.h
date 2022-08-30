/********************************************************
* SMART INTERFACE DATA				                	*
*-------------------------------------------------------*
* (c) VIRES			            Author: Wunibald Karl	*
* Last Modification:                    13.10.06 / Ka   *
********************************************************/

#ifndef _SMART_IF_H
#define _SMART_IF_H

/*------------------------------------------------------------------------------
 * INCLUDES
 *----------------------------------------------------------------------------*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

/*------------------------------------------------------------------------------
 * DEFINES
 *----------------------------------------------------------------------------*/

/*****   SMART ICD BIT DEFINES   *****/
#define	BIT_INDICATOR_R		    0x00000001
#define	BIT_INDICATOR_L		    0x00000002
#define	BIT_LIGHT_PARK		    0x00000004
#define	BIT_LIGHT_LOWBEAM	    0x00000008
#define	BIT_LIGHT_HIGHBEAM	    0x00000010
#define	BIT_LIGHT_FOG		    0x00000020
#define	BIT_WIPER_LOW		    0x00000040
#define	BIT_WIPER_HIGH		    0x00000080
#define	BIT_WIPER_INTERVAL	    0x00000100
#define	BIT_WIPER_REAR		    0x00000200
#define	BIT_WATERPUMP		    0x00000400
#define	BIT_WARN		        0x00000800
#define	BIT_DOOR_LOCK		    0x00001000
#define	BIT_HORN		        0x00002000
#define	BIT_KEY_START		    0x00004000
#define	BIT_KEY_POWERED		    0x00008000
#define	BIT_GEARSWITCH_N	    0x00010000
#define	BIT_GEARSWITCH_R	    0x00020000
#define	BIT_GEARSWITCH_UP	    0x00040000
#define	BIT_GEARSWITCH_M	    0x00080000
#define	BIT_GEARSWITCH_DOWN	    0x00100000

#define BIT_LAMP_INDICATOR	    0x00000001
#define BIT_LAMP_BATTERYLOAD	0x00000002
#define BIT_LAMP_OIL_PRESS	    0x00000004
#define BIT_LAMP_MOTORELECTRIC	0x00000008
#define BIT_LAMP_GLOW		    0x00000010
#define BIT_LAMP_HIGHBEAM	    0x00000020
#define BIT_LAMP_HANDBRAKE	    0x00000040
#define BIT_LAMP_ABS		    0x00000080
#define BIT_LAMP_AIRBAG		    0x00000100

/*------------------------------------------------------------------------------
 * STRUCTURES
 *----------------------------------------------------------------------------*/
typedef struct 
{	
	/* CAN message data */
	uint	switches;		    /* buttons and switches		    [-]	*/
	uint	lamps;			    /* buttons and switches		    [-]	*/
	float	rawSteering;		/* steering angle 		        [%]	*/
	float	rawAccelerator;		/* accelerator pedal		    [%]	*/
	float	rawBrake;		    /* brake pedal			        [%]	*/
	float	rawHandbrake;		/* handbrake			        [%]	*/
	float	indSpeed;		    /* speed indication		        [km/h]	*/
	char	line1[20];		    /* ASCII text output lines	    [-]	*/
	char	line2[20];		    /* !! only 16 chars per line	[-]	*/

	/* simulation control and indication data */
	uint	stateChangeFlag;	/* input buttons changed flag	[-]	*/

	int 	stateIndicator; 	/* indicator state L/R  -1/1	[-]	*/
	int 	stateWarnLight; 	/* warning indicator		    [-]	*/
	int 	stateLight;		    /* headlight state		        [-]	*/
	int	    stateFogLight;  	/* fog light state		        [-]	*/
	int	    stateWiperFront;	/* front wiper state		    [-]	*/
	int	    stateWiperRear; 	/* rear wiper state		        [-]	*/
	int	    stateWaterpump; 	/* state water pump		        [-]	*/
	int	    stateHorn;		    /* state horn			        [-]	*/
	int	    stateKey;		    /* state key 			        [-]	*/
	int	    stateGearShift;		/* state gear shift		        [-]	*/
	int 	stateDoorLock;		/* state door lock switch	    [-]	*/
	
	float	steering;		    /* steering angle 		        [%]	*/
	float	accelerator;		/* accelerator pedal		    [%]	*/
	float	brake;			    /* brake pedal			        [%]	*/
	float	handbrake;		    /* handbrake			        [%] */
	float	speed;			    /* speed indication		        [m/s]	*/

}	SMART_IF_t;

/*------------------------------------------------------------------------------
 * PROTOTYPES
 *----------------------------------------------------------------------------*/


#endif		/* _SMART_IF_H */

/*----------------------------------------------------------------------------
 			END OF FILE
----------------------------------------------------------------------------*/
