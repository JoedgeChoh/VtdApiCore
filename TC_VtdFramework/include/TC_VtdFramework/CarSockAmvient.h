/* ===================================================
 *  file:       CarSockAmvient.hh
 * ---------------------------------------------------
 *  purpose:	interface to the Amvient mockup
 * ---------------------------------------------------
 *  first edit:	08.10.2009 by M. Dupuis @ VIRES GmbH
 *  last mod.:  08.10.2009 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef CAR_SOCK_AMVIENT_H
#define CAR_SOCK_AMVIENT_H

typedef int				sint32;
typedef short			sint16;
typedef unsigned int	uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint8;
typedef char			sint8;
typedef float			float16;

// data package display in car's instrument
// Datagram Socket (Multicast) with:
//
//	IP=230.0.0.1
//	Port=4001

typedef struct
{
	char strVersionInfo[32];	// version info (ignored)                 [-]
	uint32 nGWSZ;				// total travel length in                 [km]
	uint32 nTWSZ;				// trip length                            [km]
	uint16 sSpeedGauge;			// speed                                  [0.1 km/h]
	uint16 sRevGauge;			// engine speed                           [rpm]
	uint16 sConsumptionGauge;	// current consumption                    [l/100km]
	sint16 sOilTemperature;		// oil temperature                        [0.1 deg C]
	uint16 sFuelGauge;			// fuel gauge                             [%]
	uint16 sFuelDigital;        // fuel amount                            [0.1l]
	uint8  cGearMode;           // automatic gear position as ASCII value ['P' 'R' 'N' 'D' 'S'  'M']
	uint8  cGear;               // manual gear position                   [1..6 = M1..M6]
	uint8  cLampState;          // lamp state (bit mask)                  [1=indicator left, 2=indicator right, 4=low beam, 8=high beam, 16=fog light rear, 32=fog light front]
	uint8  reserved0;           // 
	uint8  reserved1;           // 
	uint8  reserved2;           //
	uint8  reserved3;           //
} Instrument_t;

// data package for driver inputs
// Datagram Socket (Multicast) with:
//
//	IP=230.0.0.1
//	Port=4001
typedef struct
{
	char    strVersionInfo[32];	 // version info (ignored)                 [-]
	uint8   cLSH_Blinker;        // indicator / light handle bit mask      [0=Neutral, 1=indicator left, 2=indicator right, 4=high beam]
	uint8   cLightSwitch;        // light switch                           [0=Off, 1=auto, 2=low beam, 4=fog light front, 8=fog light rear]
	uint8   cBrakePedalPos;		 // brake pedal position:                  [0-254 (min-max), 255: invalid]
	uint8   cThrottlePedalPos;	 // throttle pedal position:               [0-254 (min-max), 255: invalid]
	float16 sSteeringWheelAngle; // steering wheel angle                   [rad]
	uint8   reserved0;			 //
	uint8   reserved1;			 //
	uint8   reserved2;			 //
	uint8   reserved3;			 //
} Driver_t;


// shared memory structure for fast transfer of viewer position
// from tracker to application
#define SHM_AMVIENT_KEY	0x081009

typedef struct
{	
    /* status values */
    unsigned int watchdog;          /* watchdog counter                                    [-] */
    unsigned int status;            /* sensor state                                        [-] */
                                    /* != 0 if something is failed                             */
    double  eyeOffXYZ[3];           /* head offset position in player co-ordinates         [m] */
    double  eyeOffHPR[3];           /* head offset attitude in player co-ordinates       [rad] */

    /* additional spare parameters */
    float   parameter[10];          /* spare parameters                                    [?] */
    
} Amv_Shm_t;

#endif
