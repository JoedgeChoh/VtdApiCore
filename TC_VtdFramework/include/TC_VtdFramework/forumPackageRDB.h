/**
 *
 * Implements the data structure for the Audi Forum Demonstrator
 *
 *  @copyright Audi Electronics Venture GmbH. All rights reserved
 *
 * @author              $Author: TEEF6VW $
 * @date                $Date: 2011-05-13 15:12:01 +0200 (Fr, 13 Mai 2011) $
 * @version             $Revision: 1004 $
 *
 * @remarks
 *
 */

typedef float float32;
typedef double float64;
    
    
#pragma pack (push, 4)

/**
 * Package ID for the custom package
 */
const uint32_t nRDB_PKG_ID_CUSTOM_AUDI_FORUM = 12000;

/**
 * version number to seperate different types of the data structure
 */
const uint32_t nVERSION_PKG = 1;


typedef struct
{
    /** 
     * represents the current destination distance 
     * @ values 0...1023
     */
    uint16_t ui16ACC_Abstandsindex;
    
    /** 
     * if set, the mockup will play the acc-sound 
     */
    uint8_t ui8ACC_Akustik;
    
    /** 
     * if another car is detected (in front of us) this is represented by this value)
     * @values 0...3
     */
    uint8_t ui8ACC_Relevantes_Objekt;
    
    /** 
     * represents the current state of the acc
     * @values 0...8
     */
    uint8_t ui8ACC_Status_Anzeige;
    
    /**
     * displays the primary status in different colors
     * @values 0..3
     */
    uint8_t ui8ACC_Status_Prim_Anz;
    
    /**
     * additional display (middle display) of pictures and text
     * @values 0...6
     */
    uint8_t ui8ACC_Status_Zusatzanz;
    
    
    /** 
     *shows the red lights around the speed display
     */
    bool bACC_Tachokranz;
    
    /**
     * additional text information e.g. ACC not available
     * @values 0...10
     */
    uint8_t ui8ACC_Texte;
    
    /**
     * several information about acc e.g. CAR_ _ _CAR - symbols, ACC ready,....
     * @attention very important
     * @values 0...31
     */
    uint8_t ui8ACC_Texte_Primaeranz;
    
    /**
     * some information about acc states and distance 
     * @values 0...20
     */
    uint8_t ui8ACC_Texte_Zusatzanz;
    
    /** 
     * displays the red symbol around the speed display and shows the destination speed @ headup 
     */
    float64 f64ACC_Wunschgeschw;
    
    /**
     * ACC handshake
     * @values 0...7
     */
    uint8_t ui8ACC_Status_ACC;
} RDB_CUSTOM_MOCKUP_ACC_t;


typedef struct 
{
    /**
     * displays the yellow HCA display
     */
    bool bLDW_Status_LED_gelb;
    /**
     * displays the green HCA display
     */
    bool bLDW_Status_LED_gruen;
    
    /**
     * displays HCA text information e.g. Fahrerübernahme 
     * @values 0...4
     */
    uint8_t ui8LDW_Texte;
    
    /**
     * displays the street and the lane borders (maybe red) 
     * @values 0...15
     */
    uint8_t ui8LDW_Lernmodus_seitenabhaengig;
    
    /**
     * represents the status of HCA 
     * @values 0...15
     */
    uint8_t ui8HCA_01_Status_HCA;
    
    /**
     * HCA sound
     * @values 0..3
     */
    uint8_t ui8LDW_Gong;
} RDB_CUSTOM_MOCKUP_HCA_t;

typedef struct
{
    /**
     * represents the internal state of presense 
     */
    uint8_t ui8PS_Stufe;
    
    /**
     * dedicated signal to fire the Belt
     * @value 0..3 intensity of the belt firing
     */
    uint8_t ui8Gurtstraffer;
    
    /**
     * dedicated signal to 
     */
    bool bOptischeWarnung;
    
    /**
     * dedicated signal to send a GONG -> same as ACC
     */
    bool bAkustischeWarnung;
    
    /**
     * dedicatde signal to activate both direction indicators
     */
    bool bWarnblinken;
    
    /**
     * dedicate signal to close to roof window
     */
    bool bDachfensterSchliessen;
    
    /**
     * dedicate signal to close the side windows
     */
    bool bFensterSchliessen;
    
    /**
     * sends out the Warning text to the middle display 
     */
    uint8_t ui8ACC_Texte_braking_guard;
} RDB_CUSTOM_MOCKUP_PS_t;


typedef struct
{
    /**
     * sends out a text over an internal hashtable
     * @values 0...7
     */
    uint8_t ui8VZE_Hinweistext;
    
    /**
     * activates the different types of displaying the information 
     * @values 0...3
     */
    uint8_t ui8VZE_Anzeigemodus;
    
    /**
     * additional sign to @ref ui8_VZE_Verkehrszeichen_1
     */
    uint8_t ui8VZE_Zusatzschild_1;
    
    /**
     * additional sign to @ref ui8_VZE_Verkehrszeichen_2
     */
    uint8_t ui8VZE_Zusatzschild_2;
    
    /**
     * additional sign to @ref ui8_VZE_Verkehrszeichen_3
     */
    uint8_t ui8VZE_Zusatzschild_3;
    
    /**
     * warning symbol for traffic sign @ref ui8_VZE_Verkehrszeichen_1
     */
    bool bVZE_Warnung_Verkehrszeichen_1;
    
    /**
     * warning symbol for traffic sign @ref ui8_VZE_Verkehrszeichen_2
     */
    bool bVZE_Warnung_Verkehrszeichen_2;
    
    /**
     * warning symbol for traffic sign @ref ui8_VZE_Verkehrszeichen_3
     */
    bool bVZE_Warnung_Verkehrszeichen_3;
    
    /**
     * traffic sign
     */
    uint8_t ui8VZE_Verkehrszeichen_1;
    
    /**
     * traffic sign
     */
    uint8_t ui8VZE_Verkehrszeichen_2;
    
    /**
     * traffic sign
     */
    uint8_t ui8VZE_Verkehrszeichen_3;
    
    /**
     * distance counter to @ref ui8_VZE_Verkehrszeichen_1
     * @values 0...3
     */
    uint8_t ui8VZE_Statuszaehler_1;
    
    /**
     * distance counter to @ref ui8_VZE_Verkehrszeichen_2
     * @values 0...3
     */
    uint8_t ui8VZE_Statuszaehler_2;
    
    /**
     * distance counter to @ref ui8_VZE_Verkehrszeichen_3
     * @values 0...3
     */
    uint8_t ui8VZE_Statuszaehler_3;
} RDB_CUSTOM_MOCKUP_VZE_t;

typedef struct
{
    /**
     * distance light on/off
     */
    bool bAFS_Fernlicht_Status;
} RDB_CUSTOM_MOCKUP_AL_t;

typedef struct 
{
    /** ACC **/
    RDB_CUSTOM_MOCKUP_ACC_t sACC;
        
    /** HCA **/
    RDB_CUSTOM_MOCKUP_HCA_t sHCA;
    
    /** adaptive light **/
    RDB_CUSTOM_MOCKUP_AL_t sAL;
    
    /** presense **/
    RDB_CUSTOM_MOCKUP_PS_t sPS;
    
    /** traffic signs **/
    RDB_CUSTOM_MOCKUP_VZE_t sVZE;
    
} RDB_CUSTOM_MOCKUP_t;

// end of pragma 4
#pragma pack(pop)

