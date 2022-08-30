#ifndef _VTDFRAMEWORK_SHAREDMEMORY_HH
#define _VTDFRAMEWORK_SHAREDMEMORY_HH

namespace VTD {

typedef unsigned int SharedMemoryHandle; ///< Handle used to uniquely identify a shared memory segment.

class SharedMemory
{
public:

    /**
    * constructor
    *   @param  id          identifier of the shared memory
    *   @param  size        total size of the shared memory
    *   @param  autoCreate  automatically create shared memory if it does not yet exist
    */
    explicit SharedMemory( const SharedMemoryHandle& handle );

    /**
    * Destructor.
    */
    virtual ~SharedMemory();

    /**
    * create a shared memory segment with a specific size and attach to it.
    * @return pointer to beginning of segment or nullptr on fail.
    */
    void* createAndAttach(size_t size);

    /**
    * create a shared memory segment with a specific size.
    * @return true if the segment was created successfully, false otherwise.
    */
    bool create(size_t size);

    /**
    * attach to a shared memory segment.
    * @return pointer to beginning of segment or nullptr on fail.
    */
    void* attach();

    /**
    * detach from shared memory
    * @return shared memory handle
    */
    bool detach();

    /**
    * destroy the current shared memory
    * @return shared memory handle
    */
    bool destroy();

    /**
    * get Identifier for shared memory segment
    * @return shared memory handle
    */
    inline SharedMemoryHandle getHandle() const { return handle_; }

    /**
    * get the pointer to the beginning of the shared memory segment.
    * @return pointer to beginning of segment or nullptr on fail.
    */
    inline void* getStart() const { return start_; }

    /**
    * get the size of the shared memory segment.
    * @return size of shared memory
    */
    size_t getSize() const;

    /**
    * query whether the Shm is on idle (nobody connected)
    * @return true if nobody is connected
    */
    inline bool idle() const { return (getConnected() == 0); }

    /**
     * @brief query the number of connected participants
     * @return the number of connected participants.
     * Will be 0 if shared memory region does not exist or is not attached.
     */
    unsigned int getConnected() const;

private:
    SharedMemoryHandle handle_; ///< shared memory handle
    size_t totalSize_;          ///< total size of the shared memory segment
    void* start_;               ///< start ptr
    bool isOwner_;              ///< is this instance the owner of the segment
};

} // namespace VTD

#endif // _VTDFRAMEWORK_SHAREDMEMORY_HH
