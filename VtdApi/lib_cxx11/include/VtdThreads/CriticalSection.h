#ifndef VTDFRAMEWORK_CRITICALSECTION_H
#define VTDFRAMEWORK_CRITICALSECTION_H

#include <VtdCore/BasicTypes.h>
#include <VtdCore/Macros.h>

#include <boost/thread.hpp>

namespace VTD {

template <class Lock>
class ScopedLock {
public:
    explicit ScopedLock(Lock& lock) : lock_(lock) {
        lock.lock();
    }

    ~ScopedLock() {
        lock_.release();
    }

private:
    Lock& lock_;

    ScopedLock(const ScopedLock&);
    ScopedLock& operator=(const ScopedLock&);
};

class CriticalSection {
public:
    CriticalSection();
    ~CriticalSection();

    void lock();
    void release();

private:
    friend class ScopedLock<CriticalSection>;

    boost::mutex mutex_;

    CriticalSection(const CriticalSection&);
    CriticalSection& operator=(const CriticalSection&);
};


} //namespace VTD

#endif //VTDFRAMEWORK_CRITICALSECTION_H
