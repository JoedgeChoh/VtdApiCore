/////////////////////////////////////////////////////////////////////////////////
// Datei:        CarSock.h
//
// Beschreibung: Header-Datei zum Datenaustausch zwischen Interface-Applikation
//               f�r Kombi-Anzeige/Lenkradbedienung und Fahrsimulation
//
// Autor:        Dr. Robert Neuss, Usaneers GmbH
// Datum:        20.7.2007
/////////////////////////////////////////////////////////////////////////////////


// Datenpaket f�r Anzeigen im Kombi-Instrument
// Datagram Socket (Multicast) mit:
//
//	IP=230.0.0.1
//	Port=4001

#ifndef CAR_SOCK_H
#define CAR_SOCK_H

typedef int				sint32;
typedef short			sint16;
typedef unsigned int	uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint8;
typedef char			sint8;

typedef struct
{
	char strVersionInfo[32];	// Versionsinfo (wird momentan nicht verwendet)
	uint32 nGWSZ;				// Gesamtwegstrecke in 1km bzw. 1mile
	uint32 nTWSZ;				// Tageswegstrecke in 0.1km bzw. 1mile
	uint16 sSpeedGauge;			// Geschw. analog in 0.1 km/h
	uint16 sRevGauge;			// Mot. Drehzahl analog in 1 rpm
	uint16 sConsumptionGauge;	// Momentanverbrauch analog in Liter
	sint16 sAmbientTemperature;	// Aussentemperatur digital in 0.1 Grad C bzw. 0.1 Grad F
	sint16 sEngineTemperature;	// Kuehlwassertemperatur digital in 0.1 Grad C bzw. 0.1 Grad F
	sint16 sOilTemperature;		// Oeltemperatur digital in 0.1 Grad C bzw. 0.1 Grad F
	uint16 sFuelGauge;			// Tankinhalt analog in  %
	uint16 sFuelDigital;		// Tankanzeige digital in 0.1Liter bzw. 0.1Galonen
	uint16 sCruiseControlSpeed;	// 0..260.0 km/h (mls ???
	uint8 cGearMode;			// Automatik-Getriebestellung als ASCII Wert: 'P' 'R' 'N' 'D' 'S'  'M'
	uint8 cGear;				// 1..6 = M1..M6 (Wird nur bei Getriebestellung 'M' angezeigt)
	uint8 cTerminalState;		// Klemmenstatus 1=R 2=15 4=50  (Anzeige des Bordcomputer-Displays erst ab Kl. R)
	uint8 cLampState;			// Lichtstatus: 1=Blinker links, 2=Blinker rechts, 4=Fernlicht, 8=Nebelschlu�leuchte, 16=Nebelscheinwerfer
	uint8 cStatus;				// Kammernleuchten: 1=DSC
	uint8 cACC;					// Bitfeld ACC-Status: 1=ACC-Seitenbalken, 2=Fahrzeug gelb, 4=Fahrzeug rot, 8=Balken 1, 16=Balken 2, 32=Balken 3, 64=Balken 4, 128=Geschwindigkeit digital anzeigen
	uint8 reserved0;			// 
	uint8 reserved1;			// 
	uint8 reserved2;			//
	uint8 vtFlags;    		    //

} SKombiInstrument;

#define SKOMBI_INSTRUMENT_LENGTH 68

// Datenpaket f�r Eingaben des Fahrers
// derzeit nur Schaltzentrum Lenks�ule (Lenkstockhebel) ohne Tasten am Multifunktionslenkrad
// Datagram Socket (Multicast) mit:
//
//	IP=230.0.0.1
//	Port=4001

typedef struct
{
	char strVersionInfo[32];	// Versionsinfo (wird momentan nicht verwendet)
	uint8 cLSH_ACC;				// 0=Neutral, 1=+1, 2=-1. 4=+10, 8=-10, 16=Resume, 32=OFF, 64= WheelDown, 128= WheelUp
	uint8 cLSH_Blinker;			// 0=Neutral, 1=Links, 2=Rechts, 4=Fernlicht, 8=Lichthupe, 16=BC oben, 32=BC unten (CC), 64= Tip
	uint8 cLSH_Wischer;			// Bit 0+1={mitte, oben, ganz oben, unten}, Bit 2+3={vorne, Mitte, hinten, ganz hinten}, Bit 4+5=Intervall {0,1,2,3}, Bit 6=Resume
	uint8 cBrakePadelPos;		// Stellung des Bremspedals: 0-254 (min-maximal durchgetreten), 255: ung�ltig
	uint8 cThrottlePadelPos;	// Stellung des Gaspedals: 0-254 (min-maximal durchgetreten) , 255: ung�ltig
	uint8 reserved2;			//
	uint8 reserved3;			//
} SLenkrad;

#define SLENKRAD_LENGTH 39

#endif
