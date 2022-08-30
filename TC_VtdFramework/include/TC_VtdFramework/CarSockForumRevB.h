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

#include <stdint.h>

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
	char strVersionInfo[31];	        // Versionsinfo (wird momentan nicht verwendet)
    uint8  cKombiVersion;               // 0=Startbildschirm, 1=Public Design, 2=A4, 3=Q5, 4=R8
	uint32 nGWSZ;				        // Gesamtwegstrecke in 1km bzw. 1mile
	uint32 nTWSZ;				        // Tageswegstrecke in 0.1km bzw. 1mile
	uint16 sSpeedGauge;			        // Geschw. analog in 0.1 km/h
	uint16 sRevGauge;			        // Mot. Drehzahl analog in 1 rpm
	uint16 sConsumptionGauge;	        // Momentanverbrauch analog in Liter
	sint16 sAmbientTemperature;	        // Aussentemperatur digital in 0.1 Grad C bzw. 0.1 Grad F
	sint16 sEngineTemperature;	        // Kuehlwassertemperatur digital in 0.1 Grad C bzw. 0.1 Grad F
	sint16 sOilTemperature;		        // Oeltemperatur digital in 0.1 Grad C bzw. 0.1 Grad F
	uint16 sFuelGauge;			        // Tankinhalt analog in  %
	uint16 sFuelDigital;		        // Tankanzeige digital in 0.1Liter bzw. 0.1Galonen
	uint16 sCruiseControlSpeed;	        // 0..260.0 km/h (mls ???
	uint8 cGearMode;			        // Automatik-Getriebestellung als ASCII Wert: 'P' 'R' 'N' 'D' 'S'  'M'
	uint8 cGear;				        // 1..6 = M1..M6 (Wird nur bei Getriebestellung 'M' angezeigt)
	uint8 cTerminalState;		        // Klemmenstatus 1=R 2=15 4=50  (Anzeige des Bordcomputer-Displays erst ab Kl. R)
	uint8 cLampState;			        // Lichtstatus: 1=Blinker links, 2=Blinker rechts, 4=Fernlicht, 8=Nebelschlu�leuchte, 16=Nebelscheinwerfer
	uint8 cStatus;				        // Kammernleuchten: 1=DSC
	uint8 cACC;					        // Bitfeld ACC-Status: 1=ACC-Seitenbalken, 2=Fahrzeug gelb, 4=Fahrzeug rot, 8=Balken 1, 16=Balken 2, 32=Balken 3, 64=Balken 4, 128=Geschwindigkeit digital anzeigen
	uint8 cDSC;					        // DSC-Status Bits 0-1: 0=nix, 1=DSC-Leuchte gelb, 2=DSC-Leuchte rot, ASR-Status Bits 2-3: 0=nix, 1(4)=ASR-Leuchte gelb, 2(8)=ASR/Leuchte rot
	uint8 reserved1;			        // 
	uint8 reserved2;			        //
	uint8 reserved3;			        //
	// AUDI ACC packages
    uint16_t ui16ACC_Abstandsindex;         // represents the current destination distance @ values 0...1023
    uint8_t  ui8ACC_Status_Anzeige;         // represents the current state of the acc @values 0...8
    uint8_t  ui8ACC_Status_Prim_Anz;        // displays the primary status in different colors  @values 0..3
    uint8_t  ui8ACC_Status_Zusatzanz;       // additional display (middle display) of pictures and text @values 0...6
    uint8_t  bACC_Tachokranz;               // shows the red lights around the speed display (bool)
    uint8_t  ui8ACC_Texte;                  // additional text information e.g. ACC not available @values 0...10
    uint8_t  ui8ACC_Texte_Primaeranz;       // several information about acc e.g. CAR_ _ _CAR - symbols, ACC ready,.... @attention very important @values 0...31
    uint8_t  ui8ACC_Texte_Zusatzanz;        // some information about acc states and distance  @values 0...20
    //float64  f64ACC_Wunschgeschw;           // displays the red symbol around the speed display and shows the destination speed @ headup, ersetzt durch sCruiseControlSpeed
    // AUDI Heading Control packages        
    uint8_t bLDW_Status_LED_gelb;           // displays the yellow HCA display
    uint8_t bLDW_Status_LED_gruen;          // displays the green HCA display
    uint8_t ui8LDW_Texte;                   // displays HCA text information e.g. FahrerÃ¼bernahme @values 0...4
    uint8_t ui8HCA_01_Status_HCA;           // represents the status of HCA  @values 0...15
    // AUDI Pre Sense packages              
    uint8_t bOptischeWarnung;               // dedicated signal to 
    uint8_t ui8ACC_Texte_braking_guard;     // sends out the Warning text to the middle display 
    // AUDI Verkehrszeichenerkennung
    uint8_t ui8VZE_Hinweistext;             // sends out a text over an internal hashtable @values 0...7
    uint8_t ui8VZE_Anzeigemodus;            // activates the different types of displaying the information  @values 0...3
    uint8_t ui8VZE_Zusatzschild_1;          // additional sign to @ref ui8_VZE_Verkehrszeichen_1
    uint8_t ui8VZE_Zusatzschild_2;          // additional sign to @ref ui8_VZE_Verkehrszeichen_2
    uint8_t ui8VZE_Zusatzschild_3;          // additional sign to @ref ui8_VZE_Verkehrszeichen_3
    uint8_t bVZE_Warnung_Verkehrszeichen_1; // warning symbol for traffic sign @ref ui8_VZE_Verkehrszeichen_1
    uint8_t bVZE_Warnung_Verkehrszeichen_2; // warning symbol for traffic sign @ref ui8_VZE_Verkehrszeichen_2
    uint8_t bVZE_Warnung_Verkehrszeichen_3; // warning symbol for traffic sign @ref ui8_VZE_Verkehrszeichen_3
    uint8_t ui8VZE_Verkehrszeichen_1;       // traffic sign
    uint8_t ui8VZE_Verkehrszeichen_2;       // traffic sign
    uint8_t ui8VZE_Verkehrszeichen_3;       // traffic sign
    uint8_t ui8VZE_Statuszaehler_1;         // distance counter to @ref ui8_VZE_Verkehrszeichen_1 @values 0...3
    uint8_t ui8VZE_Statuszaehler_2;         // distance counter to @ref ui8_VZE_Verkehrszeichen_2 @values 0...3
    uint8_t ui8VZE_Statuszaehler_3;         // distance counter to @ref ui8_VZE_Verkehrszeichen_3 @values 0...3
	uint8 reserved4;			        // 
	uint8 reserved5;			        //
	uint8 reserved6;			        //
} SKombiInstrument;

#define SKOMBI_INSTRUMENT_LENGTH 100

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
