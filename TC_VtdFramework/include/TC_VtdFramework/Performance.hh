/* ===================================================
 *  file:       Performance.hh
 * ---------------------------------------------------
 *  purpose:	performance monitoring
 * ---------------------------------------------------
 *  first edit:	29.07.2016 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_PERFORMANCE_HH
#define _FRAMEWORK_PERFORMANCE_HH

// ====== INCLUSIONS ======
#include "BaseClass.hh"
#include "Clock.hh"

namespace Framework
{
    class ScpParser;
    
class Performance : public BaseClass
{
    public:
        /**
        * check for real-time violation?
        */
        bool mCheckRealTimeViolation;
        
        /**
        * has real-time watching been set explicitly?
        */
        bool mExplicitRealTimeCheck;
        
        /**
        * tolerance for real-time violation (fraction of nominal frame duration)
        */
        double mRealTimeTolerance;
        
        /**
        * remember under/overruns
        */
        unsigned int mNoUnderruns;
        unsigned int mNoOverruns;
        
        /**
        * number of measurements
        */
        unsigned int mNoMeasurements;
        
        /**
        * run in verbose mode?
        */
        bool mVerbose;
        
        /**
        * broadcast information?
        */
        bool mBroadcast;
        
        /**
        * current computed frame time
        */
        double mNominalFrameTime;
        
        /**
        * current measured frame time
        */
        double mActualFrameTime;
        
        /**
        * print output permanently?
        */
        bool mLiveMode;
        
    private:
        /**
        * last simulation time
        */
        double mLastSimTime;
        
        /**
        * log total real-time
        */
        double mTotalRealTime;
        
        /**
        * clock for debugging
        */
        Util::Clock mClock;
        
    public:
        /**
        * constructor
        *   @param  name    name under which data is managed
        *   @param  myError pointer to object fo error handling
        */
        explicit Performance( const std::string & name, Util::ErrorBase *myError = NULL );

        /** 
        * Destroy the class.
        */
        virtual ~Performance();
        
        /**
        * debug print
        */
        void print();
        
        /**
        * reset the watchdog
        * @param time   init value for time
        */
        virtual void reset( const double & time = 0.0 );
        
        /**
        * update 
        * @param simTime     current simulation time
        * @param runMode     true if simulation is in RUN mode
        * @param debugOutput print debugging information
        */
        void update( const double & simTime, bool runMode, int highestWaitFrameSource = -1, bool debugOutput = false );
        
        /**
        * parse the configuration message
        * @param parser pointer to SCP parser
        * @param tgtEntity pointer to entity for which to interpret the messages
        */
        void parseConfig( Framework::ScpParser *parser, const std::string & tgtEntity );
};
} // namespace Smart

#endif /* _FRAMEWORK_PERFORMANCE_HH */
