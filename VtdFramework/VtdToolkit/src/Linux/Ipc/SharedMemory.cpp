#include <iostream>
#include <stdio.h>
#include <cstring>
#include <sys/shm.h>
#include <VtdCore/Ipc/SharedMemory.h>
#include <VtdCore/Logging/Log.h>

namespace VTD {

SharedMemory::SharedMemory( const SharedMemoryHandle& handle ) :
    handle_(handle),
    totalSize_(0),
    start_(0),
    isOwner_(false)
{ /**/ }

SharedMemory::~SharedMemory()
{
    if(isOwner_) {
        destroy();
    }
    else if(start_) {
        detach();
    }
}

void* SharedMemory::createAndAttach(size_t size)
{
    if(create(size)) {
        return attach();
    }
    return 0;
}

bool SharedMemory::create(size_t size)
{
    if (start_) {
        VTD_LOG_ERR("VtdToolkit: A shared memory region is already open, could not be created.");
        return false;
    }

    int shmId = shmget(handle_, 0, 0);
    if (shmId < 0 ) {
        // shared memory does not exist yet
        //create the segment
        const int flag  = IPC_CREAT | 0777;
        shmId = shmget(handle_, size, flag);
        if (shmId < 0) {
            VTD_LOG_ERRNO("VtdToolkit: shmget()");
            start_ = 0;
            return false;
        }
        totalSize_ = size;
        isOwner_ = true;
        return true;
    }
    else {
        VTD_LOG_ERR("VtdToolkit: Shared memory already exists");
    }

    return false;
}

void* SharedMemory::attach()
{
    int shmId = shmget(handle_, 0, 0);
    if (shmId < 0 ) {
        VTD_LOG_ERRNO("VtdToolkit: Could not attach to SharedMemory segment");
        return 0;
    }

    // now attach to the segment
    start_ = shmat(shmId, static_cast<void*>(0), 0);
    if (start_ == (void*) -1) {
        VTD_LOG_ERRNO("VtdToolkit: shmat()");
        start_ = 0;
        return 0;
    }

    struct shmid_ds sInfo;
    shmId = shmctl( shmId, IPC_STAT, &sInfo ) ;
    if ( shmId < 0 ) {
        VTD_LOG_ERRNO("VtdToolkit: shmctl()");
    }
    else {
        totalSize_ = sInfo.shm_segsz;
    }

    return start_;
}

bool SharedMemory::detach()
{
    if(!start_) {
        VTD_LOG_ERR("VtdToolkit: Not attached.");
        return false;
    }

    int shmid = shmdt(start_);
    if (shmid < 0) {
        VTD_LOG_ERRNO("VtdToolkit: shmdt()");
        return false;
    }

    start_ = 0;
    return true;
}

bool SharedMemory::destroy()
{
    int shmid;
    if(start_) {
        shmid = shmdt(start_);
        if (shmid < 0) {
            VTD_LOG_ERRNO("VtdToolkit: shmdt()");
        }
    }

    shmid = shmget(handle_, 0, 0);
    if(shmid < 0) {
        VTD_LOG_ERRNO("VtdToolkit: shmget()");
        return false;
    }

    shmid = shmctl(shmid, IPC_RMID, static_cast<struct shmid_ds*>(0));
    if (shmid < 0) {
        VTD_LOG_ERRNO("VtdToolkit: shmctl()");
        return false;
    }

    start_ = 0;
    return true;
}

size_t SharedMemory::getSize() const
{
    int shmid = shmget(handle_, 0, 0);
    if (shmid < 0) {
        VTD_LOG_ERRNO("VtdToolkit: shmget()");
        return 0;
    }

    shmid_ds info;
    shmid = shmctl(shmid, IPC_STAT, &info);
    if (shmid < 0) {
        VTD_LOG_ERRNO("VtdToolkit: shmctl()");
        return 0;
    }
    return info.shm_segsz;
}

unsigned int SharedMemory::getConnected() const
{
    struct shmid_ds sInfo;

    int shmid = shmget(handle_, 0, 0);
    if (shmid < 0) {
        VTD_LOG_ERRNO("shmget()");
        return 0;
    }

    shmid = shmctl(shmid, IPC_STAT, &sInfo);
    if (shmid < 0) {
        VTD_LOG_ERRNO("VtdToolkit: shmctl()");
        return 0;
    }

    return sInfo.shm_nattch;
}

} // namespace VTD

