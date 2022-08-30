#ifndef VTDFRAMEWORK_SHAREDMEMORYIO_H
#define VTDFRAMEWORK_SHAREDMEMORYIO_H

#include <stdlib.h>
#include <VtdToolkit/RDBHandler.hh>
#include <VtdCore/Ipc/SharedMemory.h>

namespace VTD {

class SharedMemoryBuffer {
public:
    SharedMemoryBuffer()
        : info(0)
        , rdbMsg(0)
    {}

    ~SharedMemoryBuffer() {}

    RDB_SHM_BUFFER_INFO_t* info;
    RDB_MSG_t* rdbMsg;
};

typedef std::vector<SharedMemoryBuffer> SharedMemoryBufferList;
typedef std::vector<RDB_MSG_t*> RdbMsgList;

/**
 * @brief The SharedMemoryIO class for reading and writing of
 * shared memory regions used with RDB buffers.
 */
class SharedMemoryIO {

public:
    SharedMemoryIO(SharedMemoryHandle shmHandle) ;
    ~SharedMemoryIO();

    /**
     * @brief createAndAttach
     * @param size
     * @return
     */
    bool createAndAttach(size_t size);

    /**
     * @brief attach
     * @return
     */
    bool attach();

    /**
     * @brief detach
     * @return
     */
    bool detach();

    /**
     * only the owning process may destroy the shm region.
     * @return
     */
    bool destroy();

    /**
     * @brief isOpen
     * @return
     */
    inline bool isAttached() { return shm_.getStart() != 0; }

    /**
     * @brief getNumberOfBuffers
     * @return the total number of buffers in the shared memory region.
     */
    unsigned int getNumberOfBuffers() const;

    /**
     * @brief get all buffers in this shared memory region.
     * @return
     */
    SharedMemoryBufferList getBuffers();

    /**
     * @brief get a specific buffer at a known index.
     * @param index The zero based index of the buffer.
     */
    SharedMemoryBuffer getBufferInfo(unsigned int index);

    /**
     * @brief get the next buffer that
     * is not locked and has the given check mask flags set.
     * If more than one buffer is readable, the one with the
     * lower frame number takes precedence.
     * @param checkMask the flags that should be set.
     * @return SharedMemoryBuffer object or 0 if buffer cannot be accessed or is locked.
     */
    SharedMemoryBuffer getNextBuffer(unsigned int checkMask);

    /**
     * @brief get the buffer with the given id that is not locked
     * and has the given check mask flags set.
     * @param checkMask the flags that should be set.
     * @param id the buffer's unique id
     * @return SharedMemoryBuffer object containing pointers or 0 if buffer cannot be accessed or is locked.
     */
    SharedMemoryBuffer tryGetBuffer(unsigned int checkMask, uint16_t bufferId);

    /**
     * @brief clearBuffer
     * @param index
     * @return
     */
    inline bool clearBuffer(unsigned int index, bool force) { return rdbHandler_.shmBufferClear(index, force); }

    /**
     * @brief Set lock flag only if not locked.
     * @param buffer
     * @return true if buffer was locked successfully, false if buffer was already locked or an error occurred.
     */
    bool tryLockBuffer(RDB_SHM_BUFFER_INFO_t& buffer);

    /**
     * @brief Force lock buffer.
     * @param buffer
     */
    inline void lockBuffer(RDB_SHM_BUFFER_INFO_t& buffer) { buffer.flags |= RDB_SHM_BUFFER_FLAG_LOCK; }

    /**
     * @brief Release lock on buffer
     * @param buffer
     */
    inline void releaseBuffer(RDB_SHM_BUFFER_INFO_t& buffer) { buffer.flags &= ~RDB_SHM_BUFFER_FLAG_LOCK; }

    /**
     * @brief getShmHandle
     * @return
     */
    inline SharedMemoryHandle getShmHandle() const { return shm_.getHandle(); }

    /**
     * @brief getShmSize
     * @return
     */
    inline size_t getShmSize() const { return shm_.getSize(); }

private:
    Framework::RDBHandler rdbHandler_;  // use the RDBHandler helper routines to handle
    SharedMemory shm_;                  // shared memory abstraction class
};

} //namespace VTD

#endif //VTDFRAMEWORK_SHAREDMEMORYIO_H
