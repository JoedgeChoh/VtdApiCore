/* ===================================================
 *  file:       ScpParser.hh
 * ---------------------------------------------------
 *  purpose:	parse an incoming SCP text message
 * ---------------------------------------------------
 *  first edit:	04.01.2008 by M. Dupuis @ VIRES GmbH
 *  last mod.:  04.01.2008 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_SCP_PARSER_HH
#define _FRAMEWORK_SCP_PARSER_HH

#include <vector>
#include <map>
#include <string>

namespace Util
{
    class ErrorBase;
}

namespace Com
{
    class NetPackage;
}

namespace Framework
{
    
class ScpParser
{
    public:
        /**
        * opcodes of incoming tags
        */
        enum ScpOpcode
        {
            ocUnknown = 0,
            ocEOF,
            ocLoadScenario,
            ocSaveScenario,
            ocSimDone,
            ocLoadReplay,
            ocDoFrame,
            ocSet,
            ocStart,
            ocStop,
            ocSensor,   //10
            ocLoad,
            ocFrustum,
            ocPosition,
            ocCull,
            ocTraffic,
            ocRecord,
            ocFile,
            ocPort,
            ocGSIConfig,
            ocReset,    //20
            ocTrigger,
            ocPlayer,
            ocFilter,
            ocTaskControl,
            ocInterface,
            ocImageGenerator,
            ocMockup,
            ocSound,
            ocDataVis,
            ocScVis,   //30
            ocGSI,
            ocRecPlay,
            ocSceneInspector,
            ocDynamics,
            ocSync,
            ocVideo,
            ocDebug,
            ocCamera,
            ocProjection,
            ocSymbol,   //40
            ocOverlay,
            ocRestart,
            ocTest,
            ocPosPlayer,
            ocRectSize,
            ocReplay,
            ocViewInertial,
            ocViewRelative,
            ocViewPlayer,
            ocViewPos,     //50
            ocPosInertial,
            ocPosRelative,
            ocPosTether,
            ocPosTetherInertial,
            ocPosSensor,
            ocPause,
            ocStep,
            ocSpeed,
            ocSimCtrl,
            ocEgoCtrl,    //60
            ocLaneChange,
            ocDriver,
            ocVehicle,
            ocWarnActDef,
            ocWarnActSet,
            ocDisplay,
            ocSensorSymbols,
            ocDatabase,
            ocWarning,
            ocCounter,   //70
            ocResetPlayer,
            ocBoundingBox,
            ocPosEyepoint,
            ocInstrument,
            ocEnvironment,
            ocTimeOfDay,
            ocOrigin,
            ocInstruments,
            ocRoadInfo,
            ocConvert,  //80
            ocText,
            ocPosScreen,
            ocScale,
            ocShowEgo,
            ocConfig,
            ocContactPoint,
            ocControl,
            ocLine,
            ocOrientation,
            ocOutput, //90
            ocUnloadSensors,
            ocLightSource,
            ocOn,
            ocOff,
            ocRemove,
            ocDynamicsPlugin,
            ocVisibility,
            ocPlayerDef,
            ocWindow,
            ocVIL,  //100
            ocImu,
            ocLaserbird,
            ocEyepointOffset,
            ocRange,
            ocProject,
            ocSky,
            ocLayoutFile,
            ocInit,
            ocFileList,
            ocObserver, //110
            ocSource,
            ocTeam,
            ocMaster,
            ocSlave,
            ocQuery,
            ocRace,
            ocReply,
            ocPathS,
            ocTrackPos,
            ocRoad,    //120
            ocInfo,
            ocShow,
            ocHide,
            ocTrafficLight,
            ocPhase,
            ocSetPhase,
            ocSetCtrl,
            ocIgnore,
            ocVersion,
            ocError,  // 130
            ocPosCamera,
            ocShape,
            ocSphere,
            ocJoystick,
            ocAxis,
            ocPrecipitation,
            ocTextSource,
            ocDriverInput,
            ocLight,
            ocPath,  // 140
            ocRDB,
            ocTaskState,
            ocAttenuation,
            ocIntensity,
            ocInitDone,
            ocVistaOverlay,
            ocVehicleDef,
            ocConnection,
            ocSUMO,
            ocEdge,     // 150
            ocPosRoad,
            ocCreate,
            ocCommand,
            ocActionMeeting,
            ocVisualDatabase,
            ocTemplate,
            ocMirrorConfig,
            ocRail,
            ocSwitch,
            ocFriction,  // 160
            ocButton,
            ocWheel,
            ocMask,
            ocRun,
            ocReceipt,
            ocPlugin,
            ocMotionSystem,
            ocShift,
            ocZoom,
            ocModelDescription,  // 170
            ocMirrors,
            ocEyepoints,
            ocEyepoint,
            ocMirror,   
            ocTarget,
            ocModifyLayout,
            ocAdd,
            ocAnchor,
            ocSurfaceCRG,
            ocParamServer,
            ocCommit,
            ocSubmit,
            ocPush,
            ocSubscribe,
            ocPublish,
            ocNotify,
            ocUpdate,
            ocSignal,
            ocApply,
            ocSimServer,
            ocPosOffset,
            ocNoise,
            ocDataLoss,
            ocCollision,
            ocIntersection,
            ocHit,
            ocSCP,
            ocDump,
            ocRecordings,
            ocRealtimeMonitor,
            ocScreenBox,
            ocSun,
            ocOffset,
            ocScenario,
            ocImageSource,
            ocLabelSource,
            ocZone,
            ocEngine,
            ocLicense,
            ocSimState,
            ocDate,
            ocUnloadSensor,
            ocUnloadPlugin,
            ocModuleManager,
            ocSpare22,
            ocSpare23,
            ocSpare24,
            ocSpare25,
            ocSpare26,
            ocSpare27,
            ocSpare28,
            ocSpare29,
            ocSpare30,
            ocSpare31,
            ocSpare32,
            ocSpare33,
            ocSpare34,
            ocSpare35,
            ocSpare36,
            ocSpare37,
            ocSpare38,
            ocSpare39,
            ocSpare40,
            ocSpare41,
            ocSpare42,
            ocSpare43,
            ocSpare44,
            ocSpare45,
            ocSpare46,
            ocSpare47,
            ocSpare48,
            ocSpare49,
            ocSpare50,
            ocSpare51,
            ocSpare52,
            ocSpare53,
            ocSpare54,
            ocSpare55,
            ocSpare56,
            ocSpare57,
            ocSpare58,
            ocSpare59,
            ocSpare60
        };
    
    protected:
        /**
        * the name of this module
        */
        std::string mName;
	
        /**
        * the error handling object (may be inherited from instantiating object)
        */
        Util::ErrorBase *mError;
        
        /**
        * remember whether error handling object has been created locally
        */
        bool mLocalError;
                
    public:
        /**
        * constructor
        *   @param  name    name under which data is managed
        *   @param  myError pointer to object fo error handling
        */
        explicit ScpParser( const std::string & name, Util::ErrorBase *myError = 0 );

        /** 
        * Destroy the class.
        */
        virtual ~ScpParser();

        /**
        * get the name of this entity
        * @return entity's name
        */
        const std::string & getName() const;
        
        /**
        * set the name of this entity
        * @param name   new name
        */
        void setName( const std::string & name );

        /**
        * print info string to stderr
        */
        virtual void print();
        
        /**
        * handle SCP commands from a file
        * @param filename   name of the file which is to be interpreted
        * @return true if command could be processed
        */
        bool handleFile( const std::string & filename );
        
        /**
        * handle an incoming net package
        * @param pkg    the net package
        * @return true if command could be processed
        */
        bool handlePackage( const Com::NetPackage* pkg );
        
        /**
        * convert an incoming package into a string
        * @param pkg    the net package
        * @return string containing the text of the whole package
        */
        std::string package2string( const Com::NetPackage* pkg );
        
        /**
        * convert an incoming package into a string and retrieve sender info
        * @param pkg    the net package
        * @param sender the name of the sender (return value)
        * @return string containing the text of the whole package
        */
        std::string package2string( const Com::NetPackage* pkg, std::string & sender );
        
        /**
        * handle a text command
        * @param cmd    command string
        * @return true if command could be processed
        */
        bool handleCommand( const std::string & cmd );
        
        /**
        * get the next opcode that was read from SCP
        * @return opcode of last read SCP entry or EOF if none is available
        */
        ScpOpcode getNextOpcode();
        
        /**
        * get the last opcode that was read from SCP
        * @return opcode of current SCP entry or EOF if none is available
        */
        ScpOpcode getCurrentOpcode();
        
        /**
        * set the current opcode and return the same value
        * @param  opcode new current opcode
        * @return opcode that has been set
        */
        ScpOpcode setCurrentOpcode( ScpOpcode opcode );
        
        /**
        * push back the given opcode for interpretation at next run
        * @param  opcode  opcode which is to be pushed back
        */
        void pushOpcode( ScpOpcode opcode );
        
        /**
        * set the name of the element that is being parsed and whose opcode has
        * been determined
        * @param  name name of the current element
        */
        void setCurrentElementName( const std::string & name );
        
        /**
        * get the name of the element which matches the current opcode
        * @return name of the current element
        */
        const std::string & getCurrentElementName() const;
        
        /**
        * get the default port foreseen for SCP communication
        */
        int getDefaultPort();
        
        /**
        * set the verbose mode
        * @param    on true to enable verbose mode
        */
        void setVerbose( bool on );
                
        /**
        * get a bool attribute
        * @param attribName name of the attribute
        * @return value read from file
        */
        bool getBool( const std::string & attribName );
                
        /**
        * read an unsigned char attribute
        * @param attribName name of the attribute
        * @return value read from file
        */
        unsigned char getUChar( const std::string & attribName );
        
        /**
        * read an unsigned short attribute
        * @param attribName name of the attribute
        * @return value read from file
        */
        unsigned short getUShort( const std::string & attribName );
        
        /**
        * read an integer attribute
        * @param attribName name of the attribute
        * @return value read from file
        */
        int getInt( const std::string & attribName );
        
        /**
        * read an unsigned integer attribute
        * @param attribName name of the attribute
        * @return value read from file
        */
        unsigned int getUInt( const std::string & attribName );

        /**
        * read a unsigned 128 bit integer attribute
        * @param attribName name of the attribute
        * @return value read from file
        */
        __uint128_t getLInt( const std::string & attribName );
        
        /**
        * read a double attribute
        * @param attribName name of the attribute
        * @return value read from file
        */
        double getDouble( const std::string & attribName );
        
        /**
        * read a float attribute
        * @param attribName name of the attribute
        * @return value read from file
        */
        float getFloat( const std::string & attribName );
        
        /**
        * read a string attribute
        * @param attribName name of the attribute
        * @return value read from file
        */
        std::string getString( const std::string & attribName );
        
        /**
        * check whether an attribute is available
        * @param attribName name of the attribute
        * @return true if attribute is defined
        */
        bool hasAttribute( const std::string & attribName );
        
        /**
        * wrap an SCP text into an SCP message container
        * @param sender     sender of the message
        * @param receiver   receiver of the message
        * @param text       the message text
        * @param msgSize    the total size of the message (set by this routine)
        * @return pointer to the complete message (must be freed by calling routine)
        */
        void* text2msg( const std::string & sender, const std::string & receiver, const std::string & text, size_t & msgSize );
        
        /**
        * provide the return value of an unknown string
        * @return the "unknown: string
        */
        const std::string & unknownString();
        
        /**
        * set (remember) start level of an operation, this routine copies the
        * current level (mLevel) into the start level
        * @param modifier the value by which to modify the start level
        */
        void setStartLevel( int modifier = 0 );
        
        /**
        * preserve the current start level
        */
        void pushStartLevel();
        
        /**
        * restore the preserved start level
        */
        void popStartLevel();
        
        /**
        * check whether current level is below the start level
        * @return true if current level is below start level
        */
        bool belowStartLevel();
        
        /**
        * check whether the next level is below the start level
        * @return true if next level is below start level
        */
        bool nextLevelIsBelowStartLevel();
        
        /**
        * get the name corresponding to an opcode
        * @param opcode the opcode which is to be decrypted
        * @return opcode identifier
        */
        const std::string & getOpcodeName( unsigned int opcode );
        
        /**
        * flush the parser, i.e. go to EOF
        */
        void flush();
        
        /**
        * flush the current parser level, i.e. return to next item in previous level
        */
        void flushLevel();
        
        /**
        * get the command string which the parser is actually parsing
        * @return currently parsed command string
        */
        const std::string & getCommand() const;
        
        /**
        * query the attributes of a given command at a given index
        * @param index  index of attribute
        * @param name  name of attribute (return value)
        * @param value value of attribute (return value)
        * @return true if attribute at the given index exists
        */
        bool getAttributeAtIndex( unsigned int index, std::string & name, std::string & value );
        
        /**
        * query all attributes of the current command
        * @param attrList  list of attribute (return value)
        * @return true if attribute at the given index exists
        */
        bool getAllAttributes( std::string & attrList );
        
        /**
        * is there a text attached to the node?
        * @return true if text is attached
        */
        bool hasText();
        
        /**
        * get the attached text
        * @return attached text or empty string
        */
        const std::string & getText() const;
        
    private:
        /**
        * hold a map of attributes and string values coming from the parser
        */
        typedef std::map< std::string, std::string > AttribMap;
        AttribMap mAttribMap;

        /**
        * hold a map of keywords and opcodes
        */
        typedef std::map< std::string, unsigned int > StringValMap;
        StringValMap mOpcodeMap;
    
        /**
        * remember verbose mode
        */
        bool mVerbose;
        
        /**
        * a temporary string variable 
        */
        std::string mLcString;
        
        /**
        * remember the current parsing position in the SCP data
        */
        void *mpCurrentPos;
        
        /**
        * remember the current document that is being parsed
        */
        void *mpDocument;
        
        /**
        * hold a pushback list of opocodes
        */
        typedef std::vector< ScpOpcode > PushBackBuffer;
        PushBackBuffer mPushBackBuffer;
        
        /**
        * remember the current and next levels of operation
        */
        unsigned int mLevel;
        unsigned int mNextLevel;
        
        /**
        * set the start level of an operation
        */
        unsigned int mStartLevel;
        
        /**
        * preserved the start level of an operation
        */
        unsigned int mStartLevelBackup;
        
        /**
        * the unknown string
        */
        std::string mUnknownString;
        
        /**
        * remember the currently parsed command
        */
        std::string mCmd;
        
        /**
        * remember current opcode
        */
        ScpOpcode mCurrentOpcode;
        
        /**
        * get the current text sub-node
        */
        std::string mText;
        
        /**
        * remember current element's name
        */
        std::string mCurrentElementName;
        
    private:
        /**
        * convert an element name to an opcode
        * @param name   name of the element
        * @return the OpenDRIVE opcode resulting from the name
        */
        unsigned int getOpcodeFromElement( const std::string & name );
        
        /**
        * convert all values of a string/value map to lowercase
        * @param myMap  the map which is to be updated
        */
        void prepareMap( StringValMap & myMap );
        
        /**
        * convert a name to lowercase
        * @param name   the name which is to be converted
        * @return the name as lowercase representation
        */
        const std::string & loCase( const std::string & name );

        /**
        * initialize the keyword/opcode pairs
        */
        void initOpcodes();
        
        /**
        * fill the attribute list from the current element data
        * @param node    the element from which to draw the attributes
        * @return true if attributes have been found
        */
        bool fillAttributeList( void* node );
        
        /**
        * add an attribute to the nodes attribute map
        * @param key the key of the attribute
        * @param value the value of the attribute
        */
        void addAttribute( const std::string & key, const std::string & value );
        
        /**
        * clear the attribute list
        */
        void clearAttributes();

};
} // namespace Framework

#endif /* _FRAMEWORK_SCP_PARSER_HH */
