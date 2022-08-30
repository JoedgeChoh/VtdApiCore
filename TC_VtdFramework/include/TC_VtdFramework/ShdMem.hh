/* ===================================================
 *  file:       ShdMem.hh
 * ---------------------------------------------------
 *  purpose:	Shared Memory management
 * ---------------------------------------------------
 *  first edit:	20.08.2005 by M. Dupuis @ VIRES GmbH
 *  last mod.:  20.08.2005 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_SHDMEM_HH
#define _FRAMEWORK_SHDMEM_HH

// ====== INCLUSIONS ======
#include <sys/shm.h>

namespace Framework
{

class ShdMem
{
    public:
        static const unsigned int sKeyRec = 0x0815a;
        static const unsigned int sKeyImg = 0x0816a;
    
    private:
        /**
        * key
        */
        int mKey;
        
        /**
        * total size of the shared memory segment
        */
        unsigned long mTotalSize;
        
        /**
        * total size of used portion of the sm
        */
        unsigned long mUsedSize;
        
        /**
        * start pointer
        */
        char* mStart;
        
        /**
        * number of connected participants
        */
        int mConnected;
        
    public:
        /**
        * constructor
        *   @param  key         identifier of the shared memory
        *   @param  size        total size of the shared memory
        *   @param  autoCreate  automatically create shared memory if it does not yet exist
        */
        explicit ShdMem( unsigned int key, unsigned long size, bool autoCreate = true );

        /**
        * Destroy the class. 
        */
        virtual ~ShdMem();
        
        /**
        * clear the entire shared memory
        */
        void clear();
        
        /**
        * create a shared memory segment with defined key and size
        * @return start pointer of segment
        */
        void* create();
        
        /**
        * destroy the current shared memory
        * @return shared memory handle
        */
        int destroy();
        
        /**
        * detach from shared memory
        * @return shared memory handle
        */
        int detach();
        
        /**
        * attach to shared memory
        * @return start pointer of segment
        */
        void* attach();
        
        /**
        * member access function
        */
        unsigned int getKey() const;
        
        /**
        * get the pointer to the start of the shared memory
        * @return   pointer to start of shared memory
        */
        void* getStart() const;
        
        /**
        * get the size of the shared memory
        * @return   size of shared memory
        */
        unsigned long getSize() const;
        
        /**
        * query whether the Shm is on idle (nobody connected)
        * @return true if nobody is connected
        */
        bool idle() const;
};
} // namespace Framework

#endif /* _FRAMEWORK_SHDMEM_HH */
