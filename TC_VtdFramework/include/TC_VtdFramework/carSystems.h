/********************************************************
* 	SMART simulator car systems definitions		        *
*-------------------------------------------------------*
* (c) VIRES			            Author: Wunibald Karl   *
* Last Modification:                    30.01.05 / Ka	*
********************************************************/

#ifndef _CAR_SYSTEMS_H
#define _CAR_SYSTEMS_H

/*------------------------------------------------------------------------------
 * INCLUDES
 *----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 * DEFINES
 *----------------------------------------------------------------------------*/
typedef enum 
{	STATE_FAIL		= -1,
	STATE_OFF		= 0,
	STATE_ON		= 1,
	STATE_STARTING,
	STATE_INIT,
	STATE_INIT_OFF,
	STATE_INIT_STANDING,
	STATE_INIT_DRIVING,
	STATE_STANDING,
	STATE_DRIVING,
	STATE_CRASHED
}	SYS_STATE_e;


/*****   ELECTRIC   *****/
#define ELE_STATE_OFF			    0
#define ELE_STATE_ON			    1

#define ELE_STATE_POWERED		    1

#define ELE_STATE_HEADLIGHT_PARK	1
#define ELE_STATE_HEADLIGHT_LOW		2
#define ELE_STATE_HEADLIGHT_HIGH	3

#define ELE_STATE_INDICATOR_LEFT	1
#define ELE_STATE_INDICATOR_RIGHT	2
#define ELE_STATE_INDICATOR_WARN	3

#define ELE_STATE_WIPER_INTERVALL	1
#define ELE_STATE_WIPER_LOW		    2
#define ELE_STATE_WIPER_HIGH		3



/*------------------------------------------------------------------------------
 * STRUCTURES
 *----------------------------------------------------------------------------*/
typedef struct
{	
	/*****   states   *****/
	SYS_STATE_e	sysState;	        /* system state			    [-]	*/
		
	int	powered;		            /* system power state		[-]	*/

	int	stateStarter;		        /* state starter		    [-]	*/
		
	int	stateHeadlight;		        /* state headlight 		    [-]	*/
	int	stateBrakelight;	        /* state brakelight		    [-]	*/
	int	stateRearlight;		        /* state rearlight		    [-]	*/
	int	stateFoglightFront;	        /* state foglight front		[-]	*/

	int	stateIndicator;		        /* state indicator		    [-]	*/
	int stateWarnRelay; 		    /* warning relay state		[-]	*/
	int	stateIndicatorRelay;	    /* state indicator relay	[-]	*/
	double	timeIndicatorRelayOn;	/* time switched on relay	[s]	*/
	
	int	stateWiperFront;	        /* state wiper front		[-]	*/
	int	stateWiperRear;		        /* state wiper rear		    [-]	*/
	int	statePumpFront;		        /* state pump front		    [-]	*/

	int	stateHorn;		            /* state pump rear		    [-]	*/

	int	stateGearShift;		        /* state gear shift		    [-]	*/
	int stateDoorLock;			    /* state door lock switch	[-]	*/


	/*****   cockpit indication lights   *****/
	double  timeCtrlCheckStart;	    /* starttime for check ctrls 	[-] */
	int 	stateCtrlIndicator;	    /* indicator light  	    	[-] */
	int 	stateCtrlBattery;   	/* battery light		        [-] */
	int 	stateCtrlOilPressure;	/* oilpressure light	    	[-] */
	int 	stateCtrlEngine;    	/* engine electronics light     [-] */
	int 	stateCtrlPreHeat;   	/* diesel engine preheat light  [-] */
	int 	stateCtrlHighbeam;  	/* highbeam light		        [-] */
	int 	stateCtrlBrakeHandle;  	/* handbrake light	    	    [-]	*/
	int 	stateCtrlABS;		    /* ABS light		    	    [-]	*/
	int 	stateCtrlAirbag;    	/* airbag light		    	    [-]	*/
	
#if 0
	/*****   not yet used   *****/
	int	statePumpRear;		        /* state pump rear		    [-]	*/
	int	stateFoglightRear;	        /* state foglight rear		[-]	*/
	int	stateCharging;		        /* state charging		    [-]	*/
	float	voltageBattery;		    /* battery voltage		    [V]	*/
	float	voltageCharger;		    /* charger voltage		    [V]	*/
#endif
}	ELECTRIC_t;



typedef struct
{	
	/*****   states   *****/
	SYS_STATE_e	sysState;	        /* system state			    [-]	    */
		
	float	rps;			        /* engine rounds per second	[1/s]	*/
	float	load;			        /* engine load	            [%]	    */
	float	oilPressure;		    /* oil pressure			    [-]	    */

}	ENGINE_t;


/*------------------------------------------------------------------------------
 * PROTOTYPES
 *----------------------------------------------------------------------------*/

extern void        elecInit(SYS_STATE_e state, ELECTRIC_t *data);
extern SYS_STATE_e elecUpdate(	double	   time,
				SMART_IF_t *ifData, 
				ELECTRIC_t *elecData,
				ENGINE_t   *engData);
extern void elecExit(ELECTRIC_t *data);

extern void        engInit(SYS_STATE_e state, ENGINE_t *data);
extern SYS_STATE_e engUpdate(	double	   time,
				SMART_IF_t *ifData, 
				ELECTRIC_t *elecData,
				ENGINE_t   *engData);
extern void engExit(ENGINE_t *data);


#endif		/* _CAR_SYSTEMS_H */

/*----------------------------------------------------------------------------
 			END OF FILE
----------------------------------------------------------------------------*/
